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
COMPONENT_VERSION=        1.9.4
COMPONENT_SUMMARY=        Package compiler and linker metadata toolkit
COMPONENT_PROJECT_URL=    http://pkgconf.org/
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=    https://distfiles.dereferenced.org/pkgconf/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=   sha256:daccf1bbe5a30d149b556c7d2ffffeafd76d7b514e249271abdd501533c1d8ae
COMPONENT_FMRI=           developer/build/pkgconf
COMPONENT_CLASSIFICATION= Development/System
COMPONENT_LICENSE=        ISC

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# do not build static library
CONFIGURE_OPTIONS += --disable-static

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ARGS += CC=$(CC)
COMPONENT_INSTALL_ARGS += PREFIX=/usr DESTDIR=$(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
