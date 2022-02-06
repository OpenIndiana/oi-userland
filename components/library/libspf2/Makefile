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
# Copyright 2022 Friedrich Kink
#

BUILD_BITS=		64 # for binaries or 32_and_64 for libraries

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libspf2
COMPONENT_VERSION=      1.2.10
COMPONENT_SUMMARY=      libspf2 implements the Sender Policy Framework, a part of the SPF/SRS protocol pair.
COMPONENT_PROJECT_URL=  https://www.$(COMPONENT_NAME).org
COMPONENT_FMRI=         library/libspf2
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/spf/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:d91e3de81ae287a2976c44f60283bd3000d720e6a112dc7142eedf1831b821c9
COMPONENT_LICENSE=      Copyright 2005 by Shevek and Wayne Schlitt, LGPL 2.1
COMPONENT_LICENSE_FILE= LICENSES

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# without '-m64' build will fail because of internally built 32bit objects
CONFIGURE_OPTIONS+=	"CFLAGS=-m64 -D__STDC_VERSION__=0"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
