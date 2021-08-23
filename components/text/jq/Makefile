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
# Copyright 2020, Nona Hansel.
# Copyright 2021, Till Wegmueller.
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         jq
COMPONENT_VERSION=      1.6
COMPONENT_REVISION= 	1
COMPONENT_SUMMARY=      jq - lightweight and flexible command-line JSON processor
COMPONENT_PROJECT_URL=	https://stedolan.github.io/jq/
COMPONENT_FMRI=         text/jq
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:5de8c8e29aaa3fb9cc6b47bb27299f271354ebb72514e3accadc7d38b5bbaa72
COMPONENT_ARCHIVE_URL=	\
  https://github.com/stedolan/jq/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT

include $(WS_MAKE_RULES)/common.mk

# Tests are broken out of source
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D); cd $(@D))
#COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D); cd $(@D); autoreconf -fi)

CONFIGURE_ENV += CFLAGS="$(CFLAGS) $(CPP_XPG6MODE)"

CONFIGURE_OPTIONS += --disable-valgrind
CONFIGURE_OPTIONS += --with-oniguruma=/usr

COMPONENT_TEST_CMD = ./tests/jqtest
COMPONENT_TEST_TARGETS = 

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-e "/^==/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/oniguruma

