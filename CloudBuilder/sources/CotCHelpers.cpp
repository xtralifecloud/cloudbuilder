//
//  CotCHelpers.cpp
//  CloudBuilder
//
//  Created by Roland Van Leeuwen on 04/05/12.
//  Copyright (c) 2012 Clan of the Cloud. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "CotCHelpers.h"
#include "cJSON.h"

namespace CotCHelpers {
	
	void Init(void)
	{
		static bool sInitDone = false;

		if(!sInitDone)
		{
			srand((unsigned int) time(0));
//			cJSON_InitHooks(NULL);

			sInitDone	= true;
		}
	
	}

	CRefClass::~CRefClass() {
#ifndef COTC_DISABLE_EXCEPTIONS
		if ((int) __ref_count > 0) throw "Freeing an object that is still retained elsewhere";
#endif
	}
}
