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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsdp
COMPONENT_VERSION=	1.1.108
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-0.15.gd7fdb72.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b72d4d84c7a02207c261082d1837757f8c131942193ceaf017daf684d61e8be1
COMPONENT_ARCHIVE_URL=	http://www.openfabrics.org/downloads/libsdp/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include ../ofed.mk

MAN3FILES = libsdp.3lib
MAN4FILES = libsdp.conf.4

include $(WS_TOP)/make-rules/shared-targets.mk

SUFFIX.64 = $(MACH64)

CFLAGS += -D_POSIX_PTHREAD_SEMANTICS

LIBS += -lsocket -lnsl

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libdir=/usr/lib/secure/$(SUFFIX.$(BITS))

CLEANUP_DIRS =	$(PROTOUSRBINDIR)/linux
CLEANUP_FILES =\
	$(PROTO_DIR)/$(CONFIGURE_PREFIX)/lib/secure/$(COMPONENT_NAME).la\
	$(PROTO_DIR)/$(CONFIGURE_PREFIX)/lib/secure/$(MACH64)/$(COMPONENT_NAME).la\

COMPONENT_PREP_ACTION = \
	$(MKDIR) $(@D)/man ; \
	cp manpages/$(MAN3FILES) manpages/$(MAN4FILES) $(@D)/man ; \

COMPONENT_POST_INSTALL_ACTION=\
	$(RM) $(CLEANUP_FILES);\
	$(RM) $(CLEANUP_DIRS)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
