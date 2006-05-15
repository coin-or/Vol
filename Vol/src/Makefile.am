# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Common Public License.

## $Id$

# Author:  Andreas Waechter           IBM    2006-04-13

AUTOMAKE_OPTIONS = foreign

########################################################################
#                               libClp                                 #
########################################################################

# Name of the library compiled in this directory.  We want it to be installed
# in the 'lib' directory
lib_LTLIBRARIES = libVol.la

# List all source files for this library, including headers
libVol_la_SOURCES = VolVolume.cpp VolVolume.hpp

# This is for libtool (on Windows)
libVol_la_LDFLAGS = -no-undefined

########################################################################
#                            Additional flags                          #
########################################################################


# Here list all include flags, relative to this "srcdir" directory.  This
# "cygpath" stuff is necessary to compile with native compilers on Windows.
# "top_srcdir" refers to the basic directory for the main package that is
# being compiled.
CXXFLAGS += \
	-I`$(CYGPATH_W) $(COINUTILSSRCDIR)/src`

########################################################################
#                Headers that need to be installed                     #
########################################################################

# Here list all the header files that are required by a user of the library,
# and that therefore should be installed in 'install'
include_HEADERS = VolVolume.hpp

########################################################################
#     Generating the configure header that is to be distributed        #
########################################################################

# You should only need to adapt the following three lines
CONFIG_DIST = VolConfig.hpp
CONFIG_H = config_vol.h
$(libVol_la_OBJECTS): ../inc/$(CONFIG_DIST)

nodist_include_HEADERS = ../inc/$(CONFIG_DIST)

../inc/$(CONFIG_DIST): ../inc/$(CONFIG_H)
	echo "/** Required defines from $(CONFIG_H) */" >bla.tmp
	echo "#ifndef __$(CONFIG_DIST)__" | sed -e 's/\./_/g' >>bla.tmp
	echo "#define __$(CONFIG_DIST)__" | sed -e 's/\./_/g' >>bla.tmp
	$(EGREP) 'COIN_' $< >>bla.tmp
	echo "#endif" >>bla.tmp
	if test -r ../inc/$(CONFIG_DIST); then \
	  if diff ../inc/$(CONFIG_DIST) bla.tmp >/dev/null 2>&1 ; then \
	    rm -f bla.tmp; \
	  else \
	    rm -f ../inc/$(CONFIG_DIST); \
	    mv bla.tmp ../inc/$(CONFIG_DIST); \
	  fi; \
	else \
	  mv bla.tmp ../inc/$(CONFIG_DIST); \
	fi

CLEANFILES = bla.tmp

DISTCLEANFILES = ../inc/$(CONFIG_DIST)
