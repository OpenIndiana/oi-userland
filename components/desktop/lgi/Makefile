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

#
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64_and_32
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         lgi
COMPONENT_VERSION=      0.9.0
COMPONENT_PROJECT_URL=  https://github.com/pavouk/lgi
COMPONENT_ARCHIVE_HASH= \
        sha256:87c7870f8a1c60b48c4d5587b7fab46863e1cb9e76a68520f47e9ef2764cfe24
COMPONENT_ARCHIVE_URL=  https://github.com/pavouk/lgi/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_BUGDB=        gnome/libraries
COMPONENT_ANITYA_ID=	1851

TPNO=                   27458

# Tests do not build on Solaris yet
TEST_TARGET= $(SKIP_TEST)

BUILD_STYLE= justmake

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += $(CC_BITS)

COMPONENT_INSTALL_ARGS += LUA_VERSION=5.2 PREFIX=$(USRDIR)
COMPONENT_INSTALL_ARGS.64 += LUA_LIBDIR=$(USRDIR)/lib/lua/5.2/64

REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += runtime/lua
