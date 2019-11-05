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

COMPONENT_NAME= glu
COMPONENT_VERSION= 9.0.0
COMPONENT_REVISION=1
COMPONENT_SUMMARY= libglu part of the Mesa 3-D Graphics Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:1f7ad0d379a722fcbd303aa5650c6d7d5544fde83196b42a73d1193568a4df12
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.freedesktop.org/pub/mesa/glu/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mesa3d.org/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

PATCH_LEVEL=0

ARCHLIBSUBDIR.64=/$(MACH64)
ARCHLIBSUBDIR=$(ARCHLIBSUBDIR.$(BITS))

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

LDFLAGS= -L$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) \
                -R$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) 

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
