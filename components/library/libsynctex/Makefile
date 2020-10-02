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
# Copyright 2020 Marco van Wieringen
#

BUILD_BITS=             64
BUILD_STYLE=		justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsynctex
COMPONENT_VERSION=      2.0.0
COMPONENT_FMRI=		library/libsynctex
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SUMMARY=	Library for synchronization between TeX files and resulting file
COMPONENT_GIT_HASH=	c11fe00dbdc6423a0e54d4e531563be645f78679
COMPONENT_SRC=		synctex-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE=	synctex-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:1025a5b2f2f5d78af6749b27437cc5455301749d7d7bda1c1dd33a5c1298593c
COMPONENT_ARCHIVE_URL= \
  https://github.com/jlaurens/synctex/archive/$(COMPONENT_GIT_HASH).zip
COMPONENT_PROJECT_URL=  https://github.com/jlaurens/synctex
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=            $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_PRE_BUILD_ACTION= \
        ( cp $(COMPONENT_DIR)/files/Makefile $(COMPONENT_DIR)/files/synctex.pc $(@D) )

REQUIRED_PACKAGES += library/zlib
