Working with user related data {#user_related_data}
===========

When working on your new game, one of the first things you will want to do is saving some information about this user. By using Clan of the Cloud APIs for storing information, it will be available from any of the devices this user will use to log in with his Clan of the Cloud profile. You can ensure this way that your players will enjoy the same experience, and this also acts a backup in case a device is lost. Storing some user's information in the cloud is possible with Clan of the Cloud APIs of course, but you have many different ways to achieve this. We will detail below the possibilities that are available to the developer, and will explain when to use them, since some APIs are better suited depending on what you want to save.

- **User Profile**<br>
This section of information is unique, global, and very limited. It's something you will not use on a regular basis. The user's profile is shared between all games, from all companies using Clan of the Cloud. Because of this, it only contains data which are really private to the player, like his name, e-mail, address, and other private data that he agreed to provide. Because any game can, at any time, modify all or part of this profile, you should not expect it to store data pertaining to your game(s).<br>
The authorized fields supported in the profile are the following ones: "email", "displayName", "lang", "firstName", "lastName", "addr1", "addr2", "addr3" and "avatar". Note that all corresponding values have to be strings.<br>
Let's see some code to help you retrieve and modify a user's profile, provided this user is already logged on with any of the available profiles. Note that when modifying a user profile, it is not mandatory to send all the keys at once. You can send only one key, or a subset, or all of them.

~~~~{.cpp}

class MyGame {
    void ReadUserProfile() {
        CloudBuilder::CUserManager::Instance()->GetProfile(CloudBuilder::MakeResultHandler(this, &MyGame::ReadUserProfileDone));
    }
    void WriteUserProfile() {
        CloudBuilder::CHJSON* json = new CloudBuilder::CHJSON;
        json->Put("displayName", "My user display name");
        json->Put("lang", "fr");
        CloudBuilder::CUserManager::Instance()->SetProfile(json, CloudBuilder::MakeResultHandler(this, &MyGame::WriteUserProfileDone));
        delete json;
    }
    void ReadUserProfileDone(CloudBuilder::eErrorCode aErrorCode, const CloudBuilder::CCloudResult *aResultGetProfile) {
        if (aErrorCode == CloudBuilder::enNoErr)
            printf("The profile display name is %s\n", aResultGetProfile->GetJSON()->GetString("displayName"));
        else
            printf("GetProfile failed with message %s!\n", aResultGetProfile->GetErrorString());
     }
    void WriteUserProfileDone(CloudBuilder::eErrorCode aErrorCode, const CloudBuilder::CCloudResult *aResultSetProfile) {
        if (aErrorCode == CloudBuilder::enNoErr)
            printf("Profile modified\n");
        else
            printf("SetProfile failed with message %s!\n", aResultSetProfile->GetErrorString());
    }
};

~~~~

- **Key/Value**<br>

The most flexible way to store any kind of information for your users is to use the key/value storing feature provided. Each user has a dedicated set of keys and values, that you are free to manage as you wish. There is no restriction, so you can at any time add, modify or remove any keys. It's entirely up to the developer to manage this storage, and Clan of the Cloud will not interfere with it.<br>
Note that you have two options for using this feature. If you don't pass a domain when accessing your keys, then everything will be local to your game. However, if you pass a domain previously created from your 'CloudBuilder Manager' (https://account.clanofthecloud.com/#/share), then your whole set of keys and values will be accessible from all applications which share this domain.<br>
This means first that you theoretically have an unlimited number of sets of keys and values. Then also, be sure when using domains, to make matching Read and Write calls in the same domain, or otherwise you will not be able to read some previously written data in another domain!<br>
Also, if you ignore the "key" entry in your JSON configuration when writing some information, be aware that you are replacing all the existing keys for this user. This option should be used with great care, and only under precise circumstances, or you may lose all the data for your user! In the same way, but without the dramatic consequences, not passing "key" when reading information, you will be returned the whole set of keys associated to this user.<br>
In the following samples, the information stored for a given key is a simple string. However, it could be a whole JSON if you need so. If this were the case, you'd have to adapt the read operation for such a key in order to handle the result as a JSON object, and not as a string.

~~~~{.cpp}

class MyGame {
    void ReadDataFromKey(const char* aKey) {
        CloudBuilder::CHJSON* json = new CloudBuilder::CHJSON;
        //  Not filling in the "domain" entry implicitly means we want to retrieve from the "private" domain.
        json->Put("key", aKey);
        CloudBuilder::CUserManager::Instance()->KeyValueRead(json, CloudBuilder::MakeResultHandler(this, &MyGame::ReadDataFromKeyDone));
        delete json;
    }
    void WriteDataWithKey(const char* aKey, const char* aValue) {
        CloudBuilder::CHJSON* json = new CloudBuilder::CHJSON;
        //  Not filling in the "domain" entry implicitly means we want to retrieve from the "private" domain.
        json->Put("key", aKey);
        json->Put("data", aValue);
        CloudBuilder::CUserManager::Instance()->KeyValueWrite(json, CloudBuilder::MakeResultHandler(this, &MyGame::WriteDataWithKeyDone));
        delete json;
    }
    void ReadDataFromKeyDone(CloudBuilder::eErrorCode aErrorCode, const CloudBuilder::CCloudResult *aResultReadDataFromKey) {
        if (aErrorCode == CloudBuilder::enNoErr)
            printf("Value is %s\n", aResultReadDataFromKey->GetJSON()->GetString("value"));
        else
            printf("Read operation failed with message %s!\n", aResultReadDataFromKey->GetErrorString());
    }
    void WriteDataWithKeyDone(CloudBuilder::eErrorCode aErrorCode, const CloudBuilder::CCloudResult *aResultWriteDataWithKey) {
        if (aErrorCode == CloudBuilder::enNoErr)
            printf("Write operation succeeded\n");
        else
            printf("Write operation failed with message %s!\n", aResultWriteDataWithKey->GetErrorString());
    }
};

~~~~

- **User Properties**<br>

There is another way to manage player's informations. For generic purposes and complex data, you should use Key/Value as described above. However, if you want to store very simple information like bool, string and number, you can use the User Properties APIs. Specifically, they are mandatory to use when you want to implement match making into your game. It's here that you will store properties which have to be matched against other players' properties so we can return you some possible opponents. But nothing prevents you from using it also for storing other bits of information, if they are trivial, which might never be used for match making (since in match making, it's up to the developer to build the query that will return possible opponents).<br>
Just like with Key/Value APIs, User Properties belong to a domain. Not filling in the domain entry when working with properties means that you want to access it in the default, private domain of the game. If it is the case, then these properties will not be shared amongst different games.

~~~~{.cpp}

class MyGame {
    void GetProperty(const char* aProperty) {
        //  Not filling in the "domain" entry implicitly means we want to retrieve from the "private" domain.
        CloudBuilder::CUserManager::Instance()->GetProperty(CloudBuilder::MakeResultHandler(this, &MyGame::GetPropertyDone), aProperty);
    }
    void SetProperty(const char* aKey, const char* aValue) {
        CloudBuilder::CHJSON* json = new CloudBuilder::CHJSON;
        //  Not passing the domain parameter implicitly means we want to retrieve from the "private" domain.
        json->Put(aKey, aValue);
        CloudBuilder::CUserManager::Instance()->SetProperty(CloudBuilder::MakeResultHandler(this, &MyGame::SetPropertyDone), json);
        delete json;
    }
    void GetPropertyDone(CloudBuilder::eErrorCode aErrorCode, const CloudBuilder::CCloudResult *aResultGetProperty)
    {
        if (aErrorCode == CloudBuilder::enNoErr) {
            CHJSON* property = aResultGetProperty->GetJSON()->Get("properties");
            printf("Property Level is %d\n", property->GetString("Level"));
        }
        else
            printf("Property retrieval failed with message %s!\n", aResultGetProperty->GetErrorString());
    }
    void SetPropertyDone(CloudBuilder::eErrorCode aErrorCode, const CloudBuilder::CCloudResult *aResultSetProperty)
    {
        if (aErrorCode == CloudBuilder::enNoErr)
            printf("SetProperty succeeded\n");
        else
            printf("SetProperty failed with message %s!\n", aResultSetProperty->GetErrorString());
    }
};

~~~~
