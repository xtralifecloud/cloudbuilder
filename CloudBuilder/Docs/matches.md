Working with matches {#matches}
===========

Clan of the Cloud provides a simple way to run matches between a set of gamers using the network. The match system is designed around a centralized game state stored on the Clan of the Cloud servers, with gamers participating to the match making a move, updating the global game state and notifying the other players on an asynchronous basis.

It means that this match system is better suited for turn by turn games, rather than real time games such as MMORPGs, which may require a more sophisticated logic to be handled on your servers.

As with other functionality, matches are scoped by domain, allowing to share data amongst multiple games. By default, your game has one dedicated domain called `private`, which you should use unless you need cross-game functionality.

API basics
-----------

The match manager is exposed through the class CloudBuilder::CMatchManager. It requires to be logged in prior to calling any of its functions. This class exposes the same functionality separated into one high level API with functions prefixed by HL, and one "normal", lower level API. The lower level API is state independent and similar to what other managers offer already. The high level API however provides a simple and clean way to start, join or resume a match and receive/post events through the use of a CloudBuilder::CMatch object.

The next code samples shown will be using the following functions, which allow to quickly make CloudBuilder::CResultHandler or CloudBuilder::CMatchResultHandler objects using a C++11 lambda objects. This can of course be replaced by traditional code. See @ref more_advanced for more information on this subject.

~~~~{.cpp}

using namespace CloudBuilder;
using namespace CotCHelpers;
using std::function;

static CResultHandler *MakeResultHandler(function<void(eErrorCode, const CCloudResult*)> func) {
	struct FunctionalResultHandler: CResultHandler {
		function<void(eErrorCode, const CCloudResult*)> func;
		FunctionalResultHandler(function<void(eErrorCode, const CCloudResult*)> func) : func(func), CResultHandler(this, &FunctionalResultHandler::Done) {}
		void Done(eErrorCode code, const CCloudResult *result) {
			func(code, result);
		}
	};
	return new FunctionalResultHandler(func);
}

static CMatchResultHandler *MakeMatchResultHandler(function<void(eErrorCode, const CCloudResult*, CMatch *)> func) {
	typedef function<void (eErrorCode, const CCloudResult*, CMatch *)> func_t;
	struct FunctionalResultHandler: CMatchResultHandler {
		func_t func;
		FunctionalResultHandler(func_t func) : func(func), CMatchResultHandler(this, &FunctionalResultHandler::Done) {}
		void Done(eErrorCode code, const CCloudResult *result, CMatch *match) {
			func(code, result, match);
		}
	};
	return new FunctionalResultHandler(func);
}

~~~~

Creating and listing matches
-----------

Creating a match is done by calling CloudBuilder::CMatchManager::CreateMatch or CloudBuilder::CMatchManager::HLCreateMatch. If you are using the high level method, it will result in a CloudBuilder::CMatch object that you can keep for use later. The following two snippets show how to do it:

~~~~{.cpp}

CHJSON config, customProps;
config.Put("domain", "private");
config.Put("maxPlayers", 10);
config.Put("description", "My match");
customProps.Put("gameType", "solo");
config.Put("customProperties", customProps);
CMatchManager::Instance()->CreateMatch(&config, MakeResultHandler([&] (eErrorCode err, const CCloudResult *result) {
	if (err == enNoErr) {
		const char *matchId = result->GetJSON()->GetSafe("match")->GetString("_id");
		StartGame(...);
	}
}));

~~~~

~~~~{.cpp}

CHJSON config;
config.Put("domain", "private");
config.Put("maxPlayers", 10);
config.Put("description", "My match");
config.Put("customProperties", CHJSON::parse("{\"gameType\": \"solo\""));
CMatchManager::Instance()->HLCreateMatch(&config, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
	if (err == enNoErr) {
		StartGame(match, ...);
	}
}));

~~~~

CloudBuilder::CMatch objects must be destroyed by calling CloudBuilder::CMatchManager::HLDestroyMatch when not needed anymore. This call will not actually delete or finish the match: it will just destroy the associated local object.

The `matchId` is used to identify the match in later requests. You will have to pass it to the API in the form of a JSON parameter named `id`. This is handled automatically if you are using the CloudBuilder::CMatch class though.

