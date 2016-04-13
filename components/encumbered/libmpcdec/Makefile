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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libmpcdec
COMPONENT_VERSION= 1.2.6
COMPONENT_FMRI = library/audio/libmpcdec
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= Portable Musepack decoder library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:4bd54929a80850754f27b568d7891e1e3e1b8d2f208d371f27d1fda09e6f12a8
COMPONENT_ARCHIVE_URL= \
   http://pkgs.fedoraproject.org/repo/pkgs/libmpcdec/$(COMPONENT_ARCHIVE)/7f7a060e83b4278acf4b77d7a7b9d2c0/$(COMPONENT_ARCHIVE)
#  http://files.musepack.net/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.musepack.net/
COMPONENT_LICENSE = BSD
COMPONENT_LICENSE_FILE = COPYING

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
