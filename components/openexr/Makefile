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

COMPONENT_NAME=         openexr
COMPONENT_VERSION=      1.6.1
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.openexr.com/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha1:b3650e6542f0e09daadb2d467425530bc8eec333
COMPONENT_ARCHIVE_URL=  http://download.savannah.nongnu.org/releases/openexr/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig
PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig

PATCH_LEVEL = 0

# Prevent RPATH/RUNPATH, even in ./configure. If conftest
# can't find something in the default search RUNPATH, we'd
# like to know why.
CFLAGS += -Xc -xnorunpath
CFLAGS += $(studio_C99_ENABLE) $(CPP_POSIX) $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_POSIX) $(CPP_LARGEFILES)
CXXFLAGS += $(CC_BITS) -mt -library=Crun -library=Cstd -compat=5
CXXFLAGS += -D_XPG5 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__=1
CXXFLAGS += $(CPP_POSIX) $(CPP_LARGEFILES)
LDFLAGS += -lpthread -lc -lm
LD_OPTIONS += -z ignore

CONFIGURE_ENV += CXX="$(CCC)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += CXXLINK="$(CCC) $(CXXFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CXXCPP="$(CCC) $(CPPFLAGS) $(CXXFLAGS) -E"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH_$(BITS))"

CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --enable-threading
CONFIGURE_OPTIONS  +=           --enable-posix-sem
CONFIGURE_OPTIONS  +=           --with-pic

build: $(BUILD_32_and_64)

MAN1LIST = exrenvmap.1 exrheader.1 exrmakepreview.1 \
	   exrmaketiled.1 exrstdattr.1

include ../../make-rules/shared-targets.mk

install: $(INSTALL_32_and_64)
	$(MKDIR) $(PROTOUSRSHAREMAN1DIR) ; \
	    list1='$(MAN1LIST)'; for f in $$list1; do \
	    $(INSTALL) -m 0644 Solaris/$$f $(PROTOUSRSHAREMAN1DIR)/ ; \
	    done
	$(MKDIR) $(PROTOUSRSHAREMAN3DIR) ; \
	$(INSTALL) -m 0644 Solaris/libopenexr.3lib $(PROTOUSRSHAREMAN3DIR)/

test: $(BUILD_32_and_64)
	@cd $(BUILD_DIR_32); $(GMAKE) check
	@cd $(BUILD_DIR_64); $(GMAKE) check

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

