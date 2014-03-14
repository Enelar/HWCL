#pragma once

#ifndef NULL
#define NULL (0)
#endif

#ifdef _HOLY_HWCL_TERRITORY_
#define _HWCL_METHOD_ __declspec(dllexport)
#undef CPP11_SUPPORTED
#define CPP11_SUPPORTED 1
#else
#define _HWCL_METHOD_ __declspec(dllimport)
#endif

#define _MEMLEAK_DETECT_ENABLED
#include "../../AX/source/ax/def.h"