Once your game is created, you will want other players to join it, and CloudBuilder::CMatchManager::ListMatches is here for that. As described previously, your game has a dedicated domain. On this domain, any player is able to create matches. This means that there are potentially millions of matches scoped to your domain. In order to refine the potential matches that one may want to display, multiple parameters can be used. One of them is the `customProperties` of the match. When listing the matches available, you may pass a JSON node called `filter` in the configuration, containing a pair of key/values indicating the attributes that need to match in the `customProperties` of a match to be returned. In the previous case, let's say we want to list the solo matches only: then we could pass {"gameType": "solo"} as `filter`.

Additionally, a number of conditions will make a given match to be hidden from the list. These include the maximum number of players having been reached or the match being in finished state.

~~~~{.cpp}

CHJSON config;
config.Put("filter", CHJSON::parse("{\"gameType\": \"solo\""));
config.Put("domain", "private");
CMatchManager::Instance()->ListMatches(&config, MakeResultHandler([&] (eErrorCode err, const CCloudResult *result) {
	if (err != enNoErr) { return; }
	// List the match IDs available to join
	for (const CHJSON *node: *result->GetJSON()->GetSafe("matches")) {
		printf("A match with ID %s is available!\n", node->GetString("_id"));
	}
}));

~~~~

There is no equivalent high level function. The IDs listed above can be used to join or resume a match using either API then.

The lifecycle of a match
-----------

A match is created by a player which is called `creator`. A `creator` is solely able to perform some administrative functions, such as deleting or finishing a match. When creating a match, you automatically become a player (although you are able to leave it right away). Everyone is free to join the match, and leave it anytime. A notification is sent to every player whenever that happens.

When the match is considered complete, the `creator` should mark it finished by calling CloudBuilder::CMatchManager::FinishMatch or CloudBuilder::CMatch::Finish. He may optionally delete it later. Finished matches are not listed by default and all calls interacting with them do fail.

Match notifications
-----------

Match notifications (aKa events) are broadcasted on the domain corresponding to the match being run. Any player who has joined the match will automatically receive events indicating changes made to the match. These events happen when a player joins the match, leaves it or posts a move.

These events must be processed by each player prior to issuing additional commands. To do so, there is a parameter, called `lastEventId` that is required for some calls and must be set to the ID of the last event from the match. Among other things, this allows to detect race conditions and guarantee the integrity of the game.

This last event comes in two forms: either as a result of a match operation (in which case you can simply pick the `lastEventId` field within the server response) if you were the one initating it, or as the `event._id` field of the last received event. You do not need to do so if you are using the high level API.

In case a player joins the match, the following event will be received by other players:

~~~~{.js}
    {
        "event": {
            "_id": "548866edba0ec600005e1941",
            "match_id": "548866ed74c2e0000098db95",
            "playersJoined": [
                {
                    "gamer_id": "548866ed74c2e0000098db94",
                    "profile": {
                        "displayName": "Guest",
                        "lang": "en"
                    }
                }
            ]
        },
        "id": "9155987d-6322-46d4-9403-e90ab4ba5fa3",
        "type": "match.join"
    }
~~~~

In case a player leaves the match, similarly the following event will be received by others:

~~~~{.js}
    {
        "event": {
            "_id": "548866eeba0ec600005e1948",
            "match_id": "548866ed74c2e0000098db95",
            "playersLeft": [
                {
                    "gamer_id": "548866ed74c2e0000098db94",
                    "profile": {
                        "displayName": "Guest",
                        "lang": "en"
                    }
                }
            ]
        },
        "id": "5007fd0a-1365-4e87-aba8-5d916731e684",
        "type": "match.leave"
    }
~~~~

In case the match is marked as finished, the following event will be broadcasted to all players except the one who initiated it.

~~~~{.js}
    {
        "type": "match.finish",
        "event": {
            "_id": "54784d07a0fcf2000086457d",
            "finished": 1,
            "match_id": "54784d07f10c190000cb96e3"
        },
        "id": "d2f908d1-40d8-4f73-802e-fe0086bb6cd5"
    }
~~~~

In case an element was drawn from the shoe, an event like this is fired:

