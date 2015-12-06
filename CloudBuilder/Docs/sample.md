Getting started {#sample_ref}
===========

We would like to thank you for downloading the CloudBuilder Client SDK and welcome you to the Clan! Through a few code
samples, this guide will present you all the basics and help you quickly get started.

Setup
===========

The first function to call when your application is launched is \link CloudBuilder::CClan::Setup CClan::Setup\endlink. This will configure the CloudBuilder library for
you. This function, as most of the functions from the SDK, exhibits a few concepts: you must pass additional parameters
in the form of a \link CotCHelpers::CHJSON CHJSON\endlink object and may provide a callback to be notified when the asynchronous process completes. The
following code snippet shows the structure that is used by most SDK API calls:

~~~~{.cpp}

class MyGame
{
	void Startup()
	{
		CotCHelpers::CHJSON json;
		json.Put("key", "*****");
		json.Put("secret", "*****");
		json.Put("env", "sandbox");
		CloudBuilder::CClan::Instance()->Setup(&json, CloudBuilder::MakeResultHandler(this, &MyGame::SetupDone));
	}

	void SetupDone(CloudBuilder::eErrorCode errorCode, const CloudBuilder::CCloudResult *result)
	{
		if (errorCode == CloudBuilder::enNoErr)
		{
			printf("Setup complete!\n");
		}
		else
		{
			printf("Setup failed with message %s!\n", result->GetErrorString());
		}
	}
};

~~~~

First about the \link CotCHelpers::CHJSON CHJSON\endlink object. See it as a simple bag of key/values. You will declare
one and put the values inside
(boolean, integer, floating point, string) using the Put method, passing the key and the value in this order. The
lifecycle of the CHJSON object is managed by you, so if you allocated it with new, you need to delete it sometime after
having passed it to the SDK.

Then about the \link CloudBuilder::CCloudResult CCloudResult\endlink. It is a simple object that basically just
encapsulates (error) information about the last call as well as the resulting JSON as returned by the server (exposed as a `CHJSON`), if
applicable. You may call \link CloudBuilder::CCloudResult::GetErrorString GetErrorString\endlink during your debugging phase to know what happened. To print out comprehensive information about the result, you may use the \link CloudBuilder::CCloudResult::Print Print\endlink method as follows:

~~~~{.cpp}
printf("Result: %s\n", result->Print().c_str());
~~~~

Thirdly, let's speak about the delegate system. The structure of a \link CloudBuilder::CResultHandler CResultHandler\endlink as accepted by all asynchronous calls
of the SDK (also known as `CDelegate<void (eErrorCode, const CCloudResult)>`) represents a C++ method to be called by the
SDK, unconditionally, once and only once, along with two arguments. Such a method typically has the form of the
`MyGame::SetupDone` above. You may also pass up to three additional arguments when building it with \link CloudBuilder::MakeResultHandler MakeResultHandler\endlink.
They will have to be accepted by your function after the two usual ones. The previous example could be transformed this
way if you wanted to pass an additional integer value.

~~~~{.cpp}

class MyGame
{
	void Startup()
	{
		CotCHelpers::CHJSON json;
		json.Put("key", "*****");
		json.Put("secret", "*****");
		json.Put("env", "sandbox");
		CloudBuilder::CClan::Instance()->Setup(&json, CloudBuilder::MakeResultHandler(this, &MyGame::SetupDone, 12345));
	}

	void SetupDone(CloudBuilder::eErrorCode errorCode, const CloudBuilder::CCloudResult *result, int additionalParam)
	{
		printf("Setup is done, with parameter %d\n", additionalParam);		// 12345
	}
};

~~~~

If the compiler does not accept the method passed to \link CloudBuilder::MakeResultHandler MakeResultHandler\endlink, check that the target type containing the method
matches the one of the first parameter, and that the additional parameters passed correspond to the method declaration.

You may also do much more with the delegates, please take a look at the page \ref more_advanced.

The CloudBuilder loop
===========

In the previous example, we have just seen how to parameterize to which games and servers you will connect, and that we will notify you
of the success or failure of this request through a handler that you pass to us. How, then, are we able to call your handler? It all
comes down to one line of code, that you have to call regularly. In your game loop, you could call the following code for each frame:

~~~~{.cpp}

class MyGame
{
	void Update()
	{
		// Do all the usual stuff: update world data, process input, check for collisions, ...

		CloudBuilder::CClan::Instance()->ProcessIdleTasks();
	}
};

~~~~

Just by calling this, you ensure that each time one of your requests has been processed by our servers, we will then call your handler so
you can decide what to do depending on the result of your request. Note that this function is a really lightweight process, and that no
network operation is involved. It means it can be called at a high frequency, and it will impact neither your CPU charge nor your framerate.
It does ensure though, that your requests will be processed with as little latency as possible.
This is possible because we do all the hard work for you behind the curtains. We manage threads for you, and this is completely transparent,
so you do not need to worry about it. Give us your handler, and we'll call you!

There is another aspect to consider when developing with CloudBuilder framework, which still relates to the game lifecycle. This is
especially true of the mobile platforms, but it is also the case on the desktop, and it is about managing background and foreground activity.
We need to know if the game is currently running in the foreground, or if the user has pushed it to the background. Why? This is mostly to
deal with push notifications, that our framework handles automatically for you. Everytime there is an interaction between two, or more,
players, some data are exchanged. By knowing that one or several of the recipients are in the background, we can create a push notification
which will remind them they have to check their game because something important happened. It is very easy to setup and you can configure
these push notifications as you wish by customizing them.

~~~~{.cpp}

class MyGame
{
	void GoToBackground()
	{
		// Do all the usual stuff: pause renderer and sound engine, ...

		CloudBuilder::CClan::Instance()->Suspend();
	}

	void GoToForeground()
	{
		// Do all the usual stuff: resume renderer and sound engine, ...

		CloudBuilder::CClan::Instance()->Resume();
	}
};

~~~~

The last thing to handle for the lifecycle of the game is when the user quits the game. Just like when going to the background, we need to
know the game process is finished. Not only to know that the framework has to generate push notifications if needed, but also to clean
things on the server. It is implemented just like this:

~~~~{.cpp}

class MyGame
{
	void Quit()
	{
		// Do all the usual stuff: resume renderer and sound engine, ...

		CloudBuilder::CClan::Instance()->Terminate();
	}
};

~~~~

If this is not done, this is not an issue, since after some time, our servers detect that the client does not answer anymore,
and we detach it properly. But it is always better to do it at the right time, to ensure consistency.

Next step: logging into CloudBuilder as a player
===========

Right! Now we have seen how to setup CloudBuilder, how we communicate with you, the developer, through handlers you give us,
and finally we now know how the game and our framework should interact together in order for smooth operations between your games and our
servers. So let's go a bit further in the development and let's look at the next step, the mandatory one before being able to invoke
any of our features: logging in as a player.
There are several ways to create an account with our framework. The easiest one is to use the concept of "Anonymous login", because it
does not involve any interaction with the player, and no UI is necessary. This login silently creates a new user who will then be able
to make requests to our servers. A bit of code is always good to look at! Here it is, it can not be simpler...

~~~~{.cpp}

class MyGame
{
	void CreateAnonymousLogin()
	{
		CloudBuilder::CUserManager::Instance()->LoginAnonymous(MakeResultHandler(this, &MyGame::LoginHandler));
	}

	void LoginHandler(eErrorCode aErrorCode, const CloudBuilder::CCloudResult *aResult)
	{
		//	If anonymous account creation went well, then we can dive in the data returned.
		if(aErrorCode == eErrorCode::enNoErr)
		{
			//	From the result, we get the embedded JSON, which could be displayed with a call to result->printFormatted();
			const CHJSON* json = aResult->GetJSON();

			//	Inside this JSON, we have lots of data that you can browse, for example here we'll grab profile and credentials.
			std::string id = json->GetString("gamer_id");
			std::string secret = json->GetString("gamer_secret");

			const CHJSON* profile = json->Get("profile");
			std::string name = profile->GetString("displayName");
		}
		else
			printf("Could not login due to error: %d - %s\n", aErrorCode, aResult->GetErrorString());
	}
};

~~~~

You can see we have kept two strings holding the credentials, id and secret, of the newly created account. This way, you can
store them locally on the device, and the next time the game will run, you will be able to see that an anonymous account has
already been created. This means you do not need to call LoginAnonymous again, but you can simply resume the session for this
user, with the code below. Note that the handler could be different, but it could also be the same, since our servers will
return the same data for both calls.

~~~~{.cpp}

class MyGame
{
	void ResumeSession()
	{
		CHJSON json;
		json.Put("id", "xxxxxxxxxxxxx");	//	xxxxxxxxxxxxx is the id string retrieved earlier.
		json.Put("secret", "yyyyyyyyyyyyy");	//	yyyyyyyyyyyyy is the secret string retrieved earlier.
		json.Put("env", "sandbox");
		CloudBuilder::CUserManager::Instance()->ResumeSession(&json, MakeResultHandler(this, &MyGame::LoginHandler));
	}
};

~~~~

Any data which had been saved during the first session (more on that in later tutorials), will then again be accessible.

What now?
===========

You can continue by taking a look at CloudBuilder::CClan, CloudBuilder::CUserManager and CloudBuilder::CTribeManager,
which are the three main classes needed to interact with the SDK.
