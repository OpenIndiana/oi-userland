#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
# Copyright 2016 Aurelien Larcher
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         freetype
COMPONENT_VERSION=      2.13.2
COMPONENT_SUMMARY=  	FreeType 2 font engine
COMPONENT_SRC=      	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:12991c4e55c506dd7f9b765933e62fd2be2e06d421505d7950a132e4f1bb484d
COMPONENT_ARCHIVE_URL=	https://download.savannah.gnu.org/releases/freetype/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://freetype.org/
COMPONENT_FMRI=			system/library/freetype-2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=      The FreeType Project License
COMPONENT_LICENSE_FILE= LICENSE.TXT

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-biarch-config
CONFIGURE_OPTIONS += --enable-freetype-config
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --with-bzip2
CONFIGURE_OPTIONS += --with-png
CONFIGURE_OPTIONS += --with-harfbuzz
CONFIGURE_OPTIONS += --with-pic

COMPONENT_PREP_ACTION = ( cd $(@D); \
	$(GSED) -ri 's:.*(AUX_MODULES.*valid):\1:' modules.cfg && \
	$(GSED) -r 's:.*(\#.*SUBPIXEL_RENDERING) .*:\1:' \
		-i include/freetype/config/ftoption.h ) 

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
