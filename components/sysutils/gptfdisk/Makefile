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

COMPONENT_NAME= gptfdisk
COMPONENT_VERSION= 1.0.1
COMPONENT_FMRI = system/storage/gptfdisk
COMPONENT_CLASSIFICATION = System/Administration and Configuration
COMPONENT_SUMMARY= GPT fdisk - Disk partitioning tool
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:864c8aee2efdda50346804d7e6230407d5f42a8ae754df70404dd8b2fdfaeac7
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/gptfdisk/files/gptfdisk/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://sourceforge.net/projects/gptfdisk/
COMPONENT_LICENSE_FILE = $(COMPONENT_NAME).license
COMPONENT_LICENSE = GPLv2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PRE_BUILD_ACTION= \
  $(CP) $(COMPONENT_DIR)/files/Makefile.solaris $(BUILD_DIR_$(BITS))

COMPONENT_BUILD_ENV+= CC="$(CC)"
COMPONENT_BUILD_ENV+= CXX="$(CXX)"
COMPONENT_BUILD_ENV+= CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV+= CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ENV+= LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_GMAKE_ARGS+= -f Makefile.solaris

GDISK_BINDIR.32 =	$(USRBINDIR32)
GDISK_BINDIR.64 =	$(USRBINDIR64)
COMPONENT_INSTALL_ARGS+= -f Makefile.solaris
COMPONENT_INSTALL_ARGS+= bindir=$(GDISK_BINDIR.$(BITS))
COMPONENT_INSTALL_ARGS+= mandir=$(USRSHAREMANDIR)/man8
COMPONENT_INSTALL_ARGS+= docdir=$(USRSHAREDOCDIR)/gdisk

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
