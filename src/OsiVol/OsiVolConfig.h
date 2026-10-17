/* Copyright (C) 2020
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * Include file for the configuration of OsiVol.
 *
 * On systems where the code is configured with the configure script
 * (i.e., compilation is always done with HAVE_CONFIG_H defined), this
 * header file includes the automatically generated header file.
 *
 * On systems that are compiled in other ways (e.g., with the
 * Developer Studio), the export attribute is defined here.
 */

#ifndef __OSIVOLCONFIG_H__
#define __OSIVOLCONFIG_H__

#ifdef HAVE_CONFIG_H
#ifdef OSIVOLLIB_BUILD

#ifdef DLL_EXPORT
# define OSIVOLLIB_EXPORT __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define OSIVOLLIB_EXPORT __attribute__((__visibility__("default")))
#else
# define OSIVOLLIB_EXPORT
#endif

#else
#include "config_osivol.h"
#endif

#else /* HAVE_CONFIG_H */

#ifndef OSIVOLLIB_EXPORT
# if defined(_WIN32) && defined(DLL_EXPORT)
#  ifdef OSIVOLLIB_BUILD
#   define OSIVOLLIB_EXPORT __declspec(dllexport)
#  else
#   define OSIVOLLIB_EXPORT __declspec(dllimport)
#  endif
# elif defined(__GNUC__) && __GNUC__ >= 4
#  define OSIVOLLIB_EXPORT __attribute__((__visibility__("default")))
# else
#  define OSIVOLLIB_EXPORT
# endif
#endif

#endif /* HAVE_CONFIG_H */

#endif /*__OSIVOLCONFIG_H__*/
