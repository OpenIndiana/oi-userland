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
# Copyright 2016 Till Wegmueller
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= libnotify
COMPONENT_VERSION= 0.7.6
COMPONENT_SUMMARY= Library for desktop notifications
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:0ef61ca400d30e28217979bfa0e73a7406b19c32dd76150654ec5b2bdf47d837
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/gnome/sources/$(COMPONENT_NAME)/0.7/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.galago-project.org/news/index.php
COMPONENT_FMRI=	library/libnotify
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)
