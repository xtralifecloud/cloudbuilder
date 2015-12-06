//
//  CloudbuilderClient.h
//  CloudBuilder
//
//  Created by roland on 24/10/12.
//  Copyright (c) 2012 Clan of the Cloud. All rights reserved.
//

#ifndef __CloudBuilder__CloudbuilderClient__
#define __CloudBuilder__CloudbuilderClient__

#include "CloudBuilder.h"

namespace CloudBuilder {
	
	int invoke_api(const char *aCommunityKey, const char *aCommunitySecret, const char *aEnv, void(*console)(const char *));
	
}

#endif /* defined(__CloudBuilder__CloudbuilderClient__) */
