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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cracklib
COMPONENT_VERSION=	2.9.11
COMPONENT_SUMMARY=	CrackLib Library and Dictionaries
COMPONENT_PROJECT_URL=	https://github.com/cracklib/cracklib
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:ca8b049a3c2d3b2225a1e8d15d613798ebc748e3950388eda2694de507ba6020
COMPONENT_ARCHIVE_URL=	https://github.com/cracklib/cracklib/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/security/cracklib
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING.LIB

TEST_TARGET= $(NO_TESTS)
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
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
