#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            32_and_64
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libcanberra
COMPONENT_VERSION=	0.30
COMPONENT_PROJECT_URL=	http://0pointer.de/lennart/projects/libcanberra/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:c2b671e67e0c288a69fc33dc1b6f1b534d07882c2aceed37004bf48c601afa72
COMPONENT_ARCHIVE_URL=	http://0pointer.de/lennart/projects/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/libraries

TPNO=			24163

TEST_TARGET= $(NO_TESTS)

# Needs updated glib2, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

# configure falsely believes ld(1) supports --gc-sections because gcc accepts
# the flag.
CONFIGURE_ENV += cc_cv_LDFLAGS__Wl___gc_sections=no

CONFIGURE_OPTIONS += --enable-gstreamer
# For documentation.
CONFIGURE_OPTIONS += --enable-lynx
CONFIGURE_OPTIONS += --enable-largefile
CONFIGURE_OPTIONS += --enable-oss
CONFIGURE_OPTIONS += --enable-pulse
CONFIGURE_OPTIONS += --enable-gtk
CONFIGURE_OPTIONS += --enable-gtk3
CONFIGURE_OPTIONS += --with-pic

REQUIRED_PACKAGES += codec/ogg-vorbis
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += web/browser/lynx
REQUIRED_PACKAGES += x11/library/libx11
