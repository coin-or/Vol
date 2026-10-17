# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

include $(top_srcdir)/BuildTools/Makemain.inc

########################################################################
#                               libVol                                 #
########################################################################

# Name of the library compiled in this directory.
lib_LTLIBRARIES = libVol.la

# List all source files for this library, including headers
libVol_la_SOURCES = VolConfig.h VolVolume.cpp VolVolume.hpp

# List all additionally required libraries
libVol_la_LIBADD = $(VOLLIB_LFLAGS)

# Flags for the linker and preprocessor
AM_LDFLAGS = $(LT_LDFLAGS)
AM_CPPFLAGS = $(VOLLIB_CFLAGS)

########################################################################
#                Headers that need to be installed                     #
########################################################################

# Here list all the header files that are required by a user of the library,
# and that therefore should be installed in 'include/coin-or'
includecoindir = $(pkgincludedir)
includecoin_HEADERS = VolVolume.hpp

install-exec-local:
	$(install_sh_DATA) config_vol.h $(DESTDIR)$(includecoindir)/VolConfig.h

uninstall-local:
	rm -f $(DESTDIR)$(includecoindir)/VolConfig.h
