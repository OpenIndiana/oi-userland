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
# Copyright (c) 2016, 2017, Wiselabs Software Ltda. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		aget
COMPONENT_VERSION=	0.4.1
COMPONENT_PROJECT_URL=	http://www.enderunix.org/aget
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d17393c7f44aab38028ae71f14b572ba1839b6e085fb2092b6ebe68bc931df4d
COMPONENT_ARCHIVE_URL=	http://www.enderunix.org/aget/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( $(CP) $(SOURCE_DIR)/Makefile.Solaris $(SOURCE_DIR)/Makefile )
COMPONENT_INSTALL_ARGS += PREFIX=$(PROTOUSRDIR)
COMPONENT_BUILD_ENV += BITS=$(BITS) CC=$(CC) CFLAGS="$(CFLAGS)"

build:		$(BUILD_64)

install:	$(INSTALL_64)

REQUIRED_PACKAGES += system/library