~~~~{.js}
	{
		"type": "match.shoedraw",
		"event": {
			"_id": "5492a7c7a6725f0000b59e4f",
			"count": 2,
			"match_id": "5492a7c6a6725f0000b59e46"
		},
		"id": "5e4e82c1-d728-4a4b-be40-e4abec320440"
	}
~~~~

Events are broadcasted in other situations, such as moves, but they are described within the related section. Subscribing to match events is done the same way as for other events, using the CloudBuilder::CUserManager::RegisterEventListener. When an event is received, if the type starts by `match.` and the `event.match_id` matches the ID of your current match, then it's for you.

When using CloudBuilder::CMatch, you may also register on this object to automate that. Both ways are shown below.

~~~~{.cpp}
void MyGame::Run() {
	CUserManager::Instance()->RegisterEventListener("private", this);
}

void MyGame::onEventReceived(const char *domain, const CCloudResult *event) {
	const char *type = event->GetJSON()->GetString("type");
	if (!strncmp(type, "match.", 6)) {
		const CHJSON *eventNode = event->GetJSON()->GetSafe("event");
		if (IsEqual(eventNode->GetString("match_id"), GetMatchId())) {
			// Event is for us... keep last event ID for the next request
			lastEventId = eventNode->GetString("_id");
		}
	}
}
~~~~

~~~~{.cpp}
void MyGame::Run(CMatch *match) {
	match->RegisterEventListener(this);
}

void MyGame::onMatchEventReceived(const CCloudResult *event) {
	const char *type = event->GetJSON()->GetString("type");
	const CHJSON *eventNode = event->GetJSON()->GetSafe("event");
	if (IsEqual(type, "match.move")) {
		// Perform a move event…
	}
}
~~~~

Note that unless you are using the CloudBuilder::CMatch class which does that for you, you need to take note of the changed `lastEventId` whenever an operation returns an updated match. This is because the player who issues a command, such as a CloudBuilder::CMatchManager::PostMove, will not receive himself the associated event. As such, he needs to take in account the resulting lastEventId returned, which will be needed for the next command. The next code snippet shows a typical low-level call with last event ID management.

~~~~{.cpp}
CHJSON config;
config.Put("id", matchId);
config.Put("move", CHJSON::parse("{\"killed\": true"));
CMatchManager::Instance()->PostMove(&config, NULL, NULL, MakeResultHandler([&] (eErrorCode err, const CCloudResult *result) {
	if (err != enNoErr) { return; }
	// Keep last event ID for later (use a copy-on-assign string object, because the returned string is deleted with the CCloudResult)
	lastEventId = result->GetJSON()->GetSafe("match")->GetString("lastEventId");
}));
~~~~


Synchronizing progress amongst players
-----------

Aside from spontaneous events (player joins, leaves, etc.), matches are made up of moves, which act as checkpoints for each "measurable step" in the game. A move is performed anytime by a player (the game logic should determine who has its turn each time), and is made up of two members:
- move: a freeform JSON that describes what happened. In the case of a chess game, it could contain "moved knight to B3".
- globalState: an optional freeform JSON that can be updated incrementally (i.e. only present attributes are affected, others are left untouched) and can contain the global state of the game. In the case of a chess game, it could contain the game piece matrix. Passing a global state will clear the history of events.

All events (move, join, etc.) are kept in the history of the match and will be passed along when fetching information about an individual match (CloudBuilder::CMatchManager::FetchMatch). This history can be used to reproduce the state of the game, by starting up clean and performing the pending moves locally. This allows to resume a match or simply join it anytime.

A global state is to be passed when you have a simple and concise way to describe the game field. If you do not pass a global state, individual events will be kept in the history of the match which might become too big at some point, depending on your game.

Therefore, you do not need to pass a global state with each move: it should be used to avoid messing up the history and if your game can support it. You need to pick an appropriate policy according to your game (maximum number of moves, checkpoints in-between, etc.).

Move events look like this:

~~~~{.js}
    {
        "type": "match.move",
        "event": {
            "_id": "54784176a8df72000049340e",
            "player_id": "547841755e4cfe0000bf6907",
            "move": {
                "what": "changed"
            }
        },
        "id": "d0fb71c1-3cd0-4bbd-a9ec-29cb46cf9203"
    }
~~~~

Private matches and invitations
-----------

