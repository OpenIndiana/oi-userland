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
# Copyright (c) 2018 Jason Martin
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     vala
COMPONENT_VERSION=  0.36.15
COMPONENT_LICENSE=  LGPL2.1
COMPONENT_FMRI=     developer/vala
COMPONENT_SUMMARY=  Vala programming language
COMPONENT_CLASSIFICATION=   Development/Other Languages
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Vala
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:3d9613e6fd95b3bf225583466aa3d6affa80345812b8e0cd3b54fc0897e49686
COMPONENT_ARCHIVE_URL=  http://download.gnome.org/sources/vala/0.36/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CFLAGS+= -D_XOPEN_SOURCE=600

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS  +=  --disable-static
CONFIGURE_OPTIONS  +=  --enable-shared

COMPONENT_TEST_ENV += CC=$(CC)
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-ne "/^PASS:/p" ' \
	'-ne "/^FAIL:/p" ' \
	'-ne "/^TOTAL:/p" '

# common targets
build:      $(BUILD_32_and_64)

install:    $(INSTALL_32_and_64)

test:       $(TEST_32_and_64)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
