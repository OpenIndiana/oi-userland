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

BUILD_BITS = 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xf86-video-ati
COMPONENT_VERSION= 6.14.6
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= xf86-video-ati - ATI Radeon video driver for the Xorg X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:aa5286b3e4f0187d7df14785c06dd800255d9405205dbf061da5d77df86bec36
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org

TEST_TARGET = $(NO_TESTS)
CONFIGURE_DEFAULT_DIRS = no
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
 ( cd $(@D) && \
    aclocal -I. && \
    autoheader && \
    libtoolize --automake --copy --force && \
    automake -a -f -c && \
    autoconf && \
    cp $(COMPONENT_DIR)/srcs/i2c/*.h $(COMPONENT_DIR)/srcs/i2c/*.c src/ )

# Paths to find libraries/modules to link with - libraries themselves listed
# in src/Makefile.am since ATI has multiple submodules with different needs

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules
MESA_XSERVERMODS_DIR=/usr/lib/mesa/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

LD_OPTIONS+= \
        -L$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -L$(MESA_XSERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
        -L$(X11_SERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
        -L$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) \
        -M $(COMPONENT_DIR)/mapfile-bt829_drv-external \
        -M $(COMPONENT_DIR)/mapfile-fi1236_drv-external \
        -M $(COMPONENT_DIR)/mapfile-msp3430_drv-external \
        -M $(COMPONENT_DIR)/mapfile-tda9885_drv-external \
        -M $(COMPONENT_DIR)/mapfile-uda1380_drv-external \
        -R$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -R$(MESA_XSERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR)

# Need to override install path for all the modules, not just ati_drv.so
MULTIMEDIA_MODDIR = $(X11_SERVERMODS_DIR)/multimedia$(SERVERMOD_SUBDIR)
DRIVER_DIR=$(X11_SERVERMODS_DIR)/drivers$(SERVERMOD_SUBDIR)
COMPONENT_COMMON_ARGS = ati_drv_ladir='$(DRIVER_DIR)' \
	radeon_drv_ladir='$(DRIVER_DIR)' \
        theatre_detect_drv_ladir='$(MULTIMEDIA_MODDIR)' \
        theatre_drv_ladir='$(MULTIMEDIA_MODDIR)' \
        theatre200_drv_ladir='$(MULTIMEDIA_MODDIR)'

CONFIGURE_OPTIONS += --enable-dri
CONFIGURE_OPTIONS += --disable-kms

COMPONENT_BUILD_ARGS += $(COMPONENT_COMMON_ARGS)
COMPONENT_INSTALL_ARGS += $(COMPONENT_COMMON_ARGS)

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/server/xorg
