/*
 * This file is part of MicroCLI.
 *
 * Copyright (C) 2012 Christian Jann <christian.jann@ymail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.clanofthecloud.cli;

import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.StrictMode;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.EditorInfo;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.clanofthecloud.cloudbuilder.CloudBuilder;
import com.clanofthecloud.cloudbuilder.GooglePlayStoreHandler;

/**
 * This is the main Activity
 */
public class MicroConsole extends Activity
{
    // Debugging
    private static final String TAG = "MicroConsole";
    private static final boolean D = true;

	IntentFilter gcmFilter;

    private static MicroConsole self = null;
    // Layout Views
    private ListView    mConsoleView;
    private EditText    mOutEditText;
    private Button      mSendButton;

    ProgressDialog dialog;

    // Array adapter for the console log
    private ArrayAdapter<String> mConversationArrayAdapter;

    private List<String> mCommandsArray;
    private int mCurrCmd = -1;
    private static boolean hasAlreadyFinishedOperation;

    // String buffer for outgoing messages
    private StringBuffer mOutStringBuffer;

	//	We need a timer and handler to call the CotC_Update() function regularly.
	private Timer cloudBuilderTimer = null;
	private Handler cloudBuilderHandler = null;

	//	We register the 2 .so needed to run the sample.
	static  {
		System.loadLibrary("CloudBuilder");
		System.loadLibrary("AndroidCLI");
	}

	//	The 2 bridges to the 2 C++ functions we need to call.
	public native void CloudBuilderSetupJNIBridge();
	public native void CloudBuilderUpdateJNIBridge();
	public native int  CLIExecute(String cmd);

	public static void WriteMessage(String result)
	{
		self.write(result);
	}

	public static void StopWait(String result)
	{
		self.stopWait();
	}

	public void stopWait()
	{
		if (dialog != null) { dialog.hide(); dialog = null; }
	}


