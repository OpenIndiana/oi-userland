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
# Copyright 2011, Andrzej Szeszo
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rxvt-unicode
COMPONENT_VERSION=	9.22
COMPONENT_FMRI=		terminal/urxvt
COMPONENT_SUMMARY=	rxvt-unicode is a fork of the well known terminal emulator rxvt
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE_FILE=	urxvt.license
COMPONENT_LICENSE=	GPLv2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:e94628e9bcfa0adb1115d83649f898d6edb4baced44f5d5b769c2eeb8b95addd
COMPONENT_ARCHIVE_URL=	http://dist.schmorp.de/rxvt-unicode/Attic/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://software.schmorp.de/pkg/rxvt-unicode.html

COMPONENT_ARCHIVE_1=	tabbedex
COMPONENT_ARCHIVE_URL_1=	https://raw.github.com/stepb/urxvt-tabbedex/master/tabbedex

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_PROTO_DIRS += $(USERLAND_ARCHIVES)

CPPFLAGS += -DLASTLOG_FILE='\"/var/adm/lastlog\"'

CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += PERL="$(PERL)"
CONFIGURE_OPTIONS += --enable-256-color
CONFIGURE_OPTIONS += --enable-smart-resize
CONFIGURE_OPTIONS += --enable-everything

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxrender
