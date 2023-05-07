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

COMPONENT_NAME=		engrampa
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	1
COMPONENT_SUMMARY=	MATE archive manager
COMPONENT_ARCHIVE_HASH=	sha256:f0224107a7a4e9ea6309c9e78aa5faac802c4cf72a49ac283aa9e7ae1e8a6c4a
COMPONENT_FMRI=		desktop/archive-manager/engrampa
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/File Managers
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/mate/caja
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
