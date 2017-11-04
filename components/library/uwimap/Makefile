#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright 2011 EveryCity Ltd. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		imap
COMPONENT_VERSION=	2007f
IPS_COMPONENT_VERSION=	0.2007.6
COMPONENT_PROJECT_URL=	http://www.washington.edu/imap/
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:3d9383e3ccb5ac6e273aa76112671b7ffdd8bef6eb7df9b5de7b7e61024f8dc5
COMPONENT_ARCHIVE_URL=	https://www.mirrorservice.org/sites/ftp.cac.washington.edu/imap/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/uw-imap
COMPONENT_SUMMARY=	University of Washington IMAP library
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE.txt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

INSTALL_COMMON=$(BUILD_DIR)/.installed

CFLAGS += -D__EXTENSIONS__

# Parallel build fails
COMPONENT_BUILD_ARGS=

COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += IP=6
COMPONENT_BUILD_ARGS += SHLIBBASE=c-client
COMPONENT_BUILD_ARGS += SHLIBNAME=libc-client.so.1
COMPONENT_BUILD_ARGS += EXTRACFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += EXTRALDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_TARGETS = ec

$(INSTALL_COMMON):	$(BUILD_32_and_64)
	$(MKDIR) -p $(PROTO_DIR)/usr/lib/$(MACH64)
	$(MKDIR) -p $(PROTO_DIR)/usr/include/c-client
	$(CP) $(BUILD_DIR_32)/c-client/libc-client.so.1 $(PROTO_DIR)/usr/lib/
	$(CP) $(BUILD_DIR_64)/c-client/libc-client.so.1 $(PROTO_DIR)/usr/lib/$(MACH64)
	$(LN) -fs libc-client.so.1 $(PROTO_DIR)/usr/lib/libc-client.so
	$(LN) -fs libc-client.so.1 $(PROTO_DIR)/usr/lib/$(MACH64)/libc-client.so
	$(CP) $(SOURCE_DIR)/src/osdep/unix/*.h $(PROTO_DIR)/usr/include/c-client/
	$(CP) $(SOURCE_DIR)/src/c-client/*.h $(PROTO_DIR)/usr/include/c-client/
	$(CP) $(BUILD_DIR_32)/c-client/linkage.h $(PROTO_DIR)/usr/include/c-client/
	$(CP) $(BUILD_DIR_32)/c-client/osdep.h $(PROTO_DIR)/usr/include/c-client/
	$(TOUCH) $@

build:	$(BUILD_32_and_64)

install:	$(INSTALL_COMMON)

test:	$(NO_TESTS)

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
