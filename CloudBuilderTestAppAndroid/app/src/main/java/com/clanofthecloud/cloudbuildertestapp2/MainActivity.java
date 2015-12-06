package com.clanofthecloud.cloudbuildertestapp2;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.StrictMode;
import android.view.View;

import com.clanofthecloud.cloudbuilder.CloudBuilder;
import com.clanofthecloud.cloudbuilder.GooglePlayStoreHandler;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends Activity {
	// The timer will just call into C++ and ensure that incoming notifications are processed.
	private class CloudBuilderUpdateTask extends TimerTask {
		@Override
		public void run() {
			cloudBuilderHandler.post(new Runnable() {
				public void run() { CloudBuilderUpdateJNIBridge(); }
			});
		}
	}

	static  {
		System.loadLibrary("CloudBuilder");
		System.loadLibrary("MyAppNative");
	}

	//	We need a timer and handler to call the CotC_Update() function regularly.
	private Timer cloudBuilderTimer = null;
	private Handler cloudBuilderHandler = null;

	//	The 2 bridges to the 2 C++ functions we need to call.
	public native void CloudBuilderSetupJNIBridge();
	public native void CloudBuilderUpdateJNIBridge();
	public native void DoLoginNatively();
	public native void DoLogoutNatively();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		// Init the library
		CloudBuilder.Init(this);

		// Disable the restriction for using Networking on main thread
		// http://stackoverflow.com/questions/12529994/networking-issues-on-honeycomb-and-higher
		if (android.os.Build.VERSION.SDK_INT > 9) {
			StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
			StrictMode.setThreadPolicy(policy);
		}

		// Setup the environment by calling into C++.
		cloudBuilderHandler = new Handler();
		CloudBuilderSetupJNIBridge();

		// Then we immediately instantiate a timer (100ms) which will regularly
		// poll to check if new notifications are pending.
		cloudBuilderTimer = new Timer("CloudBuilderTimer");
		cloudBuilderTimer.schedule(new CloudBuilderUpdateTask(), 0, 100);

		// If you are going to use the store, you nee that as well
		GooglePlayStoreHandler.InitGooglePlayStore(this);
	}

	@Override
	public synchronized void onPause() {
		super.onPause();
		CloudBuilder.Suspended();
	}

	@Override
	public synchronized void onResume() {
		super.onResume();
		CloudBuilder.Resumed();
	}

	public void clickedOnLogin(View button) {
		DoLoginNatively();
	}
	public void clickedOnLogout(View button) {
		DoLogoutNatively();
	}
}
