//
//  GameCenterHandler.h
//  CloudBuilder
//
//  Created by florian on 07/10/14.
//  Copyright (c) 2014 Clan of the Cloud. All rights reserved.
//
//  Allows to perform related to the Game Center. Works on iOS only, any attempt to use these
//  features on other platforms will silently fail with an enNotImplemed error code.
//

#ifndef CloudBuilder_GameCenterHandler_h
#define CloudBuilder_GameCenterHandler_h

namespace CloudBuilder {

	namespace GameCenter {
		/**
		 * Tries to connect through the Game Center. Returns data associated to the user account that
		 * can further be passed to the CotC backend.
		 * Resulting fields in the JSON:
		 * - playerid: unique player identifier (to be treated as an opaque token)
		 * - alias: the alias of the player (https://developer.apple.com/library/mac/documentation/GameKit/Reference/GKPlayer_Ref/Reference/Reference.html#//apple_ref/occ/instp/GKPlayer/alias)
		 * - nickname: the display name of the player
		 * - underage: whether the player is declared underage by Apple
		 */
		void login(CInternalResultHandler *handler);
		/**
		 * Takes Game Center specific steps to log out the current player.
		 */
		void logout(CInternalResultHandler *handler);
		/**
		 * Lists friends associated with the current player.
		 * Resulting fields in the JSON:
		 * - players [array of player data; see login(CInternalResultHandler*)]
		 */
		void listFriends(CInternalResultHandler *handler);
	}
	
}

#endif
