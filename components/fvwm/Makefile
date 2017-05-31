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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS=	64
# We fail to build with Studio 12.4 -- some seemingly non-existent issue on
# line 146 of X11/Xfuncproto.h (s12b117) -- and with that hacked away, we get
# lots of warnings, and finally crash.
COMPILER=	gcc
include ../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/shared-targets.mk

COMPONENT_NAME=		fvwm
COMPONENT_VERSION=	2.6.7
COMPONENT_PROJECT_URL=	http://www.fvwm.org/
COMPONENT_ARCHIVE_HASH=	sha256:01654d5abdcde6dac131cae9befe5cf6f01f9f7524d097c3b0f316e39f84ef73
COMPONENT_ARCHIVE_URL=	https://github.com/fvwmorg/fvwm/releases/download/$(COMPONENT_VERSION)/fvwm-$(COMPONENT_VERSION).tar.gz
COMPONENT_ANITYA_ID=	11128

TPNO=			35011

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV +=	PYTHON=$(PYTHON.2.7.64)
CONFIGURE_OPTIONS +=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--enable-htmldoc

COMPONENT_PRE_CONFIGURE_ACTION +=	(cd $(COMPONENT_SRC) && autoreconf -i)

# libreadline isn't linked against libcurses, despite using symbols from it, so
# its clients need to be linked directly.  However, with -z ignore passed to
# the linker by default, it gets eliminated from the link because FvwmConsoleC
# doesn't use any libcurses symbols directly.  So we add -lcurses to LD_OPTIONS
# *prior* to -zignore, and force a rebuild of just that one module.
COMPONENT_POST_BUILD_ACTION +=		\
	(cd $(BUILD_DIR_64)/modules/FvwmConsole && \
	rm -f .libs/FvwmConsoleC FvwmConsoleC && \
	$(ENV) LD_OPTIONS="-lcurses $(LD_OPTIONS)" \
	    LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)" $(MAKE))

REQUIRED_PACKAGES +=	image/library/librsvg
REQUIRED_PACKAGES +=	image/library/libpng
REQUIRED_PACKAGES +=	library/desktop/cairo
REQUIRED_PACKAGES +=	library/glib2
REQUIRED_PACKAGES +=	library/readline
REQUIRED_PACKAGES +=	runtime/perl-522
REQUIRED_PACKAGES +=	system/library/fontconfig
REQUIRED_PACKAGES +=	system/library/math
REQUIRED_PACKAGES +=	x11/library/libice
REQUIRED_PACKAGES +=	x11/library/libsm
REQUIRED_PACKAGES +=	x11/library/libx11
REQUIRED_PACKAGES +=	x11/library/libxcursor
REQUIRED_PACKAGES +=	x11/library/libxext
REQUIRED_PACKAGES +=	x11/library/libxft
REQUIRED_PACKAGES +=	x11/library/libxinerama
REQUIRED_PACKAGES +=	x11/library/libxpm
REQUIRED_PACKAGES +=	x11/library/libxrender
