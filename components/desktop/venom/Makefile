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
# Copyright 2022 Niklas Poslovski
#

BUILD_STYLE=meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         venom
COMPONENT_VERSION=      0.5.5
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://github.com/naxuroqa/venom
COMPONENT_SUMMARY=      A modern Tox client for the desktop
COMPONENT_FMRI=         communication/im/venom
COMPONENT_SRC=          Venom-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:0348e26d70b0614b6ee3d50fb6c086ae1f696ed250d8ea80eec28299bee23562
COMPONENT_ARCHIVE_URL=	https://github.com/naxuroqa/Venom/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       Applications/Internet
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING

PATH = $(PATH.gnu)

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlcipher
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gspell
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/libgee
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += network/chat/toxcore
REQUIRED_PACKAGES += system/library
