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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cracklib
COMPONENT_VERSION=	2.9.6
COMPONENT_PROJECT_URL=	https://github.com/cracklib/cracklib
COMPONENT_SUMMARY=	CrackLib Library and Dictionaries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:17cf76943de272fd579ed831a1fd85339b393f8d00bf9e0d17c91e972f583343
COMPONENT_ARCHIVE_URL=	https://github.com/cracklib/cracklib/releases/download/cracklib-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/security/cracklib
COMPONENT_LICENSE_FILE=	COPYING.LIB
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_CLASSIFICATION=	System/Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CFLAGS += -D_POSIX_PTHREAD_SEMANTICS

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --without-python

$(BUILD_DIR)/.dicts:	$(INSTALL_32) $(INSTALL_64)
	$(ENV) PATH=$(PROTO_DIR)/usr/sbin:$(PATH) $(MAKE) -C $(BUILD_DIR_32) dict-local DESTDIR=$(PROTO_DIR)
	$(TOUCH) $@

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)	$(BUILD_DIR)/.dicts

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
