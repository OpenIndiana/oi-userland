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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
# Prefer 32-bit as only "binary" delivered is a script with embedded paths.
BUILD_BITS= 32_and_64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libnet
COMPONENT_VERSION=	1.1.5
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/libnet-dev/
COMPONENT_ARCHIVE_HASH=	\
    sha256:75588f8d1232e1df34eccf2dba5e66be197b345a07fae80d8275db994496a20d
COMPONENT_ARCHIVE_URL=	http://cdnetworks-us-2.dl.sourceforge.net/project/libnet-dev/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libnet

TPNO=			17724

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Overwrite ancient autoconf scripts to fix 64-bit host detection.
COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -fi)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

PKG_PROTO_DIRS += $(COMPONENT_SRC)/doc/man/man3
CFLAGS += -g -fPIC
CONFIGURE_OPTIONS += --srcdir=$(BUILD_DIR_$(BITS))

REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
