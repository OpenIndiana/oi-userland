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
# Copyright 2022 Carsten Grzemba
#

MATE_CATEGORY= APP
BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		mate-screensaver
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	2
COMPONENT_SUMMARY= mate-screensaver is a screen saver and locker that aims to have simple, sane, secure defaults and be well integrated with the desktop
COMPONENT_ARCHIVE_HASH=	sha256:da9700ce24145bd55d24927eecfe6d31d0a52eae86e563b2c65054b356a5ff7e
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE= GPLv3
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D) && NOCONFIGURE=1 ./autogen.sh)

CONFIGURE_OPTIONS+=	--with-console-kit
CONFIGURE_OPTIONS+=	--enable-locking
CONFIGURE_OPTIONS+=	--enable-pam
CONFIGURE_OPTIONS+=	--enable-authentication-scheme=helper
CONFIGURE_OPTIONS_DBG+=	--enable-debug
CONFIGURE_OPTIONS+= $(CONFIGURE_OPTIONS_$(FLAVOUR))

REQUIRED_PACKAGES += developer/build/autoconf-archive
REQUIRED_PACKAGES += gnome/theme/background/os-backgrounds
REQUIRED_PACKAGES += library/desktop/mate/libmatekbd
REQUIRED_PACKAGES += x11/library/mesa

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/desktop/mate/libmatekbd
REQUIRED_PACKAGES += library/desktop/mate/mate-desktop
REQUIRED_PACKAGES += library/desktop/mate/mate-menus
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxscrnsaver
REQUIRED_PACKAGES += x11/library/libxxf86vm
