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
# Copyright 2016 Till Wegmueller
# Copyright 2016 Ken Mays
# Copyright 2020 Michal Nowak
# Copyright 2021 Andreas Wacknitz
#

MATE_CATEGORY=	APP
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		mate-settings-daemon
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	0
COMPONENT_SUMMARY=	Fork of gnome-settings-deamon
COMPONENT_ARCHIVE_HASH=	sha256:b77aa017ff811a6fcae40bd45f18d8606eec87be21e3e6fa6d35c0fe14e66d41
COMPONENT_CLASSIFICATION=	System/Libraries

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))/$(COMPONENT_NAME)
CONFIGURE_OPTIONS+= --disable-rfkill

# Build requirements
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += system/library/mozilla-nss

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/desktop/mate/libmatekbd
REQUIRED_PACKAGES += library/desktop/mate/libmatemixer
REQUIRED_PACKAGES += library/desktop/mate/mate-desktop
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
