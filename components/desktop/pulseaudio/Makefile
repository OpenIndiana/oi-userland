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
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 64
BUILD_STYLE=meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pulseaudio
COMPONENT_VERSION=	17.0
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	Sample Rate Converter for audio
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:053794d6671a3e397d849e478a80b82a63cb9d8ca296bd35b73317bb5ceb87b5
COMPONENT_ARCHIVE_URL= https://freedesktop.org/software/pulseaudio/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/PulseAudio/
COMPONENT_FMRI=		library/audio/pulseaudio
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE=	LGPLv2.1,GPLv2,MIT,adrian-license,Sun Public Domain license

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += -Wno-error=incompatible-pointer-types

# MESON_BUILDTYPE = debug
# COMPONENT_BUILD_ARGS += --verbose
LDFLAGS += -lnsl -lsocket

CONFIGURE_OPTIONS += -Dhal-compat=true
CONFIGURE_OPTIONS += -Dipv6=true
CONFIGURE_OPTIONS += -Dopenssl=enabled
CONFIGURE_OPTIONS += -Dorc=enabled
CONFIGURE_OPTIONS += -Doss-output=enabled
CONFIGURE_OPTIONS += -Ddatabase=gdbm
CONFIGURE_OPTIONS += -Dzshcompletiondir=/usr/share/zsh/5.9/functions/Completion/Unix
CONFIGURE_OPTIONS += -Dsystem_user=pulse
CONFIGURE_OPTIONS += -Dsystem_group=pulse
CONFIGURE_OPTIONS += -Djack=disabled
CONFIGURE_OPTIONS += -Dlirc=disabled
CONFIGURE_OPTIONS += -Dbluez5=disabled
CONFIGURE_OPTIONS += -Dgstreamer=enabled
CONFIGURE_OPTIONS += -Dbluez5-gstreamer=disabled
CONFIGURE_OPTIONS += -Dgsettings=enabled
CONFIGURE_OPTIONS += -Dgtk=disabled
CONFIGURE_OPTIONS += -Dsoxr=enabled
CONFIGURE_OPTIONS += -Dwebrtc-aec=disabled
CONFIGURE_OPTIONS += -Dsystemd=disabled
CONFIGURE_OPTIONS += -Dtests=true

CONFIGURE_ENV	+= CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV	+= PYTHON=$(PYTHON)
CONFIGURE_ENV	+= GLIB_COMPILE_SCHEMAS=/usr/bin/glib-compile-schemas


COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/Ok|Fail:|Skipped|Unexpected Pass|Timeout/'"

# to prevent reconfigure before install
COMPONENT_PRE_INSTALL_ACTION += ( cd $(@D) && touch build.ninja )
# For tests
TEST_REQUIRED_PACKAGES += developer/check

# Manually added dependencies (needed by qpaeq)
PYTHON_REQUIRED_PACKAGES += runtime/python
PYTHON_REQUIRED_PACKAGES += library/python/sip

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/audio/soxr
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/orc
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxtst
