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
# Copyright 2015 Alexander Pyhalov
# Copyright 2016 Till Wegmueller
# Copyright 2016 Ken Mays
# Copyright 2020 Michal Nowak
# Copyright (c) 2021 Tim Mooney.  All rights reserved
# Copyright 2022 Andreas Wacknitz
#

MATE_CATEGORY= LIB
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		mate-desktop
COMPONENT_MJR_VERSION=	1.28
COMPONENT_MNR_VERSION=	2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Additional UI API for MATE Desktop
COMPONENT_ARCHIVE_HASH= sha256:32bb4b792014b391c1e1b8ae9c18a82b4d447650984b4cba7d28e95564964aa2
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1

include $(WS_MAKE_RULES)/common.mk

# Manually added build dependencies
REQUIRED_PACKAGES += data/iso-codes
REQUIRED_PACKAGES += developer/build/autoconf-archive

# Add dconf-editor as dependency as otherwise mate-applets crash
# as this is a non binary dependency it is not detected automatically
REQUIRED_PACKAGES += gnome/config/dconf/dconf-editor

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxrandr
