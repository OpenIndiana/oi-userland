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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tmux
COMPONENT_FMRI=		terminal/tmux
COMPONENT_VERSION=	2.2
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_PROJECT_URL=	https://$(COMPONENT_NAME).github.io
COMPONENT_SUMMARY=	tmux terminal multiplexer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:bc28541b64f99929fe8e3ae7a02291263f3c97730781201824c0f05d7c8e19e4
COMPONENT_ARCHIVE_URL=	https://github.com/tmux/tmux/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS +=	-I/usr/include/ncurses
LDFLAGS +=	-L/usr/gnu/lib -R/usr/gnu/lib

CONFIGURE_OPTIONS +=	LIBS="-lncurses"

build:		$(BUILD_32)

install:	$(INSTALL_32)

REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
