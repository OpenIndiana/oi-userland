#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Stephan Althaus
#

BUILD_BITS=		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         codeblocks
COMPONENT_VERSION_MAJOR =      20
COMPONENT_VERSION_MINOR =      3
COMPONENT_VERSION=      20.03
COMPONENT_FMRI=         editor/codeblocks
COMPONENT_CLASSIFICATION=   Applications/Accessories
COMPONENT_PROJECT_URL=  https://sourceforge.net/projects/codeblocks/
COMPONENT_SUMMARY=      Code::BLocks IDE
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=  https://nav.dl.sourceforge.net/project/codeblocks/Sources/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
sha256:9c62817d65b1cbdd926438ea9f0647ca9c3a1e04e1b144fc87bde95f016f091c
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING

# IPS Package versions contain sequences of non-negative (for now) integers,
# separated by dots.  Leading zeroes are not allowed, due to ordering
# ambiguity, so IPS team has to massage "03" into "3" 
# and thus IPS version of codeblocks is actually 2.6 and not 2.06. 
# IPS_COMPONENT_VERSION is by default set to $(COMPONENT_VERSION)
# but in this case it has to be set specifically
# to "20.3" to comply with the convention described above.
#
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)

CXXFLAGS += -fpermissive 
CFLAGS += -fpermissive 

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

#CONFIGURE_OPTIONS += --with-wx-config=/usr/bin/wx-config-2.8
CONFIGURE_OPTIONS += --with-wx-config=/usr/bin/amd64/wx-config-3.1
#CONFIGURE_OPTIONS += --disable-pch

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/graphics/wxwidgets-3
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math

