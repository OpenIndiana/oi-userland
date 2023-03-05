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

BUILD_BITS= 64
BUILD_STYLE=	meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gst-plugins-ugly1
COMPONENT_VERSION=      1.22.1
#COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      GNOME streaming media framework plugins
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_FMRI=         library/audio/gstreamer1/plugin/ugly
COMPONENT_SRC_NAME=	gst-plugins-ugly
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:4ab3d9e13481bce1ca3c7c4bb1f65dce4f0bb40fb1cac4416e8c06dd648815c2
COMPONENT_PROJECT_URL=  https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL= 	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      LGPLv2

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

# In the past the optimisation level has been reduced for unknown reasons. Nowadays the test results don't differ anymore:
#gcc_OPT = -O2

PATH = $(PATH.gnu)

CFLAGS += -I/usr/X11/include/mesa
CFLAGS += -I/usr/X11/include

# no introspection or examples here
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += -Dorc=enabled
CONFIGURE_OPTIONS += -Dpackage-origin="https://github.com/OpenIndiana/oi-userland"
CONFIGURE_OPTIONS += -Dgpl=enabled

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_INSTALL_ENV += CC="$(CC)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CXXFLAGS="$(CXXFLAGS)"

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

unexport SHELLOPTS
# (first) delete the timing information from any line
# delete the "exit status N", it can cause issues too
# print lines that start with " N/NNN"
# print everything between "^Ok:" and "^Timeout:"
# delete the ninja log-related stuff at the end
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "s/[ 	]*[0-9][0-9]*\.[0-9][0-9]s//" ' \
	'-e "s/[ 	]*exit status [0-9][0-9]*//" ' \
	'-e "/^[ 	]*[0-9][0-9]*\/[0-9][0-9]* /p" ' \
	'-e "/^Summary of/p" ' \
	'-e "/^Ok:/,/^Timeout:/p" ' \
	'-e "/^Full log written.*/,/^ninja: build stopped.*/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += codec/opencore-amr
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/audio/liba52
REQUIRED_PACKAGES += library/audio/libcdio
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/video/libdvdread
REQUIRED_PACKAGES += library/video/libmpeg2
REQUIRED_PACKAGES += library/video/x264
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/orc
