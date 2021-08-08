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
# Copyright 2019 Michal Nowak
# Copyright 2020 Marco van Wieringen
# Copyright 2021 Andreas Wacknitz
#

MATE_CATEGORY=	APP
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		mate-session-manager
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	0
COMPONENT_SUMMARY=	The Session manager and session startup stuff
COMPONENT_ARCHIVE_HASH= sha256:5915a2f6583c0e5e58afb3abae3f4adbbe6a003c174a5b6e3d204b4e398a1816
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))/mate

# Build requirements
REQUIRED_PACKAGES += x11/library/xtrans

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus/dbus-x11
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxtst
