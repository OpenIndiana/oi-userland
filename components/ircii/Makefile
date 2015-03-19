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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ircii
COMPONENT_VERSION=	20141122
IPS_COMPONENT_VERSION=  0.2014.11.22
COMPONENT_PROJECT_URL=	http://www.eterna.com.au/ircii/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b5eefbd44d1eb987c324cde590ce649b45f96b1f0f562c6d2bb8fbe9af34762d
COMPONENT_ARCHIVE_URL=	ftp://ircii.warped.com/pub/ircII/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/ircii

TPNO=			21983

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Needed to correctly include <curses.h> and <term.h> when compiling the
# various C source files.
CFLAGS += -DINCLUDE_CURSES_H

CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"

CC += $(CC_BITS)
COMPONENT_BUILD_ARGS += CC="$(CC)"

# We need to reset configure options here because ircii is confused with
# CC and CFLAGS definitions as configure parameters.
CONFIGURE_OPTIONS       = --prefix=/usr

# The mandir definition in the top-level Makefile.in is broken. Work around it.
CONFIGURE_OPTIONS	+= --mandir=$(PROTOUSRSHAREMANDIR)

CONFIGURE_OPTIONS	+= --bindir=$(USRBINDIR)
CONFIGURE_OPTIONS	+= --libexecdir=$(USRBINDIR)
CONFIGURE_OPTIONS       += $(CONFIGURE_OPTIONS.$(BITS))

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:           $(NO_TESTS)


REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
