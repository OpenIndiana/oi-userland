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
# Copyright 2025 Jiwon Na
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           m17n-lib
COMPONENT_VERSION=        1.8.5
COMPONENT_SUMMARY=        m17n-lib - The m17n library is to support various aspects (e.g. input methods, layout engines) of multi-lingual text processing.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:7b6c425f792d06d14e4f5b17204d3627e2c8ebb423ebdae92c0c646710d3d6c7
COMPONENT_ARCHIVE_URL=    https://download.savannah.nongnu.org/releases/m17n/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           system/input-method/library/m17n
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        LGPLv2.1
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://www.nongnu.org/m17n/

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/input-method/library/libanthy
REQUIRED_PACKAGES += system/input-method/library/libthai
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
