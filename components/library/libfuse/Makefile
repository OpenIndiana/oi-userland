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
# Copyright 2016 Adam Stevko. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libfuse
COMPONENT_VERSION= 	20100615
IPS_COMPONENT_VERSION=	2.7.6
COMPONENT_REVISION=	8
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_SUMMARY=	FUSE stands for 'File system in User Space'. It provides a simple interface to allow implementation of a fully functional file system in user-space.
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH=	sha256:55ff0e54fdaaa51267cef3cd031991862aca48c00efba735b3ac169f051357b0
COMPONENT_PROJECT_URL=	https://github.com/libfuse/libfuse
COMPONENT_ARCHIVE_URL=  https://github.com/jurikm/illumos-fusefs/raw/master/lib/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

GMAKE=/usr/bin/dmake

COMPONENT_BUILD_ARGS= -e CFLAGS="$(CFLAGS)" CC=$(CC)

COMPONENT_BUILD_TARGET.32= $(MACH)
COMPONENT_BUILD_TARGET.64= $(MACH64)
COMPONENT_BUILD_TARGET=$(COMPONENT_BUILD_TARGET.$(BITS))

$(INSTALL_32):	$(BUILD_32)
		(cd $(BUILD_DIR_32) && dmake -e ROOT=$(PROTO_DIR) preinstall)
		(cd $(BUILD_DIR_32)/$(MACH) && dmake -e ROOT=$(PROTO_DIR) install)
		touch $@

$(INSTALL_64):	$(BUILD_64)
		(cd $(BUILD_DIR_64) && dmake -e ROOT=$(PROTO_DIR) preinstall)
		(cd $(BUILD_DIR_64)/$(MACH64) && dmake -e ROOT=$(PROTO_DIR) install)
		touch $@

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Manually added dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
