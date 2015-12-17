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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =	SDL
COMPONENT_VERSION =	1.2.14
COMPONENT_PROJECT_URL =	http://www.libsdl.org/
COMPONENT_SRC =		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = \
    sha256:5d927e287034cb6bb0ebccfa382cb1d185cb113c8ab5115a0759798642eed9b6
COMPONENT_ARCHIVE_URL = $(COMPONENT_PROJECT_URL)release/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/sdl

TPNO = 7683

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# libtool linking
CC += $(CC_BITS)

CONFIGURE_OPTIONS += --disable-pulseaudio
CONFIGURE_OPTIONS += CC="$(CC)"
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

# elfedit removes wrong RUNPATH/RPATH (see 22383984)
install:	$(INSTALL_32_and_64)
	/usr/bin/elfedit -e "dyn:delete RUNPATH" -e "dyn:delete RPATH" \
	  $(PROTOUSRLIBDIR)/libSDL-1.2.so.0.*
	/usr/bin/elfedit -e "dyn:delete RUNPATH" -e "dyn:delete RPATH" \
	  $(PROTOUSRLIBDIR64)/libSDL-1.2.so.0.*

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrandr
