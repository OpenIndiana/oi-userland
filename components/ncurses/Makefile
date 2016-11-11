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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ncurses
COMPONENT_VERSION=	5.7
COMPONENT_ARCHIVE_HASH= \
    sha256:0a9bdea5c7de8ded5c9327ed642915f2cc380753f12d4ad120ef7da3ea3498f4
COMPONENT_BUGDB=	library/ncurses

TPNO=			5931

include $(WS_MAKE_RULES)/gnu-component.mk

# Needed to make "gmake test" work.
COMPONENT_PRE_CONFIGURE_ACTION += \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX =	/usr/gnu

# Fix 64-bit linking via compiler.
LDFLAGS += $(CC_BITS)

CXXFLAGS += -std=sun03

# Expects GNU install.
CONFIGURE_ENV += INSTALL="$(INSTALL)"

CONFIGURE_OPTIONS +=	--with-shared
CONFIGURE_OPTIONS +=	--with-normal
CONFIGURE_OPTIONS +=	--enable-rpath
CONFIGURE_OPTIONS +=	--enable-widec
CONFIGURE_OPTIONS +=	--includedir=$(USRINCDIR)/ncurses
CONFIGURE_OPTIONS +=	--with-default-terminfo-dir=$(GNUSHARE)/terminfo

# XXX: Ugly hack copied directly from the desktop SUNWncurses.spec file:
# The sun-color terminfo included in ncurses does not work;
# copying the one shipped with Sun's curses fixes it:
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) /usr/share/lib/terminfo/s/sun-color \
	$(PROTO_DIR)$(GNUSHARE)/terminfo/s/;

# We only deliver 64-bit binaries and in /usr/bin.
COMPONENT_POST_INSTALL_ACTION.32 += \
	$(GSED) -i -e 's|$(GNUBIN)/i86|$(GNUBIN)|' \
		$(PROTOGNUBIN)/$(MACH32)/ncurses5-config;

# There is no master test file because tests are interactive and not
# tied to the build.
COMPONENT_TEST_DIR =		$(BUILD_DIR)/$(MACH$(BITS))/test
COMPONENT_TEST_TARGETS =

$(SKIP_TEST_AT_TOP_LEVEL)

REQUIRED_PACKAGES += shell/bash
# Required by this Makefile.
REQUIRED_PACKAGES += system/data/terminfo/terminfo-core
