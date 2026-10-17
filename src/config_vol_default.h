/***************************************************************************/
/*           HERE DEFINE THE PROJECT SPECIFIC PUBLIC MACROS                */
/*    These are only in effect in a setting that doesn't use configure     */
/***************************************************************************/

/* Version number of project */
#define VOL_VERSION "devel"

/* Major Version number of project */
#define VOL_VERSION_MAJOR 9999

/* Minor Version number of project */
#define VOL_VERSION_MINOR 9999

/* Release Version number of project */
#define VOL_VERSION_RELEASE 9999

#ifndef VOLLIB_EXPORT
#if defined(_WIN32) && defined(DLL_EXPORT)
#define VOLLIB_EXPORT __declspec(dllimport)
#else
#define VOLLIB_EXPORT
#endif
#endif
