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

BUILD_STYLE= justmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= redis
COMPONENT_VERSION= 8.6.1
COMPONENT_SUMMARY= Redis in-memory data structure store
COMPONENT_PROJECT_URL= https://redis.io/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://download.redis.io/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:6873fc933eeb7018aa329e868beac7228695f50c0d46f236a4ff1a6d7f7bb5b6
COMPONENT_FMRI= database/redis
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

#CFLAGS += $(XPG6MODE)

COMPONENT_ENV += PATH="$(PATH.illumos)"
COMPONENT_ENV += CC="$(CC)"
COMPONENT_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV = $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV = $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV += PREFIX=/usr

COMPONENT_TEST_ENV = $(COMPONENT_ENV)
# Tests are not reliable - replica tests often fail with rdb child didn't terminate

# By default ignore all lines
JUSTMAKE_TEST_TRANSFORMS += "-n"
# remove time of running
JUSTMAKE_TEST_TRANSFORMS += "-e 's/(.*)//'"
JUSTMAKE_TEST_TRANSFORMS += "-e '/ok\]/p'"
JUSTMAKE_TEST_TRANSFORMS += "-e '/err\]/p'"
JUSTMAKE_TEST_TRANSFORMS += "-e '/WARNING/p'"

# Sort test results
JUSTMAKE_TEST_TRANSFORMS += "| ( \
	$(GSED) -u -e '/^\$$/Q' | $(SORT) | $(COMPONENT_TEST_TRANSFORMER) -e '\$$G' ; \
	$(CAT) \
    ) | $(COMPONENT_TEST_TRANSFORMER) -e ''"

USE_DEFAULT_TEST_TRANSFORMS?=no
ifeq ($(strip $(USE_DEFAULT_TEST_TRANSFORMS)),yes)
COMPONENT_TEST_TRANSFORMS+= $(JUSTMAKE_TEST_TRANSFORMS)
endif

# Manually added dependencies
TEST_REQUIRED_PACKAGES += runtime/tcl-8

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
