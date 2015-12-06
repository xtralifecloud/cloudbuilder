/**
 * Copyright 2015 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.clanofthecloud.cloudbuilder.pushnotifications;

import android.app.IntentService;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;

import com.clanofthecloud.cloudbuilder.CloudBuilder;
import com.clanofthecloud.cloudbuilder.EErrorCode;
import com.clanofthecloud.cloudbuilder.iab.IabHelper;
import com.google.android.gms.gcm.GcmPubSub;
import com.google.android.gms.gcm.GoogleCloudMessaging;
import com.google.android.gms.iid.InstanceID;

import org.json.JSONObject;

import java.io.IOException;

public class RegistrationIntentService extends IntentService {

	static final String UNREGISTER_PARAM = "unregister";
    private static final String TAG = "RegIntentService";
    private static final String[] TOPICS = {"global"};
    private static String registrationToken;
    // Calls
    private static IabHelper.CloudResultListener handlerCalledWhenRegistrationTokenReceived;

    public RegistrationIntentService() {
        super(TAG);
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        try {
            // In the (unlikely) event that multiple refresh operations occur simultaneously,
            // ensure that they are processed sequentially.
            synchronized (TAG) {
                // [START register_for_gcm]
                // Initially this call goes out to the network to retrieve the token, subsequent calls
                // are local.
                // [START get_token]
                InstanceID instanceID = InstanceID.getInstance(this);
                ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
                Object senderId = ai.metaData.get("cotc.GcmSenderId");
                if (senderId == null) {
                    Log.e(TAG, "!!!!!!!!! cotc.GcmSenderId not configured in manifest, push notifications won't work !!!!!!!!!");
                    senderId = "";
                }
	            if (CloudBuilder.sVerboseLog) Log.v(TAG, "Using senderId: " + senderId.toString());
                String token = instanceID.getToken(senderId.toString(),
                        GoogleCloudMessaging.INSTANCE_ID_SCOPE, null);
                // [END get_token]
	            if (CloudBuilder.sVerboseLog) Log.v(TAG, "GCM Registration Token: " + token);

                registrationToken = token;

                // Subscribe to topic channels
                if (intent.getBooleanExtra(UNREGISTER_PARAM, false)) {
                    unsubscribeTopics(token);
                } else {
                    subscribeTopics(token);
                }
                // [END register_for_gcm]

                // Call handler
                if (handlerCalledWhenRegistrationTokenReceived != null) {
                    JSONObject obj = new JSONObject();
                    obj.put("token", token);
                    handlerCalledWhenRegistrationTokenReceived.onDone(EErrorCode.enNoErr, obj, null);
                }
            }
        } catch (Exception e) {
            Log.w(TAG, "Failed to complete token refresh", e);
            // If an exception happens while fetching the new token or updating our registration data
            // on a third-party server, this ensures that we'll attempt the update at a later time.
//            sharedPreferences.edit().putBoolean(QuickstartPreferences.SENT_TOKEN_TO_SERVER, false).apply();
        }
        // Notify UI that registration has completed, so the progress indicator can be hidden.
        Intent registrationComplete = new Intent(Controller.REGISTRATION_COMPLETE);
        LocalBroadcastManager.getInstance(this).sendBroadcast(registrationComplete);
    }

    public static String getRegistrationToken() {
        return registrationToken;
    }

    /**
     * Sets a handler to be called when the registration token is obtained from Google.
     * @param handler handler to call.
     */
    public static void setRegistrationTokenHandler(IabHelper.CloudResultListener handler) {
        handlerCalledWhenRegistrationTokenReceived = handler;
    }

    /**
     * Subscribe to any GCM topics of interest, as defined by the TOPICS constant.
     *
     * @param token GCM token
     * @throws IOException if unable to reach the GCM PubSub service
     */
    // [START subscribe_topics]
    private void subscribeTopics(String token) throws IOException {
        for (String topic : TOPICS) {
            GcmPubSub pubSub = GcmPubSub.getInstance(this);
            pubSub.subscribe(token, "/topics/" + topic, null);
        }
	    if (CloudBuilder.sVerboseLog) Log.v(TAG, "Registered topics");
    }
    private void unsubscribeTopics(String token) throws IOException {
        for (String topic : TOPICS) {
            GcmPubSub pubSub = GcmPubSub.getInstance(this);
            pubSub.unsubscribe(token, "/topics/" + topic);
        }
	    if (CloudBuilder.sVerboseLog) Log.v(TAG, "Unregistered topics");
    }
    // [END subscribe_topics]

}
