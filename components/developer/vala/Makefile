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
# Copyright (c) 2019 Jason Martin
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     vala
COMPONENT_VERSION=  0.40.14
COMPONENT_LICENSE=  LGPL2.1
COMPONENT_FMRI=     developer/vala
COMPONENT_SUMMARY=  Vala programming language
COMPONENT_CLASSIFICATION=   Development/Other Languages
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Vala
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:20ce47126d24dc41314b9832b14e5e67693da716fc024619cb4c3e96566a9152
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/vala/0.40/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS  +=  --disable-static
CONFIGURE_OPTIONS  +=  --enable-shared

COMPONENT_TEST_ENV += LANG=C
COMPONENT_TEST_ENV += CC=$(CC)
COMPONENT_TEST_ENV += CXX="$(CXX)"
COMPONENT_TEST_ENV += FC="$(FC)"
COMPONENT_TEST_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_TEST_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_TEST_ENV += FCFLAGS="$(FCFLAGS)"
COMPONENT_TEST_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_TEST_ARGS += -k -i

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
    '-ne "/ tests passed/p" ' \
    '-ne "/ tests failed/p" '

# common targets
build:      $(BUILD_32_and_64)

install:    $(INSTALL_32_and_64)

test:       $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