Matches can not be made private directly, but they can be made hidden unless they have a particular property by using the `filter` property. Basically, one would simply create a match with a custom property named {"visible": "public"} and include this property in the filter when listing the public matches.

Once a player has created a given match, he can then invite other players he would like to join by sending an invitation. Of course, you should not send more invitations than the number of vacant players in the match.

~~~~{.cpp}

CHJSON config;
config.Put("id", matchId);
config.Put("gamer_id", friendId);
CMatchManager::Instance()->InvitePlayer(&config, ...);

~~~~

The other player will receive a message looking like the following, and should show a popup indicating that there is a pending invitation.

~~~~{.js}
    {
        "type": "match.invite",
        "event": {
            "_id": "54784d07a0fcf2000086457d",
            "match_id": "54784d07f10c190000cb96e3"
            "inviter": {
                "gamer_id": "5487260cf45e5f84c7cd7223",
                "profile": {
                    "displayName": "Guest",
                    "lang": "en"
                }
            }
        },
        "id": "d2f908d1-40d8-4f73-802e-fe0086bb6cd9"
    }
~~~~

The list of pending invitations can be shown by using CloudBuilder::CMatchManager::ListMatches and putting an `invited` attribute inside the configuration JSON. An invitation is cleared when the player joins the match or by calling CloudBuilder::CMatchManager::DismissInvitation. This call doesn't require the player ID, as it simply removes the authenticated player from the invited list.

Random-generator based games (Casino "shoe"-like functionality)
-----------

CloudBuilder provides functionality to help building games of chance, allowing each individual players to check the outcome of the match in order to ensure consistency. It does this by providing a server-based randomizing device, which hides sensitive information. Therefore, it can help ensure that all players, including the match creator have the same chances. And that no one is able to predict the outcome of the match (or fiddle/hack with it either, as other players are able to detect it).

The seed element that is returned with the detailed version of the match (i.e. when joining or fetching it), along with the shoe are the two elements which help building games of chance. The seed is a random number that is generated upon creation of every match. It can be used to initialize a pseudorandom number generator inside the game, and allows to ensure that every player will thus have the same sequence of values.

The shoe, as in Casino, is basically a container of possible values that are returned in a random order as they are poked. It could represent the values of the cards for instance. It is possible to have more than once the same element in the shoe (as when having two card sets). The shoe is posted by the person who creates the game and then shuffled. The shoe remains hidden, with no one having access to it, until the match is finished.

Players can draw one or more elements off the shoe by posting a request to this resource. The shoe is shared with all players, meaning that any element from the shoe is returned only once to a player having requested it.
When all items have been drawn from the shoe and more items are requested, the existing serie is duplicated, shuffled and appended to the current shoe, meaning an endless play can be considered.
Drawing items from the shoe will trigger one event of type `match.shoedraw` per request, sent to players except the caller. When the match finishes, fetching detailed info about the match will return the shoe. It can be used by all players to check that the game has been fair: should one player have hacked the game, it is possible to detect it by comparing the shoe to the actual moves.

To use the shoe in your match, the match creator must post an array of values in the configuration JSON. These values may be any object, from a simple number to an object with a complex hierarchy. We suggest using values as simple as possible though, to spare bandwidth when drawing items from the shoe. An example is shown below.

~~~~{.cpp}
CHJSON config, *shoe = CHJSON::Array();
config.Put("domain", "private");
config.Put("maxPlayers", 10);
// Put possible values in the shoe
shoe->Add(new CHJSON(1.));
shoe->Add(new CHJSON(2.));
shoe->Add(new CHJSON(3.));
shoe->Add(new CHJSON(4.));
config.Put("shoe", shoe);
CMatchManager::Instance()->HLCreateMatch(&config, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
	if (err == enNoErr) {
		...
	}
}));
~~~~

Drawing objects can be done this way:

~~~~{.cpp}
match.DrawFromShoe(2, NULL, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
	if (err != enNoErr) { return; }
	// Should have fetched two items from the list passed previously
	for (const CHJSON *node: *result->GetJSON()->GetSafe("drawnItems")) {
		printf("Got %d\n", node->valueInt());
	}
));
~~~~

When the game is finished, anyone is able check the contents of the shoe by using CloudBuilder::CMatchManager::FetchMatch and inspecting the `shoe` subnode of the `match` node present in the result.
