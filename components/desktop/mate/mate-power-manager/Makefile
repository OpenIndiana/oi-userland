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
# Copyright (c) 2018 Alexander Pyhalov
# Copyright (c) 2019 Michal Nowak
# Copyright (c) 2020 Marco van Wieringen
# Copyright (c) 2021 Tim Mooney.  All rights reserved
# Copyright 2022 Andreas Wacknitz
#

MATE_CATEGORY= APP
BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		mate-power-manager
COMPONENT_MJR_VERSION=  1.26
COMPONENT_MNR_VERSION=  1
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=      MATE Power Manager utilities for desktop users
COMPONENT_ARCHIVE_HASH= sha256:20cd9d22ed04babf98bb50e71a0ec5d78a8a476287723278f87da76cabfb1042
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Manually add apps icons files not getting installed by the Makefiles
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/16x16/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/16x16/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/16x16/apps ; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/22x22/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/22x22/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/22x22/apps ; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/24x24/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/24x24/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/24x24/apps ; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/32x32/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/32x32/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/32x32/apps ; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/48x48/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/48x48/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/48x48/apps ; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/64x64/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/64x64/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/64x64/apps ; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/96x96/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/96x96/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/96x96/apps ; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/128x128/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/128x128/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/128x128/apps ; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/256x256/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/256x256/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/256x256/apps ; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/icons/hicolor/scalable/apps ; \
	$(CP) $(SOURCE_DIR)/data/icons/scalable/apps/* $(PROTO_DIR)/usr/share/icons/hicolor/scalable/apps ;

# Manually add icons files not getting installed by the Makefiles
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/mate-power-manager/icons/hicolor ; \
	$(CP) -pr $(SOURCE_DIR)/data/icons/* $(PROTO_DIR)/usr/share/mate-power-manager/icons/hicolor ;


# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf-archive

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/mate/mate-panel
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/upower
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrandr
