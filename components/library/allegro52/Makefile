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

COMPONENT_NAME=	allegro
COMPONENT_VERSION=	5.2.0
COMPONENT_FMRI=	library/$(COMPONENT_NAME)52
# Note: Allegro 5.x is not source-compatible with earlier major releases
# Allegro 5.2 is source-compatible but binary-incompatible with Allegro 5.0
# Project document on packaging suggests to name packages accordingly and
# to provide older ones too. In our oi-userland we have no legacy for it.

COMPONENT_SUMMARY=	LibAlleg (Allegro) is a cross-platform library to support video game and multimedia programming
COMPONENT_SRC_TAG=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SRC=	$(COMPONENT_SRC_TAG).0
COMPONENT_ARCHIVE=	$(COMPONENT_SRC_TAG).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:af5a69cd423d05189e92952633f9c0dd0ff3a061d91fbce62fb32c4bd87f9fd7
COMPONENT_ARCHIVE_URL=	\
  http://download.gna.org/allegro/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://liballeg.org/
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	ZLIB,GiftWare
COMPONENT_LICENSE_FILE=	LICENSE.txt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

CXXFLAGS+=$(CXXFLAGS.$(BITS))
CFLAGS+=$(CFLAGS.$(BITS))

CONFIGURE_OPTIONS+= --sysconfdir=/etc

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
