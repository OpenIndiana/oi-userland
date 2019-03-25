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
# Copyright (c) 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nano
COMPONENT_VERSION=	4.0
COMPONENT_FMRI=		editor/nano
COMPONENT_SUMMARY=	GNU implementation of nano, a text editor emulating pico
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_PROJECT_URL=	https://www.nano-editor.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:1e2fcfea35784624a7d86785768b772d58bb3995d1aec9176a27a113b1e9bac3
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/nano/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D) && autoreconf -fiv )

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--enable-color
CONFIGURE_OPTIONS +=	--enable-multibuffer
CONFIGURE_OPTIONS +=	--enable-utf8
# magic does not identify files given their content
CONFIGURE_OPTIONS +=	--disable-libmagic
CONFIGURE_OPTIONS +=	get_wch=getwch

CPPFLAGS += -I$(USRINCDIR)/ncurses
CFLAGS += -I$(USRINCDIR)/ncurses

COMPONENT_POST_INSTALL_ACTION = \
	$(INSTALL) -D -m 0644 $(BUILD_DIR)/$(MACH64)/doc/sample.nanorc $(PROTO_DIR)$(ETCDIR)/nanorc

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
