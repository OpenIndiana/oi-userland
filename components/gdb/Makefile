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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gdb
COMPONENT_VERSION=	6.8
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:15e67382c39640caafa144abf2c8943106aa97d9
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gdb/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# optimization level lowered to -xO3 to address failures in the
# gdb test suite at -xO4.

studio_OPT.sparc.32 =	-xO3
studio_OPT.sparc.64 =	-xO3
studio_OPT.i386.32 =	-xO3
studio_OPT.i386.64 =	-xO3

IPS_COMPONENT_VERSION =	6.8
COMPONENT_PROJECT_URL =	http://www.gnu.org/software/gdb/

CURSES_DIR_32 = /usr/gnu/lib
CURSES_DIR_64 = /usr/gnu/lib/$(MACH64)
CURSES_DIR = $(CURSES_DIR_$(BITS))
LDFLAGS += -L$(CURSES_DIR) -R$(CURSES_DIR)

# `echo $(CFLAGS)` and `echo $(LDFLAGS)` used to
# work around problem with extra blank characters
# inserted into configrue option strings during
# nested configure invocations within the gdb build.

CONFIGURE_ENV += CFLAGS="`echo $(CFLAGS)`"
CONFIGURE_ENV += LDFLAGS="`echo $(LDFLAGS)`"

CONFIGURE_OPTIONS += --with-system-readline
CONFIGURE_OPTIONS += --with-x=no
CONFIGURE_OPTIONS += --with-curses
CONFIGURE_OPTIONS += --with-libexpat-prefix=/usr/lib
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
