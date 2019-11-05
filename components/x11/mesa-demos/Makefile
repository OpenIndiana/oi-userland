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
# Copyright 2016 Ken Mays
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mesa-demos
COMPONENT_VERSION= 8.3.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= The Mesa 3-D Graphics demo applications
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:c173154bbd0d5fb53d732471984def42fb1b14ac85fcb834138fb9518b3e0bef
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.freedesktop.org/pub/mesa/demos/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mesa3d.org/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -f -i)

CONFIGURE_ENV += GLEW_CFLAGS="-I-have-no-GLEW-"
CONFIGURE_ENV += GLEW_LIBS="-I-have-no-GLEW-"

CONFIGURE_OPTIONS += --without-glut
CONFIGURE_OPTIONS += --disable-osmesa

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
