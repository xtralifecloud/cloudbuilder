Migrating Android apps to v3.00 {#android_migrating_v3}
===========

Along with version 3.00, the Android integration has changed a lot and has been streamlined. It is now much easier to integrate and is now oriented toward Android Studio instead of the Eclipse development environment which is not supported anymore by Google.

For now, support for native code in Android Studio is still so-so. Therefore we recommend that you keep implementing and debugging your C++ from other development environments such as Visual Studio for Windows or Xcode for Mac.

Basically, you need to:
- Update your main activity to reflect changes. Basically remove everything related to CloudBuilder and start over with the tutorial [here](@ref getting_started_android). It should not take long but we recommend that you follow the steps carefully.
- Update the GCM (push notifications) if you are using them. Here too, it should not take long, especially since all the server configuration has already been made. Remove your custom class extending CloudBuilder or its functionality related to handling push notifications, and start over with the tutorial [here](@ref toc_push_2).
- Additionally, you may need to bring modifications in the backoffice as well, as described [here](@ref toc_push_2).
