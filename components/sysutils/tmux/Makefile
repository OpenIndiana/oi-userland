#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2011, 2013, EveryCity Ltd. All rights reserved.
# Copyright 2019, Michal Nowak
# Copyright 2019, Solene Rapenne
# Copyright 2020, Nona Hansel
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tmux
COMPONENT_VERSION=	3.1c
# Version for IPS. It is easier to do it manually than convert the letter to a
# number while taking into account that there might be no letter at all.
IPS_COMPONENT_VERSION=	3.1.3
COMPONENT_FMRI=		terminal/tmux
COMPONENT_PROJECT_URL=	https://$(COMPONENT_NAME).github.io
COMPONENT_SUMMARY=	tmux terminal multiplexer
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:918f7220447bef33a1902d4faff05317afd9db4ae1c9971bef5c787ac6c88386
COMPONENT_ARCHIVE_URL= \
	https://github.com/tmux/tmux/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	BSD

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS +=	-I/usr/include/ncurses

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f -i)

CONFIGURE_OPTIONS +=	--enable-utempter
CONFIGURE_OPTIONS +=	LIBS="-lncurses"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libutempter
