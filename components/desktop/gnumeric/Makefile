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
# Copyright 2019 Jason Martin
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     gnumeric
COMPONENT_VERSION=  1.12.52
COMPONENT_PROJECT_URL=  https://www.gnome.org
COMPONENT_SUMMARY=  GTK Spreadsheet Application
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:73cf73049a22a1d828506275b2c9378ec37c5ff37b68bb1f2f494f0d6400823b
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/1.12/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     desktop/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=   Applications/Office
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

PYTHON_VERSION=3.9

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += PYTHON="$(PYTHON)"

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --without-perl

COMPONENT_TEST_ARGS += -k

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/XPASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/XFAIL:/p" ' \
	'-e "/ERROR:/p" '

# To prevent "libtool_install_magic: unbound variable"
unexport SHELLOPTS

# Build dependencies
REQUIRED_PACKAGES += text/itstool

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/goffice
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgsf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
