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
# Copyright 2020 Alexander Pyhalov
# Copyright 2021 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
# Copyright 2022 Niklas Poslovski
#

BUILD_BITS= 64
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= redis
COMPONENT_VERSION= 6.2.13
COMPONENT_SUMMARY= Redis in-memory data structure store
COMPONENT_PROJECT_URL= https://redis.io/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://download.redis.io/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:89ff27c80d420456a721ccfb3beb7cc628d883c53059803513749e13214a23d1
COMPONENT_FMRI= database/redis
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= COPYING

COMPONENT_ENV += CC="$(CC)"
COMPONENT_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV = $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV = $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV += PREFIX=/usr

COMPONENT_TEST_ENV = $(COMPONENT_ENV)
# Tests are not reliable - replica tests often fail with
# rdb child didn't terminate
# Remove measured times (eg. 11 seconds:
# Remove trailing random numbers on server.

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/server\.[0-9]*.[0-9]*/server\./" ' \
	'-e "s/[0-9]* seconds//" ' \
	'-n' \
	'-e "/ok/p" ' \
	'-e "/err/p" ' \
	'-e "/exception/p" ' \
	'-e "/done/p" '

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
