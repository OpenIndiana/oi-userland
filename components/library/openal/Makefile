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
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	openal
COMPONENT_VERSION=	1.17.2
COMPONENT_FMRI=	library/audio/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	OpenAL is a cross-platform 3D Audio library to support video game and multimedia programming
COMPONENT_SRC=	$(COMPONENT_NAME)-soft-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
  sha256:a341f8542f1f0b8c65241a17da13d073f18ec06658e1a1606a8ecc8bbc2b3314
COMPONENT_ARCHIVE_URL=	\
  http://kcat.strangesoft.net/$(COMPONENT_NAME)-releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://kcat.strangesoft.net/openal.html
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=	LGPGv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

CXXFLAGS+=$(CXXFLAGS.$(BITS)) -D__EXTENSIONS__
CFLAGS+=$(CFLAGS.$(BITS)) -D__EXTENSIONS__

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
