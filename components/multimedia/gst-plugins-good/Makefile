#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016-2018 Aurelien Larcher.  All rights reserved.
# Copyright 2019 Michal Nowak
# Copyright 2021 Tim Mooney.  All rights reserved.
# Copyright 2022-2023 Niklas Poslovski
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-plugins-good
COMPONENT_VERSION=	1.26.0
COMPONENT_SUMMARY=      GNOME streaming media framework plugins
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:9e18f139ef69ad0867c2dfbb8fe1d1736d76df11aac83f60e8d3adb1e2eaf03b
COMPONENT_PROJECT_URL=  https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/gstreamer/plugin/good
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

# almost everything is "auto" with meson
CONFIGURE_OPTIONS += -Dorc=enabled
CONFIGURE_OPTIONS += -Dlame=enabled
CONFIGURE_OPTIONS += -Doss=enabled
CONFIGURE_OPTIONS += -Doss4=enabled
CONFIGURE_OPTIONS += -Dqt5=disabled
CONFIGURE_OPTIONS += -Dqt6=disabled
CONFIGURE_OPTIONS += -Dtwolame=enabled
CONFIGURE_OPTIONS += -Dsoup=enabled
CONFIGURE_OPTIONS += -Dtests=enabled
# disable amrnb and amrwbdec because they are in opencore-amr which is in encumbered
CONFIGURE_OPTIONS += -Damrnb=disabled
CONFIGURE_OPTIONS += -Damrwbdec=disabled
CONFIGURE_OPTIONS += -Dpackage-origin="https://github.com/OpenIndiana/oi-userland"

# build dependency not detected by REQUIRED_PACKAGES
REQUIRED_PACKAGES += system/header/header-audio

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += audio/lame
REQUIRED_PACKAGES += audio/mpg123
REQUIRED_PACKAGES += audio/twolame
REQUIRED_PACKAGES += audio/wavpack
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += codec/flac-15
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/aalib
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/audio/taglib
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/orc
REQUIRED_PACKAGES += library/video/libvpx
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxtst
