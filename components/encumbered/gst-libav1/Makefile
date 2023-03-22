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
# Copyright 2021 Tim Mooney.  All rights reserved.
# Copyright 2022-2023 Niklas Poslovski
#

BUILD_BITS= 64
BUILD_STYLE=	meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gst-libav
COMPONENT_VERSION=      1.22.1
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      GNOME streaming media framework plugins
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:c958e825dc3ac3b7a481f8db5268131a1cd701312385c2d803dc63c8e460b5fb
COMPONENT_PROJECT_URL=  https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/gstreamer1/plugin/libav
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CFLAGS += -I/usr/X11/include/mesa
CFLAGS += -I/usr/X11/include

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += -Dpackage-origin="https://github.com/OpenIndiana/oi-userland"

# Most tests currently fail because of loader errors.
# (first) delete the timing information from any line
# delete the "exit status N", it can cause issues too
# print lines that start with " N/NNN"
# print everything between "^Ok:" and "^Timeout:"
# delete the ninja log-related stuff at the end
unexport SHELLOPTS
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "s/[        ]*[0-9][0-9]*\.[0-9][0-9]s//" ' \
        '-e "s/[        ]*exit status [0-9][0-9]*//" ' \
        '-e "/^[        ]*[0-9][0-9]*\/[0-9][0-9]* /p" ' \
        '-e "/^Summary of/p" ' \
        '-e "/^Ok:/,/^Timeout:/p" ' \
        '-e "/^Full log written.*/,/^ninja: build stopped.*/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += video/ffmpeg
