# Copyright (C) 2006 International Business Machines.
# All Rights Reserved.
# This file is distributed under the Common Public License.

## $Id$

# Author:  Andreas Waechter            IBM    2006-04-13

#############################################################################
#                       Names and other basic things                        #
#############################################################################

AC_PREREQ(2.59)

AC_INIT([Vol],[trunk],[coin-vol@list.coin-or.org])

AC_COPYRIGHT([
Copyright 2006 International Business Machines and others.
All Rights Reserved.
This file is part of the open source package Coin which is distributed
under the Common Public License.])

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
AC_COIN_PROJECTDIR_INIT(Vol)

# Check if user wants to produce debugging code
AC_COIN_DEBUG_COMPILE(Vol)

# Get the name of the C++ compiler and appropriate compiler options
AC_COIN_PROG_CXX

# Initialize automake and libtool
AC_COIN_INIT_AUTO_TOOLS

#############################################################################
#                              COIN components                              #
#############################################################################

AC_COIN_HAS_MODULE(CoinUtils, [coinutils = trunk])
if test $coin_has_coinutils != yes ; then
  #if we have to use the fallback routines, then obviously it will not find CoinUtils dependencies
  #thus, we check whether ThirdParty/Blas and ThirdParty/Lapack have been setup and
  #assume that if present then they are dependencies of CoinUtils
  AC_COIN_HAS_MODULE_FALLBACK(Blas,   [coinblas],   [../ThirdParty/Blas],   [required=0 dodefine=0 doconditional=0])
  AC_COIN_HAS_MODULE_FALLBACK(Lapack, [coinlapack], [../ThirdParty/Lapack], [required=0 dodefine=0 doconditional=0])
fi
AC_COIN_HAS_MODULE_FALLBACK(CoinUtils, [coinutils], [../CoinUtils])
if test $coin_has_coinutils != yes ; then
  AC_MSG_ERROR([Required package CoinUtils not available.])
fi
#so if we had to do find Blas and Lapack separately, then add their linker flags to the CoinUtils flags
#actually the libs may already be included in libCoinUtils, but we may still need the fortran library flags
COINUTILS_LIBS="$COINUTILS_LIBS $LAPACK_LIBS $BLAS_LIBS"

AC_COIN_HAS_MODULE(Osi,      [osi],            [required=0], [../Osi])
AC_COIN_HAS_MODULE(OsiTests, [osi-unittests],  [required=0], [../Osi])
AC_COIN_HAS_MODULE(Sample,   [coindatasample], [required=0], [../Data/Sample])
AC_COIN_HAS_MODULE(Netlib,   [coindatanetlib], [required=0], [../Data/Netlib])

##############################################################################
#                   VPATH links for example input files                      #
##############################################################################

# In case this is a VPATH configuration we need to make sure that the
# input files for the examples are available in the VPATH directory.

AC_COIN_VPATH_LINK(examples/VolUfl/ufl.par)
AC_COIN_VPATH_LINK(examples/VolUfl/data.gz)
AC_COIN_VPATH_LINK(examples/Volume-LP/data.mps.gz)
AC_COIN_VPATH_LINK(examples/Volume-LP/lp.par)

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
		 vol.pc vol-uninstalled.pc])

if test $coin_has_osi = yes ; then
  AC_CONFIG_FILES([src/OsiVol/osi-vol.pc
                   osi-vol-uninstalled.pc:src/OsiVol/osi-vol-uninstalled.pc.in])
fi

# even though we do not use the config_vol.h file, we config a header file here
# this is for the compilation of OsiVol, which works much better with -DHAVE_CONFIG_H
# instead of a list of single defines (-DPACKAGE_NAME=...) in the compiler flags
AC_CONFIG_HEADER([inc/config_vol.h])

# Finally, we let configure write all the output...
AC_COIN_FINALIZE
