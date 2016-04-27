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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
# Prefer 32-bit as only "binary" delivered is a script with embedded paths.
BUILD_BITS= 32_and_64
# gcc will handle src/cpuinfo.
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =	SDL
COMPONENT_VERSION =	1.2.15
COMPONENT_PROJECT_URL =	http://www.libsdl.org/
COMPONENT_ARCHIVE_HASH = \
    sha256:d6d316a793e5e348155f0dd93b979798933fb98aa1edebcc108829d6474aad00
COMPONENT_ARCHIVE_URL = $(COMPONENT_PROJECT_URL)release/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/sdl

TPNO = 28045

COMPONENT_PREP_ACTION += ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh );

TEST_TARGET= $(SKIP_TEST)
include $(WS_MAKE_RULES)/common.mk

# libtool linking
CC += $(CC_BITS)

CONFIGURE_OPTIONS += --disable-pulseaudio

# elfedit removes wrong RUNPATH/RPATH (see 22383984)
COMPONENT_POST_INSTALL_ACTION.32= \
	$(ELFEDIT) -e "dyn:delete RUNPATH" -e "dyn:delete RPATH" \
	  $(PROTOUSRLIBDIR)/libSDL-1.2.so.0.*

COMPONENT_POST_INSTALL_ACTION.64= \
	$(ELFEDIT) -e "dyn:delete RUNPATH" -e "dyn:delete RPATH" \
	  $(PROTOUSRLIBDIR64)/libSDL-1.2.so.0.*

REQUIRED_PACKAGES += developer/gcc
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrandr
