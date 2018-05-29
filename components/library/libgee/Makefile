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
# Copyright (c) 2013 David Hoeppner. All rights reserved.
# Copyright (c) 2018 Jason Martin
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     libgee
COMPONENT_VERSION=  0.20.1
COMPONENT_SUMMARY=  GObject based collection and utility library
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/Libgee
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:bb2802d29a518e8c6d2992884691f06ccfcc25792a5686178575c7111fea4630
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/libgee/0.20/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=    library/libgee
COMPONENT_FMRI=     library/libgee
COMPONENT_CLASSIFICATION=   Development/C

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=       --disable-static
CONFIGURE_OPTIONS  +=       --enable-shared

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build:      $(BUILD_32_and_64)

install:    $(INSTALL_32_and_64)

test:       $(TEST_32_and_64)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
