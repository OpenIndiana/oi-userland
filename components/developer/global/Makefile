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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		global
COMPONENT_VERSION=	6.5.6
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/global
COMPONENT_SUMMARY=	A source code tagging system.
COMPONENT_DESCRIPTION=	GNU GLOBAL is a source code tagging system that works the same way across diverse environments, such as Emacs editor, Vi editor, Less viewer, Bash shell, various web browsers, etc.
COMPONENT_FMRI=         developer/global
COMPONENT_CLASSIFICATION=	Development/Editors
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:122f9afa69a8daa0f64c12db7f02981fe573f51a163fa3829ed4f832cd281505
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/global/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV=	DEST_DIR=$(PROTO_DIR)
COMPONENT_INSTALL_ENV=	DEST_DIR=$(PROTO_DIR)
CONFIGURE_BINDIR.64=	$(CONFIGURE_BINDIR.32)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
