#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2019 Evgeny Litvinenko
#

BUILD_BITS = 32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wine
COMPONENT_VERSION=	4.17
COMPONENT_REVISION =	1
COMPONENT_PROJECT_URL=	https://www.winehq.org/
COMPONENT_SUMMARY=	Wine - Run Windows applications.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7480a1436687486996ba6cf91fef71b70e6dafffbf2c55ea2430094c1025b2ae
COMPONENT_ARCHIVE_URL=	https://dl.winehq.org/wine/source/4.x/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sign
COMPONENT_FMRI=		runtime/wine
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION=	Applications/System Utilities

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += AS="/usr/bin/gas"
CONFIGURE_OPTIONS += --with-pulse
CONFIGURE_OPTIONS += --with-oss

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/mpg123
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libgphoto2-2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
