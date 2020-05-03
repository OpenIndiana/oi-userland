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
#

BUILD_BITS=64
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= redis
COMPONENT_VERSION= 6.0.1
COMPONENT_SUMMARY= Redis in-memory data structure store
COMPONENT_PROJECT_URL= https://redis.io/
COMPONENT_FMRI= database/redis
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  http://download.redis.io/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:b8756e430479edc162ba9c44dc89ac394316cd482f2dc6b91bcd5fe12593f273
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= COPYING

COMPONENT_ENV += CC="$(CC)"
COMPONENT_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV = $(COMPONENT_ENV)
COMPONENT_TEST_ENV = $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV = $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV += PREFIX=/usr

# Tests are not reliable - replica tests often fail with
# rdb child didn't terminate
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
