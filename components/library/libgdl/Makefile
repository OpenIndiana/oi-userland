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
# Copyright (c) 2018 Jason Martin
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     gdl
COMPONENT_VERSION=  3.28.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY=  Gnome Docking library
COMPONENT_LICENSE = LGPLv2
COMPONENT_PROJECT_URL=  https://developer.gnome.org/gdl/
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:52cc98ecc105148467b3b2b4e0d27ae484b1b6710d53413f771ed07ef1b737b6
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/gdl/3.28/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= Development/GNOME and GTK+
COMPONENT_FMRI=     library/libgdl

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build:      $(BUILD_32_and_64)

install:    $(INSTALL_32_and_64)

# creates test-dock in build arch/gdl
test:       $(TEST_32_and_64)

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
