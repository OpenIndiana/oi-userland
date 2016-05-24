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
# Copyright 2015 Captain XNV
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           freeglut
COMPONENT_VERSION=        2.8.1
COMPONENT_FMRI=           x11/library/freeglut
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  freeglut - open-source alternative to the OpenGL Utility Toolkit (GLUT) librarys
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:dde46626a62a1cd9cf48a11951cdd592e7067c345cffe193a149dfd47aef999a
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/project/freeglut/freeglut/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://freeglut.sourceforge.net/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= freeglut.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --x-includes=/usr/include
CONFIGURE_OPTIONS+= --x-libraries=/usr/lib/$(LIBSUBDIR)

CPPFLAGS += -D__posix__ -D__unix__

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

