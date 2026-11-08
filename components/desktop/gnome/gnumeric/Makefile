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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=     gnumeric
COMPONENT_MJR_VERSION=  1.12
COMPONENT_VERSION=  $(COMPONENT_MJR_VERSION).62
COMPONENT_SUMMARY=  Gnumeric is an open-source spreadsheet program
COMPONENT_PROJECT_URL=  https://www.gnumeric.org
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:89331121321b9bad72d37af5a6d13a0a636f0fbb0880f0ea1f2cf8b7ab9ae631
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     desktop/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=   Applications/Office
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_ENV += PYTHON="$(PYTHON)"

COMPONENT_TEST_ARGS += -k

# Build dependencies
REQUIRED_PACKAGES += text/itstool

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/goffice
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgsf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES.perl += runtime/perl
REQUIRED_PACKAGES.python += runtime/python
