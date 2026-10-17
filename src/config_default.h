/* include the COIN-OR-wide system specific configure header */
#include "configall_system.h"

/* this needs to come before the include of config_vol_default.h */
#ifndef VOLLIB_EXPORT
#if defined(_WIN32) && defined(DLL_EXPORT)
#define VOLLIB_EXPORT __declspec(dllexport)
#else
#define VOLLIB_EXPORT
#endif
#endif

/* include the public project specific macros */
#include "config_vol_default.h"
