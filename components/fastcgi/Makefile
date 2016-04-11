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
# Prefer 32-bit as default fastcgi target matters.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		fastcgi
COMPONENT_VERSION=	2.4.0
COMPONENT_PROJECT_URL=	http://www.fastcgi.com/
COMPONENT_SRC_NAME=	fcgi
COMPONENT_ARCHIVE_HASH=	\
    sha256:66fc45c6b36a21bf2fbbb68e90f780cc21a9da1fffbae75e76d2b4402d3f05b9
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)dist/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/fcgi

TPNO=			8415

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Tell libtool to pass this flag through using -Wc.
# https://www.gnu.org/software/libtool/manual/html_node/Stripped-link-flags.html
LDFLAGS +=	-Wc,$(studio_NORUNPATH)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --includedir=$(CONFIGURE_INCLUDEDIR)/fastcgi

COMPONENT_PREP_ACTION = (cd $(@D) ; touch NEWS AUTHORS ChangeLog ; autoreconf -if)

ASLR_MODE = $(ASLR_ENABLE)

REQUIRED_PACKAGES += system/library/c++-runtime
