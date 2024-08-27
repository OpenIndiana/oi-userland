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
# Copyright 2022 Vincent Torri
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           pkgconf
COMPONENT_VERSION=        2.3.0
COMPONENT_SUMMARY=        Package compiler and linker metadata toolkit
COMPONENT_PROJECT_URL=    http://pkgconf.org/
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=    https://distfiles.dereferenced.org/pkgconf/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=   sha256:3a9080ac51d03615e7c1910a0a2a8df08424892b5f13b0628a204d3fcce0ea8b
COMPONENT_FMRI=           developer/build/pkgconf
COMPONENT_CLASSIFICATION= Development/System
COMPONENT_LICENSE=        ISC
COMPONENT_LICENSE_FILE=   COPYING

# Tests depend upon kyua framework
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# do not build static library
CONFIGURE_OPTIONS += --disable-static

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ARGS += CC=$(CC)
COMPONENT_INSTALL_ARGS += PREFIX=/usr DESTDIR=$(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
