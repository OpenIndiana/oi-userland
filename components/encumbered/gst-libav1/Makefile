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
# Copyright 2016 Aurelien Larcher.  All rights reserved.
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gst-libav
COMPONENT_VERSION= 1.16.2
COMPONENT_SUMMARY= GNOME streaming media framework plugins
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_FMRI= library/audio/gstreamer1/plugin/libav
COMPONENT_SRC= $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:c724f612700c15a933c7356fbeabb0bb9571fb5538f8b1b54d4d2d94188deef2
COMPONENT_ARCHIVE_URL= \
  http://gstreamer.freedesktop.org/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gstreamer.freedesktop.org/
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING.LIB

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(SOURCE_DIR) && autoreconf -f)

PATH = $(PATH.gnu)

CFLAGS += -I/usr/X11/include/mesa
CFLAGS += -I/usr/X11/include

CONFIGURE_OPTIONS += --sysconfdir=/etc

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
