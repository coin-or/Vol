# Copyright (C) 2006 International Business Machines.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

## $Id$

# Author:  Andreas Waechter            IBM    2006-04-13

#############################################################################
#                       Names and other basic things                        #
#############################################################################

AC_PREREQ(2.59)

AC_INIT([Vol],[1.3.2],[coin-vol@list.coin-or.org])

AC_COPYRIGHT([
Copyright 2006 International Business Machines and others.
All Rights Reserved.
This file is part of the open source package Coin which is distributed
under the Eclipse Public License.])

# List one file in the package so that the configure script can test
# whether the package is actually there
AC_CONFIG_SRCDIR(src/VolVolume.cpp)

# Where should everything be installed by default?  Here, we want it
# to be installed directly in 'bin', 'lib', 'include' subdirectories
# of the directory where configure is run.  The default would be
# /usr/local.
AC_PREFIX_DEFAULT([`pwd`])

#############################################################################
#                         Standard build tool stuff                         #
#############################################################################

# Get the system type
AC_CANONICAL_BUILD

# If this project depends on external projects, the Externals file in
# the source root directory contains definition of where to find those
# externals.  The following macro ensures that those externals are
# retrieved by svn if they are not there yet.
AC_COIN_PROJECTDIR_INIT(Vol,4:2:3)

# Check if user wants to produce debugging code
AC_COIN_DEBUG_COMPILE(Vol)

# Get the name of the C++ compiler and appropriate compiler options
AC_COIN_PROG_CXX

# Initialize automake and libtool
AC_COIN_INIT_AUTO_TOOLS

#############################################################################
#                              COIN components                              #
#############################################################################

AC_COIN_CHECK_PACKAGE(CoinUtils, [coinutils],     [VolLib])
AC_COIN_CHECK_PACKAGE(Osi,       [osi],           [OsiVolLib])
AC_COIN_CHECK_PACKAGE(OsiTests,  [osi-unittests])
AC_COIN_CHECK_PACKAGE(Sample,    [coindatasample])

##############################################################################
#                   VPATH links for example input files                      #
##############################################################################

# In case this is a VPATH configuration we need to make sure that the
# input files for the examples are available in the VPATH directory.

AC_COIN_VPATH_LINK(examples/VolUfl/ufl.par)
AC_COIN_VPATH_LINK(examples/VolUfl/data.gz)
AC_COIN_VPATH_LINK(examples/Volume-LP/data.mps.gz)
AC_COIN_VPATH_LINK(examples/Volume-LP/lp.par)

# Setup doxygen
AC_COIN_DOXYGEN(CoinUtils Osi)

##############################################################################
#                   Finishing up by writing all the output                   #
##############################################################################

# Here list all the files that configure should create (except for the
# configuration header file)
AC_CONFIG_FILES([Makefile
		 examples/VolLp/Makefile
		 examples/VolUfl/Makefile
		 examples/Volume-LP/Makefile
                 src/Makefile
                 src/OsiVol/Makefile
                 test/Makefile
                 doxydoc/doxygen.conf
		 vol.pc vol-uninstalled.pc])

if test $coin_has_osi = yes ; then
  AC_CONFIG_FILES([osi-vol.pc:src/OsiVol/osi-vol.pc.in
                   osi-vol-uninstalled.pc:src/OsiVol/osi-vol-uninstalled.pc.in])
fi

# even though we do not use the config_vol.h file, we config a header file here
# this is for the compilation of OsiVol, which works much better with -DHAVE_CONFIG_H
# instead of a list of single defines (-DPACKAGE_NAME=...) in the compiler flags
AC_CONFIG_HEADER([inc/config_vol.h])

# Finally, we let configure write all the output...
AC_COIN_FINALIZE
