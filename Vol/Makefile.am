# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

## $Id$

# Author:  Andreas Waechter           IBM    2006-04-13

AUTOMAKE_OPTIONS = foreign

########################################################################
#                          Subdirectories                              #
########################################################################

SUBDIRS = src

########################################################################
#             Additional files to be included in tarball               #
########################################################################

# Here we need include all files that are not mentioned in other Makefiles

EXTRA_DIST = \
	doc/ufldoc.bib \
	doc/ufldoc.ps \
	doc/ufldoc.tex \
	examples/Volume-LP/lpc.cpp \
	examples/Volume-LP/lp.h \
	examples/Volume-LP/Makefile.in \
	examples/Volume-LP/reader.cpp \
	examples/Volume-LP/lpc.h \
	examples/Volume-LP/Doc \
	examples/Volume-LP/Doc/doc.bib \
	examples/Volume-LP/Doc/doc_latex.tex \
	examples/Volume-LP/Doc/doc_latex.ps \
	examples/Volume-LP/Doc/doc_latex.dvi \
	examples/Volume-LP/data.mps.gz \
	examples/Volume-LP/reader.h \
	examples/Volume-LP/lp.cpp \
	examples/Volume-LP/lp.par \
	examples/Volume-LP/README \
	examples/VolUfl/Makefile.in \
	examples/VolUfl/doc \
	examples/VolUfl/doc/ufldoc.bib \
	examples/VolUfl/doc/ufldoc.tex \
	examples/VolUfl/doc/ufldoc.ps \
	examples/VolUfl/INSTALL \
	examples/VolUfl/ufl.cpp \
	examples/VolUfl/ufl.par \
	examples/VolUfl/data.gz \
	examples/VolUfl/ufl.hpp \
	examples/VolLp/Makefile.in \
	examples/VolLp/INSTALL \
	examples/VolLp/vollp.cpp

########################################################################
#                           Extra Targets                              #
########################################################################

test: all
	cd test; $(MAKE) test

unitTest: test

# Doxygen documentation

doxydoc:
	doxygen doxydoc/doxygen.conf

clean-doxydoc:
	( cd doxydoc ; rm -rf html *.log *.tag )

clean-local: clean-doxydoc

.PHONY: doxydoc

########################################################################
#                  Installation of the addlibs file                    #
########################################################################

pkgconfiglibdir = $(libdir)/pkgconfig
pkgconfiglib_DATA = vol.pc

if COIN_HAS_OSI
pkgconfiglib_DATA += osi-vol.pc
endif

addlibsdir = $(DESTDIR)$(datadir)/coin/doc/Vol
	
install-data-hook:
	@$(mkdir_p) "$(addlibsdir)"
if COIN_HAS_PKGCONFIG
	PKG_CONFIG_PATH=@COIN_PKG_CONFIG_PATH@ \
	$(PKG_CONFIG) --libs vol > $(addlibsdir)/vol_addlibs.txt
else
if COIN_CXX_IS_CL
	echo "-libpath:`$(CYGPATH_W) @abs_lib_dir@` libVol.lib @VOLLIB_LIBS_INSTALLED@" > $(addlibsdir)/vol_addlibs.txt
else
	echo -L@abs_lib_dir@ -lVol @VOLLIB_LIBS_INSTALLED@ > $(addlibsdir)/vol_addlibs.txt
endif
endif

uninstall-hook:
	rm -f $(addlibsdir)/vol_addlibs.txt

install-exec-local: install-doc

uninstall-local: uninstall-doc

########################################################################
#                         Maintainer Stuff                             #
########################################################################

# Files that are generated and should be cleaned with make distclean
DISTCLEANFILES =

include BuildTools/Makemain.inc
