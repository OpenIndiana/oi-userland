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
COMPONENT_VERSION=	3.3.1
HUMAN_VERSION=		3.3a
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	tmux terminal multiplexer
COMPONENT_PROJECT_URL=	https://$(COMPONENT_NAME).github.io
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e4fd347843bd0772c4f48d6dde625b0b109b7a380ff15db21e97c11a4dcdf93f
COMPONENT_ARCHIVE_URL=	https://github.com/tmux/tmux/releases/download/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		terminal/tmux
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	BSD

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -I/usr/include/ncurses

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f -i)

CONFIGURE_OPTIONS += --enable-utempter
CONFIGURE_OPTIONS += LIBS="-lncurses"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libutempter
REQUIRED_PACKAGES += system/library/math
