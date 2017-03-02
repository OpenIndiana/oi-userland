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
# Copyright 2011, 2013, EveryCity Ltd. All rights reserved.
# Copyright 2013 David Hoeppner. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mhash
COMPONENT_VERSION=	0.9.9.9
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://mhash.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3dcad09a63b6f1f634e64168dd398e9feb9925560f9b671ce52283a79604d13e
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION += \
	(cd $(SOURCE_DIR); \
	rm -f Makefile config.guess config.h config.sub config.status; \
	./buildconf; \
	$(CLONEY) $(SOURCE_DIR) $(@D);)	\

CONFIGURE_OPTIONS  +=	--enable-shared
CONFIGURE_OPTIONS  +=	--disable-static
CONFIGURE_OPTIONS  +=	--with-pic


build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
