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
# Copyright (c) 2017 Dariusz Sendkowski
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         global
COMPONENT_VERSION=	6.6.9
COMPONENT_SUMMARY=	A source code tagging system.
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/global
COMPONENT_DESCRIPTION=	GNU GLOBAL is a source code tagging system that works the same way across diverse environments, such as Emacs editor, Vi editor, Less viewer, Bash shell, various web browsers, etc.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:aacba0fa8d60ca645e62f312dcd23b47ed48a081aa0fb1563cff4702d9d1fad5
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/global/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/global
COMPONENT_CLASSIFICATION=Development/Editors
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV=	DEST_DIR=$(PROTO_DIR)
COMPONENT_INSTALL_ENV=	DEST_DIR=$(PROTO_DIR)

CONFIGURE_OPTIONS += --enable-static=no

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
