#pragma once

#ifndef NULL
#define NULL (0)
#endif

#ifdef _HOLY_HWCL_TERRITORY_
#define _HWCL_METHOD_ __declspec(dllexport)
#else
#define _HWCL_METHOD_ __declspec(dllimport)
#endif