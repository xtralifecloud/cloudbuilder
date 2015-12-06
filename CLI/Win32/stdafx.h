// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <CommCtrl.h>
#include "Richedit.h"

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>
#include <map>
#include <memory>
#include <vector>
using std::map;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

#define numberof(o) (sizeof(o) / sizeof(*(o)))
