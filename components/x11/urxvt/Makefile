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
# Copyright 2023, Niklas Poslovski
#

SINGLE_PERL_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         rxvt-unicode
COMPONENT_VERSION=      9.31
COMPONENT_FMRI=         terminal/urxvt
COMPONENT_SUMMARY=      rxvt-unicode is a fork of the well known terminal emulator rxvt
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE_FILE= urxvt.license
COMPONENT_LICENSE=      GPLv2
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:aaa13fcbc149fe0f3f391f933279580f74a96fd312d6ed06b8ff03c2d46672e8
COMPONENT_ARCHIVE_URL=  http://dist.schmorp.de/rxvt-unicode/Attic/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://software.schmorp.de/pkg/rxvt-unicode.html

COMPONENT_ARCHIVE_1=		tabbedex
COMPONENT_ARCHIVE_URL_1=	https://raw.github.com/stepb/urxvt-tabbedex/master/tabbedex
COMPONENT_ARCHIVE_HASH_1=	sha256:462af29c744cd3ba6c85ae11aadbd9a016ac9dc016f5bb7c1511751f60dd66a9

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PKG_PROTO_DIRS += $(USERLAND_ARCHIVES)

CPPFLAGS += -DLASTLOG_FILE='\"/var/adm/lastlog\"'

CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += PERL="$(PERL)"
CONFIGURE_OPTIONS += --enable-256-color
CONFIGURE_OPTIONS += --enable-smart-resize
CONFIGURE_OPTIONS += --enable-everything

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libptytty
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxrender
