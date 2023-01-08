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
# Copyright 2022 Niklas Poslovski
#

USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         sqlcipher
COMPONENT_VERSION=      4.5.3
COMPONENT_SUMMARY=      SQLite extension that provides transparent 256-bit AES encryption of database
COMPONENT_PROJECT_URL=  https://www.zetetic.net/sqlcipher/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:5c9d672eba6be4d05a9a8170f70170e537ae735a09c3de444a8ad629b595d5e2
COMPONENT_FMRI=         database/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=       Development/Databases
COMPONENT_LICENSE=      BSD

CFLAGS += -DSQLITE_HAS_CODEC
LDFLAGS += -L$(OPENSSL_LIBDIR)

CONFIGURE_OPTIONS += --enable-tempstore=yes
CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_LIBDIR)
CONFIGURE_OPTIONS += CPPFLAGS=-I$(OPENSSL_INCDIR)

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
