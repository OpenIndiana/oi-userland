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

COMPONENT_NAME=           libXmu
COMPONENT_VERSION=        1.1.2
COMPONENT_FMRI=           x11/library/libxmu
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  libXmu - miscellaneous utility functions for Xaw and Xt clients
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:756edc7c383254eef8b4e1b733c3bf1dc061b523c9f9833ac7058378b8349d0b
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/lib/libXmu-1.1.2.tar.bz2
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) && \
                                        cd $(@D) &&  autoreconf -f  -i )
CFLAGS += -I/usr/include/X11/xcms

CONFIGURE_OPTIONS += --without-lint
CONFIGURE_OPTIONS += --disable-lint-library

COMPONENT_BUILD_ARGS += V=1

PATH=/usr/gnu/bin:/usr/bin

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
