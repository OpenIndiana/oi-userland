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
# Copyright (c) 2021 Tim Mooney.  All rights reserved
# Copyright 2022 Andreas Wacknitz
#

MATE_CATEGORY= APP
BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		mate-applets
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	1
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=	Applets components for the MATE Desktop Environment
COMPONENT_ARCHIVE_HASH= sha256:3ab8f61db376dc333ce4c18722c63a07fab3e8e1272b7e0e097ad4597b17c2c2
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --enable-stickynotes 
CONFIGURE_OPTIONS+= --disable-polkit
CONFIGURE_OPTIONS+= --without-nl

CONFIGURE_ENV+= PYTHON="$(PYTHON.3.5.64)"
CONFIGURE_ENV+= am_cv_python_pythondir="$(PYTHON.3.5.VENDOR_PACKAGES.64)"
CONFIGURE_ENV+= am_cv_python_pyexecdir="$(PYTHON.3.5.VENDOR_PACKAGES.64)"
CONFIGURE_ENV+= LIBS="-lnsl -lsocket"

REQUIRED_PACKAGES += library/python/pygobject-3-35

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/character-map/gucharmap
REQUIRED_PACKAGES += desktop/mate/mate-panel
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtksourceview3
REQUIRED_PACKAGES += library/desktop/libwnck3
REQUIRED_PACKAGES += library/desktop/mate/libmateweather
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgtop
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
