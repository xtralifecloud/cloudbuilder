//
//  CGameManager.h
//  CloudBuilder
//
//  Created by Roland Van Leeuwen on 10/04/12.
//  Copyright (c) 2012 Clan of the Cloud. All rights reserved.
//

#ifndef CloudBuilder_CGameManager_h
#define CloudBuilder_CGameManager_h

#include "CloudBuilder.h"
#include "CotCHelpers.h"

/*! \file CGameManager.h
 */

namespace CloudBuilder
{
	class CClan;
	class CCloudResult;

	/** The CGameManager class is helpful when you want to store global data for your
		application. These data will be accessible to all users who have installed and
		are using this application. It can be useful for introducing new levels, new
		assets, or anything that you wish to add to the application in future updates.
		It also provides helper methods to store and retrieve high scores.
	*/
	class FACTORY_CLS CGameManager {
	public:

		/**
			* Use this method to obtain a reference to the CGameManager.
			* @return the one and only instance of this manager
		*/
		static CGameManager *Instance();
		
		/** Method used to post a High Score for this application.
            @param aHandler result handler whenever the call finishes (it might also be synchronous)
			@param  aHighScore is the score you want to post.
			@param  aMode is a C string holding the game mode for which this score should be
			considered.
			@param	aScoreType string with "hightolow" or "lowtohigh"
			@param  aInfoScore is an optional string wich describe the score
			@param  aForce is an optional boolean used in case we authorize the new high score
			to be inferior to the previous one.
            @param  aDomain is the domain in which the score has to be pushed. "private" means it's
            local to this game only.
			@result if noErr, the json passed to the handler may contain: @code
			"done" : 1,
			"rank" : 123 @endcode
			`done` means that the score has been recorded as the highest, while `rank` is the effective rank
			of the player (returned even if the player has not actually been classed, that is if `done` is 0).
		*/
		void Score(CResultHandler *aHandler, long long aHighScore, const char *aMode, const char *aScoreType, const char *aInfoScore, bool aForce, const char *aDomain="private");

		/** Method used to retrieve the rank of a High Score for this application.
            @param aHandler result handler whenever the call finishes (it might also be synchronous)
			@param  aHighScore is the score whose rank you want to retrieve.
			@param  aMode is a C string holding the game mode for which you want to retrieve
			rank for this score.
            @param  aDomain is the domain in which the rank has to be retrieved. "private" means it's
            local to this game only.
			@result if noErr, the json passed to the handler may contain:
			 "rank" : 1
		*/
		void GetRank(CResultHandler *aHandler, long long aHighScore, const char *aMode, const char *aDomain="private");

		/** Method used to retrieve the best High Scores for this application.
            @param aHandler result handler whenever the call finishes (it might also be synchronous)
			@param  aCount is the number of best scores you want to retrieve, default is 10
			@param  aPage is the number of the page to retrieve. the default is 1
			@param  aMode is a C string holding the game mode for which you want to retrieve
			the best High Scores.
            @param  aDomain is the domain in which the best scores have to be retrieved. "private"
            means it's local to this game only.
			@result if noErr, the json passed to the handler may contain:
			{ <aMode>: {
				"maxpage" : 10,
				"rankOfFirst" : 1,
				"page" : 1,
				"scores" : []
			}
		*/
		void BestHighScore(CResultHandler *aHandler, int aCount, int aPage, const char *aMode, const char *aDomain="private");
		
		/** Method used to retrieve scores centered on the user score for this application.
            @param aHandler result handler whenever the call finishes (it might also be synchronous)
			@param  aCount is the number of best scores you want to retrieve, default is 10
			@param  aMode is a C string holding the game mode for which you want to retrieve
			the best High Scores.
            @param  aDomain is the domain in which the best scores have to be retrieved. "private"
            means it's local to this game only.
			@result if noErr, the json passed to the handler may contain:
			{ <aMode>: {
				"maxpage" : 10,
				"rankOfFirst" : 1,
				"page" : 1,
				"scores" : []
			}
		*/
		void CenteredScore(CResultHandler *aHandler, int aCount, const char *aMode, const char *aDomain="private");
		
		/** Method used to retrieve the best Scores of the logged user.
			@param aHandler result handler whenever the call finishes (it might also be synchronous)
            @param  aDomain is the domain in which the best scores have to be retrieved. "private"
            means it's local to this game only.
			@result if noErr, the json passed to the handler may contain list of :
			<modes>:	{
			"timestamp":	"2014-09-12T15:30:56.938Z",
			"score":	100,
			"info":	"some text",
			"order":	"lowtohigh",
			"rank":	3
			}
		 */
		void UserBestScores(CResultHandler *aHandler, const char *aDomain="private");

