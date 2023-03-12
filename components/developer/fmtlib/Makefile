#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2023 Friedrich Kink
#

BUILD_BITS=		64
BUILD_STYLE=		cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         fmt
COMPONENT_VERSION=      9.1.0
HUMAN_VERSION=          $(COMPONENT_VERSION)
COMPONENT_SUMMARY=      fmt is an open-source formatting library providing a fast and safe alternative to C stdio and C++ iostreams.
COMPONENT_PROJECT_URL=  https://github.com/fmtlib/$(COMPONENT_NAME)
COMPONENT_FMRI=         developer/fmt
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=  https://github.com/$(COMPONENT_NAME)lib/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:5dea48d1fcddc3ec571ce2058e13910a0d4a6bab4cc09a809d8b1dd1c88ae6f2
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE.rst

PATH=			$(PATH.gnu)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TRANSFORMS = \
        '-e "s/Passed.*$$/Passed/" ' \
        '-e "/^Test project/d" ' \
	'-e "/^Total Test/d" '

CMAKE_OPTIONS += -DFMT_MASTER_PROJECT=ON
# Auto-generated dependencies