	@Override
    public void onCreate(Bundle savedInstanceState)
    {
//    	GCMIntentService.Init(this);
        CloudBuilder.Init(this);

    	super.onCreate(savedInstanceState);
        if (D) Log.e(TAG, "+++ ON CREATE +++");

        self = this;

        mCommandsArray = new ArrayList<String>();

        // Set up the window layout
        setContentView(R.layout.main);

        // Disable the restriction for using Networking on main thread
        // http://stackoverflow.com/questions/12529994/networking-issues-on-honeycomb-and-higher
        if (android.os.Build.VERSION.SDK_INT > 9)
        {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
            StrictMode.setThreadPolicy(policy);
        }

        //	First, we setup the environment by calling into C++.
        cloudBuilderHandler = new Handler();
        CloudBuilderSetupJNIBridge();

        //	Then we immediately instantiate a timer (100ms) which will regularly
        //	poll to check if new notifications are pending.

        cloudBuilderTimer	= new Timer("CloudBuilderTimer");
        cloudBuilderTimer.schedule(new CloudBuilderUpdateTask(), 0, 100);

        dialog = null;

	    GooglePlayStoreHandler.InitGooglePlayStore(this);
    }

/*	private final BroadcastReceiver gcmReceiver = new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {
        	GCMIntentService.HandleNotification(intent);
        }
    };*/

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }

    public void onStart()
    {
        super.onStart();
        if (D) Log.e(TAG, "++ ON START ++");
        setupConsole();
    }

    @Override
    public synchronized void onResume()
    {
        super.onResume();
        if (D) Log.e(TAG, "+ ON RESUME +");
//        registerReceiver(gcmReceiver, gcmFilter);
        CloudBuilder.Resumed();
//        CloudBuilder.HandleNotification(null);
        if (dialog != null) { dialog.hide(); dialog = null;}
    }

    private void setupConsole()
    {
        Log.d(TAG, "setupConsole()");

        // Initialize the array adapter for the console log
        mConversationArrayAdapter = new ArrayAdapter<String>(this, R.layout.message);
        mConsoleView = (ListView) findViewById(R.id.in);
        mConsoleView.setAdapter(mConversationArrayAdapter);
        mConsoleView.setOnItemClickListener(new OnItemClickListener() {
    	   @Override
    	   public void onItemClick(AdapterView<?> adapter, View view, int position, long arg) {
    	      recallHistory(adapter.getItemAtPosition(position).toString());
    	   }
    	});
        fillPresetHistoryCommands(mConversationArrayAdapter);

        // Initialize the compose field with a listener for the return key
        mOutEditText = (EditText) findViewById(R.id.edit_text_out);
        mOutEditText.setOnEditorActionListener(mWriteListener);
        mOutEditText.requestFocus();

        // Initialize the send button with a listener that for click events
        mSendButton = (Button) findViewById(R.id.button_send);
        mSendButton.setOnClickListener(new OnClickListener()
        {
            public void onClick(View v)
            {
            	MicroConsole.this.sendButtonClicked();
            }
        });

        // Initialize the buffer for outgoing messages
        if (mOutStringBuffer == null)
            mOutStringBuffer = new StringBuffer("");
    }

    public synchronized void onPause()
    {
        super.onPause();
        if (D) Log.e(TAG, "- ON PAUSE -");
        CloudBuilder.Suspended();
//        unregisterReceiver(gcmReceiver);
        if (dialog != null) { dialog.hide(); dialog = null;}
   }

    public void onStop()
    {
        super.onStop();
        if (D) Log.e(TAG, "-- ON STOP --");
    }

    public void onDestroy()
    {
        super.onDestroy();
        if (D) Log.e(TAG, "--- ON DESTROY ---");
        // Stop the ConnectionService
    }

    public void write(String message)
    {
        mConversationArrayAdapter.add(message);
    }

    private void fillPresetHistoryCommands(ArrayAdapter<String> conversationArrayAdapter) {
    	conversationArrayAdapter.add("> cmd 3");
        conversationArrayAdapter.add("> loginanonymous");
        conversationArrayAdapter.add("> loginwith facebook");
        conversationArrayAdapter.add("> friendsof facebook");
        conversationArrayAdapter.add("> loginwith googleplus");
        conversationArrayAdapter.add("> friendsof googleplus");
	}

    private void recallHistory(String historyLine) {
    	if (historyLine.startsWith("> ")) {
            String line = historyLine.substring(2);
            mOutEditText.setText(line);
            mOutEditText.setSelection(line.length());
    	} else {
        	Toast.makeText(getApplicationContext(), "Click on a command to recall it", Toast.LENGTH_SHORT).show();
    	}
    }

    public void sendButtonClicked() {
        if (D) Log.e(TAG, "[sendButton clicked]");
        // Send a message using content of the edit text widget
        TextView view = (TextView) findViewById(R.id.edit_text_out);
        String message = view.getText().toString();
        sendMessage(message);
    }

    /**
     * Sends a message.
     * @param message  A string of text to send.
     */
    private void sendMessage(String message)
    {
        // Check that there's actually something to send
        if (message.length() > 0)
        {
            try
            {
                // Reset out string buffer to zero and clear the edit text field
                mOutStringBuffer.setLength(0);
                mOutEditText.setText("");
                mCommandsArray.add(message.replaceAll("\\r\\n", ""));
                mCurrCmd = mCommandsArray.size()-1;
                mConversationArrayAdapter.add("> " + message.replaceAll("\\r\\n", ""));
                synchronized (MicroConsole.this) { hasAlreadyFinishedOperation = true; }
                int err = CLIExecute(message.replaceAll("\\r\\n", ""));
                synchronized (MicroConsole.this) {
	                if (err == 0 && !hasAlreadyFinishedOperation)
	                {
	//                	Toast.makeText(getApplicationContext(), "waiting...",Toast.LENGTH_SHORT).show();
	                	dialog = new ProgressDialog(this);
	                	dialog.setMessage("Connecting to CloudBuilder...");
	                	dialog.setIndeterminate(true);
	                	dialog.setCancelable(false);
	                	dialog.show();
	                }
	                else if (err != -1 && err != 0)
	                	Toast.makeText(getApplicationContext(), "ERROR !",Toast.LENGTH_SHORT).show();
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
        }
    }

    // The action listener for the EditText widget, to listen for the return key
    private TextView.OnEditorActionListener mWriteListener =
        new TextView.OnEditorActionListener()
    {
        public boolean onEditorAction(TextView view, int actionId, KeyEvent event)
        {
            // If the action is a key-up event on the return key, send the message
            if (actionId == EditorInfo.IME_NULL && event.getAction() == KeyEvent.ACTION_UP)
            {
                String message = view.getText().toString();
                sendMessage(message);
            }
            // Click on the Done button
            if (actionId == EditorInfo.IME_ACTION_DONE || (event != null && event.getKeyCode() == KeyEvent.KEYCODE_ENTER))
            {
                MicroConsole.this.sendButtonClicked();
            }
            if (D) Log.i(TAG, "END onEditorAction");
            return true;
        }
    };

    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if (D) Log.d(TAG, "onActivityResult " + requestCode + " " +resultCode);
	    // Required for the In-app Billing (CStoreManager).
	    GooglePlayStoreHandler.HandleActivityResult(requestCode, resultCode, data);

    	switch (requestCode)
        {
        case 0:
            break;

        }// end switch
    }

    public boolean onCreateOptionsMenu(Menu menu)
    {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu, menu);
        return true;
    }

    public boolean onOptionsItemSelected(MenuItem item)
    {
        switch (item.getItemId())
        {
        case R.id.option1:
            sendMessage("setup cloudbuilder DEV 10.0.1.201");
            return true;
        case R.id.option2:
//            sendMessage("setup cloudbuilder DEV 192.168.90.7");
            sendMessage("invitefb 100005995985880");
            return true;
        case R.id.option3:
            // "Previous Cmd"
        	if (mCurrCmd !=-1 && mCommandsArray.size() > 0 )
        	{
                mOutEditText.setText(mCommandsArray.get(mCurrCmd));
                mCurrCmd--; if (mCurrCmd<0) mCurrCmd = 0;
        	}
            return true;
        case R.id.option4:
        	// "Next Cmd"
        	if (mCurrCmd !=-1 && mCurrCmd < mCommandsArray.size())
        	{
                mOutEditText.setText(mCommandsArray.get(mCurrCmd));
                mCurrCmd++; if (mCurrCmd>=mCommandsArray.size()) mCurrCmd = mCommandsArray.size()-1;
        	}
            return true;
        }

        return false;
    }

    //	The timer will just call into C++ and ensure that incoming notifications
    //	are processed.
    private class CloudBuilderUpdateTask extends TimerTask {

		@Override
		public void run() {
			cloudBuilderHandler.post(new Runnable() {

				public void run() {
					// TODO Auto-generated method stub
					CloudBuilderUpdateJNIBridge();

				}

			});
		}
    }
}