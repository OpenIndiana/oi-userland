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
# Copyright 2015 Alexander Pyhalov
# Copyright 2016 Till Wegmueller
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libnotify
COMPONENT_VERSION= 0.7.7
COMPONENT_SUMMARY= Library for desktop notifications
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:9cb4ce315b2655860c524d46b56010874214ec27e854086c1a1d0260137efc04
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/gnome/sources/$(COMPONENT_NAME)/0.7/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.galago-project.org/news/index.php
COMPONENT_FMRI=	library/libnotify
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=       $(@D)/configure


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

CONFIGURE_OPTIONS += --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
