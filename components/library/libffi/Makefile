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
# Copyright 2011-2013, EveryCity Ltd. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libffi
COMPONENT_VERSION=	3.2.1
COMPONENT_PROJECT_URL=	http://sourceware.org/libffi/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d06ebb8e1d9a22d19e38d63fdb83954253f39bedc5d46232a05645685722ca37
COMPONENT_ARCHIVE_URL=	ftp://sourceware.org/pub/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += -DFFI_MMAP_EXEC_WRIT=1

CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--disable-raw-api

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(NO_TEST)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
