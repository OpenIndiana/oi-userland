#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =        lcms
COMPONENT_VERSION=      1.19
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.littlecms.com/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha1:d5b075ccffc0068015f74f78e4bc39138bcfe2d4
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/lcms/files/lcms/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

PYTHON_VERSION = 2.6

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig
PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig

PATCH_LEVEL = 0

LIBNAME =       $(COMPONENT_NAME)
LINTOUT =       lint.out

# These aren't set by default.
PYTHON.$(PYTHON_VERSION).32 = /usr/bin/python2.6
PYTHON.$(PYTHON_VERSION).64 = /usr/bin/$(MACH64)/python2.6

PYTHONMODULEDIR_32 = /usr/lib/python$(PYTHON_VERSION)/vendor-packages
PYTHONMODULEDIR_64 = /usr/lib/python$(PYTHON_VERSION)/vendor-packages/64
PROTOPYTHONMODULE32DIR = $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages
PROTOPYTHONMODULE64DIR = $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/64
PROTOUSRINCLUDEDIR = $(PROTO_DIR)/usr/include

CFLAGS += -Xc -xnorunpath $(CC_BITS)
CFLAGS += $(studio_C99_ENABLE) $(CPP_POSIX) $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_POSIX) $(CPP_LARGEFILES) -DNDEBUG
CXXFLAGS += -mt -library=Crun -library=Cstd -compat=5
CXXFLAGS += -features=anachronisms,except,rtti,export,extensions,nestedaccess,tmplife,tmplrefstatic
CXXFLAGS += -instances=global -template=geninlinefuncs -xlang=c99
CXXFLAGS += -xbuiltin=%none -xinline=%auto
CXXFLAGS += -D_XPG5 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__=1
CXXFLAGS += $(CPP_POSIX) $(CPP_LARGEFILES) $(CC_BITS)
LDFLAGS += -lpython$(PYTHON_VERSION) -lc -lm
PYTHONPATH_32 = /usr/lib/python$(PYTHON_VERSION)
PYTHONPATH_64 = /usr/lib/$(MACH64)/python$(PYTHON_VERSION)
ELFEDIT = /usr/bin/elfedit
GSED = /usr/gnu/bin/sed
DOS2UNIX = /usr/bin/dos2unix

CONFIGURE_ENV += CXX="$(CCC)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += CCLD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CXXLD="$(CCC) $(CXXFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CXXCPP="$(CCC) $(CPPFLAGS) $(CXXFLAGS) -E"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += PYTHONPATH="$(PYTHONPATH_$(BITS))"
CONFIGURE_ENV += PYTHONMODULEDIR="$(PYTHONMODULEDIR_$(BITS))"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH_$(BITS))"

CONFIGURE_OPTIONS  +=           --includedir=/usr/include/lcms
CONFIGURE_OPTIONS  +=           --enable-shared
CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --with-jpeg
CONFIGURE_OPTIONS  +=           --with-tiff
CONFIGURE_OPTIONS  +=           --with-zlib
CONFIGURE_OPTIONS  +=           --with-python
CONFIGURE_OPTIONS  +=           --with-pic

PKG_PROTO_DIRS +=	$(COMPONENT_SRC)

COMPONENT_POST_CONFIGURE_ACTION = \
    ( cd $(@D); \
    $(CP) -p $(SOURCE_DIR)/include/lcms.h ./include/ ; \
    $(RM) -f $(SOURCE_DIR)/include/icc34.h ; \
    $(CP) -p include/icc34.h $(SOURCE_DIR)/include/ )

COMPONENT_POST_BUILD_ACTION = \
    ( cd $(@D) ; \
	$(LINT) -nsvx $(CC_BITS) -o $(LIBNAME) -I$(@D) \
	-I$(COMPONENT_DIR)/$(COMPONENT_SRC)/include \
	-I$(COMPONENT_DIR)/$(COMPONENT_SRC) \
	$(COMPONENT_DIR)/llib-l$(LIBNAME) > $(LINTOUT) 2>&1)

# We have to do this because libtool builds the C++ library with an
# incorrect RUNPATH/RPATH
COMPONENT_POST_INSTALL_ACTION = \
    ( $(ELFEDIT) -e "dyn:runpath $(USRLIBDIR)" \
	    $(PROTOPYTHONMODULE32DIR)/_lcms.so ; \
	$(ELFEDIT) -e "dyn:rpath $(USRLIBDIR)" \
	    $(PROTOPYTHONMODULE32DIR)/_lcms.so ; \
	$(ELFEDIT) -e "dyn:runpath $(USRLIBDIR64)" \
		$(PROTOPYTHONMODULE64DIR)/_lcms.so ; \
	$(ELFEDIT) -e "dyn:rpath $(USRLIBDIR64)" \
		$(PROTOPYTHONMODULE64DIR)/_lcms.so ; \
	$(DOS2UNIX) $(PROTOUSRINCLUDEDIR)/lcms/icc34.h > \
	    $(PROTOUSRINCLUDEDIR)/lcms/icc34.h.u ; \
	$(CP) -fp $(PROTOUSRINCLUDEDIR)/lcms/icc34.h.u \
	    $(PROTOUSRINCLUDEDIR)/lcms/icc34.h ; \
	$(DOS2UNIX) $(PROTOUSRINCLUDEDIR)/lcms/lcms.h > \
	    $(PROTOUSRINCLUDEDIR)/lcms/lcms.h.u ; \
	$(CP) -fp $(PROTOUSRINCLUDEDIR)/lcms/lcms.h.u \
	    $(PROTOUSRINCLUDEDIR)/lcms/lcms.h ; \
	$(RM) -f $(PROTOUSRINCLUDEDIR)/lcms/icc34.h.u \
	    $(PROTOUSRINCLUDEDIR)/lcms/lcms.h.u ; \
	$(CP) $(COMPONENT_DIR)/llib-l$(LIBNAME) $(PROTOUSRLIBDIR)/ ; \
	cd $(@D); $(INSTALL) llib-l$(LIBNAME).ln \
	    $(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS)) )

build: $(BUILD_32_and_64)

MAN1LIST = icc2ps.1 icclink.1 icctrans.1 \
	   jpegicc.1 tifficc.1 wtpt.1

include ../../make-rules/shared-targets.mk

install: $(INSTALL_32_and_64)
	$(MKDIR) $(PROTOUSRSHAREMAN1DIR) ; \
	    list1='$(MAN1LIST)'; for f in $$list1; do \
	    $(GSED) -f oracleman-stability \
		$(PROTOUSRSHAREMAN1DIR)/$$f > \
		$(PROTOUSRSHAREMAN1DIR)/$$f.sed 2>&1 ; \
	    $(CP) -fp $(PROTOUSRSHAREMAN1DIR)/$$f.sed \
		$(PROTOUSRSHAREMAN1DIR)/$$f ; \
	    $(RM) -f $(PROTOUSRSHAREMAN1DIR)/$$f.sed ; \
	    done

test: $(BUILD_32_and_64)
	@cd $(BUILD_DIR_32); $(GMAKE) check
	@cd $(BUILD_DIR_64); $(GMAKE) check

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

