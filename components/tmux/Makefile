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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tmux
COMPONENT_FMRI=		terminal/tmux
COMPONENT_VERSION=	1.8
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	tmux.license
COMPONENT_PROJECT_URL=	http://$(COMPONENT_NAME).sourceforge.net
COMPONENT_SUMMARY=	tmux terminal multiplexer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f265401ca890f8223e09149fcea5abcd6dfe75d597ab106e172b01e9d0c9cd44
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CFLAGS +=	-I/usr/include/ncurses
LDFLAGS +=	-L/usr/gnu/lib -R/usr/gnu/lib

CONFIGURE_OPTIONS +=	LIBS="-lncurses"

build:		$(BUILD_32)

install:	$(INSTALL_32)

include ../../make-rules/depend.mk
