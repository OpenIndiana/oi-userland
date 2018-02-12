#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013, Jon Tibble.
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         jq
COMPONENT_VERSION=      1.5
COMPONENT_SUMMARY=      jq - lightweight and flexible command-line JSON processor
COMPONENT_PROJECT_URL=	https://stedolan.github.io/jq/
COMPONENT_FMRI=         text/jq
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:c4d2bfec6436341113419debf479d833692cc5cdab7eb0326b5a4d4fbe9f493c
COMPONENT_ARCHIVE_URL=	\
  https://github.com/stedolan/jq/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Tests are broken out of source
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += CFLAGS="$(CFLAGS) $(CPP_XPG6MODE)"

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-valgrind

COMPONENT_TEST_CMD = ./tests/jqtest
COMPONENT_TEST_TARGETS = 

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-e "/^==/d" '

build:   $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test:    $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
