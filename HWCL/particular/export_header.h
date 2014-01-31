#pragma once

#ifdef _HOLY_HWCL_TERRITORY_
#define _HWCL_METHOD_ __declspec(dllexport)
#else
#define _HWCL_METHOD_ __declspec(dllimport)
#endif