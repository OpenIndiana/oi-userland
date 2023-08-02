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
# Copyright 2021 David Stes
#

BUILD_BITS=		64
BUILD_STYLE=	meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		paprefs
COMPONENT_VERSION=	1.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=	PulseAudio Preferences
COMPONENT_PROJECT_URL=	https://freedesktop.org/software/pulseaudio/paprefs
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:b3f21e40dc3936d15e3ffc910fb0c07c14b88e8c287715b456a948c17638f633
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/Sound and Video
COMPONENT_FMRI=		desktop/paprefs
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# essential to set /usr/gnu/bin/msgfmt  (GNU msgfmt is required for .po files)
PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/gtkmm3
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
