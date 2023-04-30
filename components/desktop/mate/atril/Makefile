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
# Copyright 2016 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2020 Marco van Wieringen
# Copyright (c) 2021 Tim Mooney.  All rights reserved
# Copyright 2022 Andreas Wacknitz
#

MATE_CATEGORY= APP
BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		atril
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	1
COMPONENT_SUMMARY=	MATE PDF document viewer
COMPONENT_ARCHIVE_HASH= sha256:a53a613acb9701a18ad671bf590254d1ce836ba0ae1be2c0bd8948fdf6b491a4
COMPONENT_FMRI=		desktop/pdf-viewer/atril
COMPONENT_CLASSIFICATION=	Applications/Office
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# gobject-introspection
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

CONFIGURE_OPTIONS += --enable-introspection
# tested atril 1.26.0 with epub support and it's still poor.  It
# uses webkitgtk2 for the epubs and can open some, but fails on
# others.  Worse, Atril spawns webkitgtk2 processes for non-epub
# documents too.  Leave epub disabled until that improves, maybe
# with an updated webkitgtk?
CONFIGURE_OPTIONS += --disable-epub

# test suite requires a python module called 'dogtail'
# for testing GUI applications which we don't currently package.

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/mate/caja
REQUIRED_PACKAGES += image/djvulibre
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libspectre
REQUIRED_PACKAGES += library/libsynctex
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
