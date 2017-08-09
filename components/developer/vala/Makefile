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
# Copyright (c) 2017 Andreas Wacknitz
# Copyright (c) 2017 agrellum@gmail.com
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     vala
COMPONENT_VERSION=  0.36
COMPONENT_REVISION= 4
COMPONENT_LICENSE=  LGPL2.1
COMPONENT_FMRI=     developer/vala
COMPONENT_SUMMARY=  Vala programming language
COMPONENT_CLASSIFICATION=   Development/Other Languages
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Vala
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).$(COMPONENT_REVISION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:e9f23ce711c1a72ce664d10946fbc5953f01b0b7f2a3562e7a01e362d86de059
COMPONENT_ARCHIVE_URL=  http://download.gnome.org/sources/vala/0.36/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS  +=  --disable-static
CONFIGURE_OPTIONS  +=  --enable-shared

# common targets
build:      $(BUILD_32_and_64)

install:    $(INSTALL_32_and_64)

test:       $(TEST_32_and_64)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
