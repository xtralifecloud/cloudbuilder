Table of contents {#mainpage}
===========

- [Getting started](@ref sample_ref)
- [Integrating into an Android application](@ref getting_started_android_ref)
	* [Migrating an Android application from v1 or v2](@ref android_migrating_v3)
- **API reference** (showing main classes; open [class list](annotated.html) for a comprehensive reference)
	- @ref CloudBuilder.CClan "The CClan main object": allows to perform basic tasks. Required in any application.
	- @ref CloudBuilder.CUserManager "The CUserManager object": allows to perform a login, and interact with user-related data.
	- @ref CloudBuilder.CTribeManager "The CTribeManager object": tasks related to the community around the current user.
	- @ref CloudBuilder.CGameManager "The CGameManager object": tasks revolving around the whole game (regardless of the current user).
	- @ref CloudBuilder.CIndexManager "The CIndexManager object": offers a powerful store for quickly indexing and looking up various data in your game.
	- @ref CloudBuilder.CFilesystemManager "The CFilesystemManager object": a platform-independent file system.
	- [The CotCHelpers namespace](@ref CotCHelpers) provides utilitary classes that are used within the SDK but may as well be shared in your projects.
- [Working with user related data](@ref user_related_data)
- [Setting up for Facebook](@ref facebook_ref)
- [Setting up for Google+](@ref googleplus_ref)
- [Working with achievements](@ref achievements)
- [Working with matches](@ref matches)
- [Offering in-app purchases](@ref store)
- [Mastering additional components](@ref more_advanced)
- [Push Notification Settings](@ref push_ref)
- [ChangeLog](#changes)

- - - - 

# Changes Log {#changes}

## Version 3.00

Please read the *Modified* section carefully, as it lists changes you may need to bring to your code.

Removed:
- Unity support at all. Either use an older version of CloudBuilder or switch to the whole new Unity-SDK available at https://github.com/clanofthecloud/unity-sdk.

Modified:
- All new integration with Google Cloud Messaging for smoother push notifications. The whole integration changes though, so read carefully in order to migrate.
- The #CotCHelpers::CHJSON::print and #CotCHelpers::CHJSON::printFormatted as well as #CloudBuilder::CCloudResult::Print methods now return a #CotCHelpers::cstring instead of a `char*`. It means that you do not need to free the associated string (it is carried on by the `cstring` instance and freed once it becomes out of scope). This is explained more in detail in the [Mastering additional components](@ref pretty_print_json) section.
- Various bug fixes.

Added:
- Logging improvements: can now call CloudBuilder.setVerboseLog and CClan::SetLogLevel to set logging levels.

## Version 2.99

New features:
- Login function to social networks no longer embed authentication screen. It's up to the developer to do it, then pass ID and token to CotC Login function.

## Version 2.8.8

New features:
	- Android builds now include all 64 bit versions (ARM, Intel).

Changes:
	- iOS builds now link and embed newest version of GooglePlayServices.


## Version 2.8.4

New features:
	- A hook was added when a referral operation takes place.
	- Leaderboard score posting operation has been added to batch command.

Changes:
	- Optimization of the thread management inside CloudBuilder.

Bug fixes:
	- In Android, permission for Facebook friends was not requested. Now done, so list of friends can be retrieved again.

## Version 2.8.3

New features:
	- Unity ships now 64 bits build on Mac OS X. Mandatory for Unity 5 compatibility.
	- CloudBuilder on Android now comes with native x86 build.

Changes:
	- Documentation now includes a section on how managing user's information.

Bug fixes:
	- More bugs have been removed from Store Manager and InApp module.

## Version 2.8.2

New features:
	- SampleUnity has been totally revamped and is much easier to use on Android.

Changes:
	- The most recent Facebook SDKs are now used (3.23.0).

## Version 2.8.1

New features:
	- CClan::Ping and CUser::ChangeEmail were missing in Unity wrapper.

Bug fixes:
	- Fix a crash in CStore::FetchProductInformation when products list was not configured.

## Version 2.8.0

New features:
	- InApp transactions added, see CloudBuilder::CStoreManager class.
	- It is now possible to call scripts uploaded to the servers, through the CloudBuilder::CUserManager::Batch method.

## Version 2.6.0

New features:
	- Asynchronous multiplayer module added, see CloudBuilder::CMatchManager class.
	- Domain management has been generalized, extending to leaderboards, achievements, properties, matches and more. Many methods were changed, especially in CloudBuilder::CGameManager.
	- New methods to work on a single property rather than all the properties at the same time.

Changes:
	- In the Unity wrapper, it is now possible to have different delegates depending on the key used to write some data.
	- When two identical scores are sent, they are sorted with the timestamp to ensure an order in the leaderboard.

Bug fixes:
	- When a user is erased in development environment, its scores are also erased in leaderboard.
	- CloudBuilder::CGameManager::GetRank is now working. Return "not implemented" before.

## Version 2.4.1

New features:
	- CloudBuilder::CUserManager::ChangePassword was added.

## Version 2.4.0

New features:
	- CloudBuilder::CUserManager and CloudBuilder::CGameManager now can delete Key/Values entries by using the KeyValueDelete methods.
	- Added CloudBuilder::CUserManager::MailPassword to generate a shortcode when a user lost his password.

Bug fixes:
	- Unlink method now calls delegate in Unity wrapper.
	- It is now possible to link an account to Facebook and publish something just after.

## Version 2.2.0

New features:
	- Achievements are now available in the CloudBuilder.

Changes:
	- On iOS, the Facebook link now uses the "native" Facebook module, not the Facebook SDK, which works better for publications.
	- The godfather module now has more options and is more flexible.
	- When calling CloudBuilder::CUserManager::Publish, if the user cancels the publication, the SDK does not return an error code anymore. It returns a valid return code, but the JSON returned has an entry with "done" set to zero, indicating that the story was not published because the user decided so.

Bug fixes:
	- CloudBuilder::CUserManager::UserExist can now be called if no user is logged in.
	- Some friends method sometimes did not call delegates.

## Version 2.0.0

Brand new version.
