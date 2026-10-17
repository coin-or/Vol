# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

include $(top_srcdir)/BuildTools/Makemain.inc

########################################################################
#                             libOsiVol                                #
########################################################################

# Name of the library compiled in this directory.
lib_LTLIBRARIES = libOsiVol.la

# List all source files for this library, including headers
libOsiVol_la_SOURCES = \
	OsiVolConfig.h \
	OsiVolSolverInterface.cpp OsiVolSolverInterface.hpp \
	OsiVolSolverInterfaceIO.cpp

# List all additionally required libraries
libOsiVol_la_LIBADD = $(OSIVOLLIB_LFLAGS) ../libVol.la

# Flags for the linker and preprocessor
AM_LDFLAGS = $(LT_LDFLAGS)
AM_CPPFLAGS = -I$(srcdir)/.. -I.. $(OSIVOLLIB_CFLAGS)

########################################################################
#                Headers that need to be installed                     #
########################################################################

# Here list all the header files that are required by a user of the library,
# and that therefore should be installed in 'include/coin-or'
includecoindir = $(pkgincludedir)
includecoin_HEADERS = OsiVolSolverInterface.hpp

install-exec-local:
	$(install_sh_DATA) config_osivol.h $(DESTDIR)$(includecoindir)/OsiVolConfig.h

uninstall-local:
	rm -f $(DESTDIR)$(includecoindir)/OsiVolConfig.h
