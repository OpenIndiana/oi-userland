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

MATE_CATEGORY= LIB
BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		caja-extensions
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	1
COMPONENT_SUMMARY=	Set of extensions for Caja, the MATE file manager
COMPONENT_ARCHIVE_HASH=	sha256:589c19e3fa10242d6239a5ccb9585598436a56ebe94d2eb2a50b5950cce1d520
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/File Managers
COMPONENT_FMRI=		desktop/mate/caja/$(COMPONENT_NAME)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# if we add gupnp libraries there may be additional functionality or
# extensions related to sendto

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/mate/caja
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/mate/mate-desktop
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
