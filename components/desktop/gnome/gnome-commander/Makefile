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
# Copyright (c) 2017 Alexander Pyhalov
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-commander
HUMAN_VERSION=		1.18.6
COMPONENT_SUMMARY=	gnome commander file manager
COMPONENT_PROJECT_URL=	https://gcmd.github.io/
COMPONENT_ARCHIVE_HASH=	sha256:ca11736869c3e08aa0a12d8caf1e1ce79679365b177c07eb4ab810cd4da4c8cb
COMPONENT_FMRI=		desktop/file-manager/gnome-commander
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/File Managers
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH= $(PATH.gnu)

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Testing needs the XDG_CACHE_HOME environment variable pointing to a writable
# directory (the directory does not need to exist) because otherwise Fontconfig
# complains it is unable to find writable cache directories.
COMPONENT_PRE_TEST_ACTION += $(RM) -r $(@D)/.xdg_cache_home
COMPONENT_TEST_ENV += XDG_CACHE_HOME="$(@D)/.xdg_cache_home"

# Manually added test dependencies
TEST_REQUIRED_PACKAGES += system/library/fontconfig

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/exiv2
REQUIRED_PACKAGES += library/audio/taglib
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgsf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
