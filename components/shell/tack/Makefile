#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tack
COMPONENT_VERSION=	1.0.9
HUMAN_VERSION=		1.09
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	TACK - terminfo action checker
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/ncurses/
COMPONENT_FMRI=		terminal/tack
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:8d6034fa48c73c52ddd356306837975e8c81c70da201714f8f860f556f09f6cf
COMPONENT_ARCHIVE_URL=	ftp://ftp.invisible-island.net/ncurses/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX = $(GNUDIR)

CFLAGS += -I/usr/include/ncurses

CONFIGURE_OPTIONS +=	--enable-widec

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
