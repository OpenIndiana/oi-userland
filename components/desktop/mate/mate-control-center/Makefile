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
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2020 Marco van Wieringen
# Copyright (c) 2021 Tim Mooney.  All rights reserved 
# Copyright 2022 Andreas Wacknitz
#

MATE_CATEGORY= APP
BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		mate-control-center
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	0
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=	MATE desktop wide preference configuration tools
COMPONENT_ARCHIVE_HASH= sha256:286714ea778f6540fe74ef00aaf504c47141518d26ab224994f4a1af36b0134a
COMPONENT_FMRI=			desktop/mate/control-center
COMPONENT_CLASSIFICATION=	Applications/Configuration and Preferences
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += library/desktop/desktop-file-utils
REQUIRED_PACKAGES += desktop/mate/mate-settings-daemon

# no longer auto-detected
REQUIRED_PACKAGES += system/library/libdbus-glib

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/mate/marco
REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/desktop/mate/libmatekbd
REQUIRED_PACKAGES += library/desktop/mate/mate-desktop
REQUIRED_PACKAGES += library/desktop/mate/mate-menus
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxscrnsaver
