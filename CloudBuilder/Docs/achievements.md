Working with achievements {#achievements}
===========

CloudBuilder provides a platform independent way of handling achievements for your game. Note that **achievements need to be defined on the backoffice** before being used on the client.

This page is aimed at being a little tutorial on how to work with achievements from the CloudBuilder SDK (client). For the next steps, we will suppose that you already know how to create achievements from the backoffice. For a complete list of useful functions in the SDK, take a look at \ref user_achievements "Achievements module".

Querying the progress of the gamer
-----------

Fetching the state of achievements is a function that require the customer to be logged in. In general, the status of achievements represents an association between a gamer and a game.

The call that we are going to use is `ListAchievements`:

`void CloudBuilder::CUserManager::ListAchievements(const CotCHelpers::CHJSON *configuration, CloudBuilder::CResultHandler *handler)`

This call requires a configuration passed in the form of a `CHJSON` object as usual. Read the documentation for more information on the keys that should be passed. An example is shown below, we'll create UI buttons with information about each achievement. The GUI toolkit is virtual, and you may want to implement additional features such as pagination.

~~~~{.cpp}

CHJSON config;
CUserManager::Instance()->ListAchievements(&config, MakeResultHandler(this, &MyGame::OnListedAchievements));

if (code == enNoErr) {
	const CHJSON *achievements = result->GetJSON()->GetSafe("achievements");
	for (CHJSON::Iterator it = achievements->begin(); it != achievements->end(); ++it) {
		const CHJSON *node = *it;
		const char *achievementName = node->name();
		double progress = node->GetDouble("progress");

		GUI::Button *button = buttonList->AddButton();
		// The progress is expressed as a floating point number between 0 and 1
		button->progressPercent = progress * 100.0;
		
		// You can put additional data in the definition ('gameData' node)
		// Here we use that to hide some achievements by default and reveal them
		// explicitely by storing a property in the 'gamerData' (for the gamer)
		bool hiddenUnlessUnlocked = node->GetSafe("gameData")->GetBool("initiallyHidden");
		bool revealedByGamer = node->GetSafe("gamerData")->GetBool("unhidden");
		// Do not show hidden achievements
		if (hiddenUnlessUnlocked && !revealedByGamer)
			continue;
		
		// Some data can be displayed depending on the achievement name (used as an unique identifier)
		if (!strcmp(achievementName, "supersonic")) {
			// Display your text, potentially localized based on the state of the gamer
			button->title = "Supersonic runner!";
			if (progress >= 1)
				button->subtitle = "Achievement obtained because you rock!";
			else
				button->subtitle = "Finish the game in under one hour!";
		}
	}
}

~~~~

Notifying progress
-----------

If you have configured your achievements through the backoffice, you know that achievements are triggered when so-called units reach a certain value. This means that to trigger an achievement, you will increase the value of an unit. An easy way to perform that is by using the following method.

`void CloudBuilder::CUserManager::EarnAchievment(const char *unit, int increment, const CHJSON *gamerData, CResultHandler *handler);`

Most parameters except for the `unit` can be left at their default value, which means that the unit will be incremented from one and no gamer data will be posted. The following example shows how to notify an achievement. We expect an achievement like that to have been configured in the backoffice :

~~~~{.js}
"supersonic" {
	"type": "limit",
	"config": {
		"unit": "supersonic",
		"maxValue": 1
	}
}
~~~~

The special thing here is that the name of the achievement is the same as the unit, which should be perfect for most achievements. Posting an achievement is done as follows:

~~~~{.cpp}

CUserManager::Instance()->EarnAchievement("supersonic", +1, NULL, MakeResultHandler(this, MyGame::OnEarnAchievement));

void MyGame::OnEarnAchievement(eErrorCode code, const CCloudResult *result) {
	if (code == enNoErr) {
		// Process the response
	}
}

~~~~

Now on processing the response. The result is what you get from CloudBuilder::CUserManager::TransactionV2. That is, two nodes: `balance` and `achievements`. For a player who has never played before, the result should look like:

~~~~{.js}
{
	"balance": {
		"supersonic":   1
	},
	"achievements": {
		"supersonic": {
			"type": "limit",
			"config": {
				"maxValue": 1,
				"unit": "supersonic"
			},
			"progress": 1,
			"gamerData": {
				"key": "value"
			}
		}
	}
}
~~~~

This is it for the "simple" version. Achievements provide much more powerful functionality, which you can access by separately calling CloudBuilder::CUserManager::TransactionV2 (to post the fact that an unit has changed, potentially realizing an achievement) and CloudBuilder::CUserManager::SetAchievementData to associate data with the achievement if needed.

The previous call would look like this:

~~~~{.cpp}

using namespace CloudBuilder;
CHJSON config, tx;
tx.Put("supersonic", +1);
config.Put("transaction", tx);
config.Put("description", "Earned achievement supersonic by 1");
// The OnEarnAchievement can be the same as before
CUserManager::Instance()->TransactionV2(&config, MakeResultHandler(this, MyGame::OnEarnAchievement));

void MyGame::OnEarnAchievement(eErrorCode code, const CCloudResult *result) {
	if (code == enNoErr) {
		// And store associated data with the achievement
		CHJSON config;
		config.Put("domain", "private");		// default value, so not necessary
		config.Put("name", "supersonic");
		config.Put("data", 12345);				// anything actually
		CUserManager::Instance()->SetAchievementData(&config, ...);
	}
}

~~~~

Note that this time, we are making a transaction with a key value of name `supersonic`, and we are storing data (`SetAchievementData`) with the achievement `supersonic`. Unlike the previous call to `EarnAchievement`, they need not be the same. You could for instance configure an achievement named `beRich` which triggers when `goldCoins` reaches 100000. In that case, you would pass different strings to `TransactionV2` (`goldCoins`) and `SetAchievementData` (`beRich`).

Domains
-----------

By default, achievements use the key/value storage associated with the private domain (that is, reserved for this game). You may create achievement on different domains, in which case they refer to units posted in the corresponding domain.

Associating user data with an achievement
-----------

Data can be associated for an user and an achievement. To store it, pass a `CHJSON` as third parameter to CloudBuilder::CUserManager::EarnAchievement. Or call CloudBuilder::CUserManager::SetAchievementData as shown below. In the following case, we want to unhide an achievement that has been marked as hidden by default and not listed in the section above.

~~~~{.cpp}

CHJSON config, data;
data.Put("unhidden", true);
config.Put("data", data);
config.Put("name", "supersonic");
CUserManager::Instance()->SetAchievementData(&config, MakeResultHandler(...));

~~~~

Other uses for data stored by user and achievement include storing any useful detail on how the gamer did get the score.
