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
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gstreamer1
COMPONENT_VERSION=      1.22.9
COMPONENT_SUMMARY=      GNOME streaming media framework
COMPONENT_PROJECT_URL=  https://gstreamer.freedesktop.org/
COMPONENT_SRC_NAME=		gstreamer
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:1e7124d347e8cdc80f08ec1d370c201be513002af1102bb20e83c5279cb48ebd
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CFLAGS += -I/usr/X11/include

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBEXECDIR)
CONFIGURE_OPTIONS += -Dexamples=disabled
CONFIGURE_OPTIONS += -Dintrospection=enabled
CONFIGURE_OPTIONS += -Dpackage-origin="https://github.com/OpenIndiana/oi-userland"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CC="$(CC)"

unexport SHELLOPTS

# As test results keep only everything betweeni the lines containing Ok: and Timeout:
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^Ok:/,/^Timeout:/p" '

# not picked up by REQUIRED_PACKAGES but still needed
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# gmp & gsl needed only for the test suite
TEST_REQUIRED_PACKAGES += library/gmp
TEST_REQUIRED_PACKAGES += developer/gsl

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
