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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tmux
COMPONENT_VERSION=	3.5
COMPONENT_SUMMARY=	tmux terminal multiplexer
COMPONENT_PROJECT_URL=	https://$(COMPONENT_NAME).github.io
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2fe01942e7e7d93f524a22f2c883822c06bc258a4d61dba4b407353d7081950f
COMPONENT_ARCHIVE_URL=	https://github.com/tmux/tmux/releases/download/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		terminal/tmux
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	BSD

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -I/usr/include/ncurses

COMPONENT_PREP_ACTION= ( cd $(@D) ; autoreconf -fiv )

CONFIGURE_OPTIONS += --enable-utempter
CONFIGURE_OPTIONS += LIBS="-lncurses"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libutempter
REQUIRED_PACKAGES += system/library/math
