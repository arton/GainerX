
#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

#include <queue>
#include <string>

#ifndef COUNT_OF
#define COUNT_OF(x) (sizeof(x)/sizeof(x[0]))
#endif

using namespace ATL;
