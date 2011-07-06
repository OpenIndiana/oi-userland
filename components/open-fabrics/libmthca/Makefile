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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmthca
COMPONENT_VERSION=	1.0.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-0.1.gbe5eef3.tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:5d118728fd57982d5c7fe21ea7b4e6b0c3884c08
COMPONENT_ARCHIVE_URL=	http://www.openfabrics.org/downloads/libmthca/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include ../ofed.mk

LIBS +=	-libverbs
LDFLAGS +=	-L$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))

CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"

COMPONENT_POST_INSTALL_ACTION =\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/$(COMPONENT_NAME).la;\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/$(COMPONENT_NAME).la;\

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
