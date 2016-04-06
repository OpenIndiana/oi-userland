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
# Copyright 2016 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= libdiscid
COMPONENT_VERSION= 0.6.1
COMPONENT_SUMMARY= Library for creating MusicBrainz DiscIDs
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:aceb2bd1a8d15d69b2962dec7c51983af32ece318cbbeb1c43c39802922f6dd5
COMPONENT_ARCHIVE_URL= \
  http://ftp.musicbrainz.org/pub/musicbrainz/libdiscid/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://musicbrainz.org/doc/libdiscid
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = library/musicbrainz/libdiscid
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --disable-static

# For tests to pass
ENV = /usr/bin/env -i

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
