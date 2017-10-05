//
//  CIndexManager.cpp
//  CloudBuilder
//
//  Created by Florian Bronnimann on 11/06/15.
//  Copyright (c) 2015 Clan of the Cloud. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "CloudBuilder_private.h"
#include "CClan.h"
#include "CIndexManager.h"
#include "CClannishRESTProxy.h"

using namespace CotCHelpers;

namespace CloudBuilder {
	
	static singleton_holder<CIndexManager> managerSingleton;

	CIndexManager::CIndexManager() {
	}
	
	CIndexManager::~CIndexManager() {
	}

	CIndexManager *CIndexManager::Instance() {
		return managerSingleton.Instance();
	}

	void CIndexManager::Terminate() {
		managerSingleton.Release();
	}

	void CIndexManager::DeleteObject(const CotCHelpers::CHJSON *aConfiguration, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); }

		CClannishRESTProxy::Instance()->DeleteIndexedObject(aConfiguration, MakeBridgeDelegate(aHandler));
	}

	void CIndexManager::FetchObject(const CotCHelpers::CHJSON *aConfiguration, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); }

		CClannishRESTProxy::Instance()->GetIndexedObject(aConfiguration, MakeBridgeDelegate(aHandler));
	}

	void CIndexManager::IndexObject(const CotCHelpers::CHJSON *aConfiguration, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); }

		CClannishRESTProxy::Instance()->IndexObject(aConfiguration, MakeBridgeDelegate(aHandler));
	}

	void CIndexManager::Search(const CotCHelpers::CHJSON *aConfiguration, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); }

		CClannishRESTProxy::Instance()->SearchIndexedObjects(aConfiguration, MakeBridgeDelegate(aHandler));
	}
}

