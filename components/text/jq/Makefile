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

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         jq
COMPONENT_VERSION=      1.7
COMPONENT_SUMMARY=      jq - lightweight and flexible command-line JSON processor
COMPONENT_PROJECT_URL=	https://stedolan.github.io/jq/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:402a0d6975d946e6f4e484d1a84320414a0ff8eb6cf49d2c11d144d4d344db62
COMPONENT_ARCHIVE_URL=	https://github.com/stedolan/jq/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         text/jq
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

ELFEDIT = /usr/bin/elfedit

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -fiv )

# Tests are broken out of source
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D); cd $(@D))

# Remove the RUNPATH otherwise it will be set to somewhere inside PROTO_DIR
COMPONENT_POST_INSTALL_ACTION += $(ELFEDIT) -e "dyn:runpath ''" $(PROTOUSRBINDIR)/jq ;

CONFIGURE_ENV += CFLAGS="$(CFLAGS) $(XPG6MODE)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS) $(XPG6MODE) -DNDEBUG=1"

CONFIGURE_OPTIONS += --disable-dependency-tracking
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-valgrind
CONFIGURE_OPTIONS += --with-oniguruma=/usr

COMPONENT_TEST_CMD = ./tests/jqtest
COMPONENT_TEST_TARGETS = 

COMPONENT_TEST_TRANSFORMS += \
        '-e "/^==/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/oniguruma
