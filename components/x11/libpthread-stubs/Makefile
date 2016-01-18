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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           libpthread-stubs
COMPONENT_VERSION=        0.3
COMPONENT_FMRI=           x11/library/libpthread-stubs
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_SUMMARY=  pthread-stubs - pkg-config data file for building software using POSIX threads
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:35b6d54e3cc6f3ba28061da81af64b9a92b7b757319098172488a660e3d87299 
COMPONENT_ARCHIVE_URL= \
  http://xcb.freedesktop.org/dist/libpthread-stubs-0.3.tar.bz2
COMPONENT_PROJECT_URL = http://xcb.freedesktop.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

