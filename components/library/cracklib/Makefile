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
# Copyright (c) 2015 Alexander Pyhalov
#

BUILD_BITS=			32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cracklib
COMPONENT_VERSION=	2.9.7
COMPONENT_PROJECT_URL=	https://github.com/cracklib/cracklib
COMPONENT_SUMMARY=	CrackLib Library and Dictionaries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:fe82098509e4d60377b998662facf058dc405864a8947956718857dbb4bc35e6
COMPONENT_ARCHIVE_URL=	https://github.com/cracklib/cracklib/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/security/cracklib
COMPONENT_LICENSE_FILE=	COPYING.LIB
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_CLASSIFICATION=	System/Libraries

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -D_POSIX_PTHREAD_SEMANTICS

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --without-python

$(BUILD_DIR)/.dicts:	$(INSTALL_32) $(INSTALL_64)
	$(ENV) PATH=$(PROTO_DIR)/usr/sbin:$(PATH) $(MAKE) -C $(BUILD_DIR_32) dict-local DESTDIR=$(PROTO_DIR)
	$(TOUCH) $@

# common targets
install:	$(INSTALL_32_and_64)	$(BUILD_DIR)/.dicts

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