		/**
			Method to read a single key of the global JSON object stored for this game and domain.
			@param aConfiguration is a JSON configuration, that may contain
			- domain: the domain on which the action is to be taken (if not passed, the private domain is used)
			- key: name of the key to retrieve from the global JSON object (if not passed, all keys are returned)
			@param aHandler result handler whenever the call finishes (it might also be synchronous)
			@result if noErr and no binary key was passed in the configuration, the json passed to the handler may contain:
			{
				"<key1>" : "value1", "<key2>" : "value2", …
			}
			Note: if the key was entered as a string in the backoffice (rather than stored as an object), then the key
			"value" encloses the string data, not parsed as a JSON. You can do so by using CHJSON::parse.
		 */
		void KeyValueRead(const CotCHelpers::CHJSON *aConfiguration, CResultHandler *aHandler);
		
		/**
            Method to write a single key of the global JSON object stored for this user and domain.
            @param aConfiguration is a JSON configuration, that may contain
            - domain: the domain on which the action is to be taken (if not passed, the private domain is used)
            - key: name of the key to delete from the global JSON object. BEWARE: if you omit the key, ALL entries
            will be deleted!
            @param aHandler result handler whenever the call finishes (it might also be synchronous)
            @result if noErr and no binary key was passed in the configuration, the json passed to the handler may contain:
            {
                "done": 1
            }
		 void KeyValueWrite(const CotCHelpers::CHJSON *aConfiguration, CResultHandler *aHandler);
		 For security raison this method has been removed, please use the Backoffice to do this
		 */
		
		/**
			Method to delete a single key of the global JSON object stored for this game and domain.
			@param aConfiguration is a JSON configuration, that may contain
			- domain: the domain on which the action is to be taken (if not passed, the private domain is used)
            - key: name of the key to delete from the global JSON object. BEWARE: if you omit the key, ALL entries
            will be deleted!
			@param aHandler result handler whenever the call finishes (it might also be synchronous)
			@result if noErr, the json passed to the handler may contain:
			{
				"done": 1
			}
		 void KeyValueDelete(const CotCHelpers::CHJSON *aConfiguration, CResultHandler *aHandler);
		 For security raison this method has been removed, please use the Backoffice to do this
		 */

		/**
			 Method to read a single key containing binary data stored for this domain.
			 @param aConfiguration JSON allowing for extensible configuration, that may contain:
			 - domain: the domain on which the action is to be taken (if not passed, the private domain is used)
			 - key: name of the key to retrieve
			 @param aHandler result handler whenever the call finishes (it might also be synchronous)
			 @result if noErr, the json passed to the handler may contain:
			 {
			 "url" : "<signed URL>",
			 }
			 CCloudResult.HasBinary() must be true and you can acces to the data through :
		 */
		void BinaryRead(const CotCHelpers::CHJSON *aConfiguration, CResultHandler *aHandler);
		
		/**
			
			 Method to insert or modify a single key represented by binary data
			 @param aConfiguration JSON allowing for extensible configuration, that may contain:
			 - domain: the domain on which the action is to be taken (if not passed, the private domain is used)
			 - key: name of the key to retrieve
			 @param aPointer is the binary array you want to save.
			 @param aSize is the size of the binary array, in bytes.
			 @param aHandler result handler whenever the call finishes (it might also be synchronous)
			 @result if noErr, the json passed to the handler may contain:
			 {
			 "url" : "<signed URL>",
			 }
		void BinaryWrite(const CotCHelpers::CHJSON *aConfiguration, const void *aPointer, size_t aSize, CResultHandler *aHandler);
		For security raison this method has been removed, please use the Backoffice to do this
		*/
		 
		/**
		 Method to remove data pointed by a single key.
		 @param aConfiguration JSON allowing for extensible configuration, that may contain:
		 - domain: the domain on which the action is to be taken (if not passed, the private domain is used)
		 - key: name of the key to delete
		 @param aHandler result handler whenever the call finishes (it might also be synchronous)
		 @result if noErr, the json passed to the handler may contain:
		 {
		 "done" : 1,
		 }
		void BinaryDelete(const CHJSON *aConfiguration, CResultHandler *aHandler);
		For security raison this method has been removed, please use the Backoffice to do this
		*/

		/**
		 * Run a batch on the server side.
		 * Batch is edited on BackOffice server.
		 * @param aConfiguration JSON data describing the dat to pass to the batch
		 	- domain: the domain on which the action is to be taken (if not passed, the private domain is used)
		 	- name: the name identifying the batch
		 * @param aParameters JSON data describing the data to pass to the batch
			- input: user defined data
		 * @param aHandler the handler called with the result when the call completes
		 * @result if noErr, the json passed to the handler will contain the result of the executed batch
		 */
		void Batch(CResultHandler *aHandler, const CotCHelpers::CHJSON *aConfiguration, const CotCHelpers::CHJSON *aParameters);

	private:
		/**
		 * Not publicly instantiable/subclassable. Use Instance().
		 */
		CGameManager();
		~CGameManager();
		/**
		 * You need to call this in CClan::Terminate().
		 */
		void Terminate();

		void binaryWriteDone(const CCloudResult *result, const void *, size_t, CResultHandler *);
		void binaryReadDone(const CCloudResult *result, CResultHandler *aHandler);

		friend class CClan;
		friend struct singleton_holder<CGameManager>;
	};
	
}


#endif
