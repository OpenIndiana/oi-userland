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
# Copyright 2020 Alexander Pyhalov
#

BUILD_BITS= NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mypaint-brushes
COMPONENT_VERSION= 1.3.1
COMPONENT_SUMMARY= Brushes used by software using libmypaint
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:fef66ffc241b7c5cd29e9c518e933c739618cb51c4ed4d745bf648a1afc3fe70
COMPONENT_ARCHIVE_URL= \
  https://github.com/mypaint/mypaint-brushes/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://github.com/mypaint/mypaint-brushes
COMPONENT_LICENSE= Creative Commons 1.0 Universal
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI= library/mypaint-brushes

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
