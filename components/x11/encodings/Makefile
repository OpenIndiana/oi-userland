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
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           encodings
COMPONENT_VERSION=        1.0.4
COMPONENT_FMRI=           x11/library/libfontenc/encodings
COMPONENT_CLASSIFICATION= System/Fonts
COMPONENT_SUMMARY=  encodings - data files for libfontenc to map font encodings between character sets
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:ced6312988a45d23812c2ac708b4595f63fd7a49c4dcd9f66bdcd50d1057d539
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/font/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= encodings.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --disable-gzip-small-encodings
CONFIGURE_OPTIONS+= --disable-gzip-large-encodings

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)


