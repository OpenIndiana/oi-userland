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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS=			32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gettext
COMPONENT_VERSION=	0.21
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/gettext/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:d20fcbb537e02dcf1383197ba05bd0734ef7bf5db06bdb241eb69b7d16b73192
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/pub/gnu/gettext/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/gnu-gettext

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--disable-java
CONFIGURE_OPTIONS +=	--disable-libasprintf
CONFIGURE_OPTIONS +=	--disable-openmp
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--without-emacs

# Tests should run in a clean environment
COMPONENT_TEST_ENV =	-i PATH=${PATH}

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/=========/p" ' \
	'-e "/Testsuite summary for/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/PASS/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/XFAIL/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/XPASS/p" ' \
	'-e "/ERROR/p" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += library/libcroco

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/gnome/gettext
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
