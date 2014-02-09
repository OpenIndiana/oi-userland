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
# Copyright (c) 2014 Rouven Wachhaus
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		nano
COMPONENT_VERSION=	2.2.6
COMPONENT_PROJECT_URL=	http://www.nano-editor.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:be68e133b5e81df41873d32c517b3e5950770c00fc5f4dd23810cd635abce67a
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/nano/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/nano

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--enable-color
CONFIGURE_OPTIONS  +=		--enable-multibuffer
CONFIGURE_OPTIONS  +=		--enable-nanorc
CONFIGURE_OPTIONS  +=		--enable-utf8
CONFIGURE_OPTIONS  +=		--disable-iberty
CONFIGURE_OPTIONS  +=		get_wch=getwch

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
