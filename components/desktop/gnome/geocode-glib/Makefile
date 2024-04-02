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
# Copyright 2018 Alexander Pyhalov
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         geocode-glib
COMPONENT_MJR_VERSION=  3.26
COMPONENT_MNR_VERSION=  4
COMPONENT_VERSION=      $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY=      A library for geocode and reverse geocoding
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:2d9a6826d158470449a173871221596da0f83ebdcff98b90c7049089056a37aa
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.gnome.org
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_FMRI=         library/desktop/geocode-glib
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING.LIB

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
