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
# Copyright 2013 Adam Stevko. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libdaemon
COMPONENT_VERSION=	0.14
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:fd23eb5f6f986dcc7e708307355ba3289abe03cc381fc47a80bca4a50aa6b834
COMPONENT_PROJECT_URL=	http://0pointer.de/lennart/projects/libdaemon
COMPONENT_ARCHIVE_URL=	http://pkgs.fedoraproject.org/repo/pkgs/libdaemon/$(COMPONENT_ARCHIVE)/509dc27107c21bcd9fbf2f95f5669563/$(COMPONENT_ARCHIVE)	

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

gcc_OPT = -O2

CONFIGURE_OPTIONS += --disable-lynx
#CONFIGURE_OPTIONS += --disable-examples

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
