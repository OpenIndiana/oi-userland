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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2013  Erol Zavidic. All rights reserverd.
# Copyright (c) 2016  Adam Stevko. All rights reserverd.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	ncurses
COMPONENT_VERSION=	5.9
COMPONENT_REVISION=	5
COMPONENT_SUMMARY=	A CRT screen handling and optimization package.
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/ncurses/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:9046298fb440324c9d4135ecea7879ffed8546dd1b58e59430ea07a4633f563b
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/ncurses
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Needed to make "gmake test" work.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX =	/usr/gnu

# Workaround compilation failure with macro "mouse_trafo"
CPPFLAGS += -P

# force XPG6 standard
CXXFLAGS += -D_XPG6
LDFLAGS += -D_XPG6
CPPFLAGS += -D_XPG6
CFLAGS += -std=c99 -D_POSIX_C_SOURCE=200112L

CONFIGURE_OPTIONS +=	--with-shared
CONFIGURE_OPTIONS +=	--with-normal
CONFIGURE_OPTIONS +=	--enable-rpath
CONFIGURE_OPTIONS +=	--enable-widec
CONFIGURE_OPTIONS +=	--enable-pc-files
CONFIGURE_OPTIONS +=	--includedir=$(USRINCDIR)/ncurses

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# XXX: Ugly hack copied directly from the desktop SUNWncurses.spec file:
# The sun-color terminfo included in ncurses does not work;
# copying the one shipped with Sun's curses fixes it:
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) /usr/share/lib/terminfo/s/sun-color \
	$(PROTO_DIR)$(GNULIB)/terminfo/s/

COMPONENT_TEST_DIR =		$(BUILD_DIR)/$(MACH$(BITS))/test
COMPONENT_TEST_TARGETS =

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
