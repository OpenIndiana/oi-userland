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

X11_CATEGORY=DRIVER
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xf86-video-intel
COMPONENT_VERSION= 2.99.917
COMPONENT_REVISION= 10
COMPONENT_FMRI= x11/server/xorg/driver/xorg-video-intel
COMPONENT_SUMMARY= xf86-video-intel - Intel integrated graphics chipset driver for the Xorg X server
COMPONENT_GIT_DATE= 20171018
COMPONENT_GIT_HASH= 4798e18b2b2c8b0a05dc967e6140fd9962bc1a73
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-$(COMPONENT_VERSION)-$(COMPONENT_GIT_DATE).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:71afc36afaa9893c29ce937d09b464a54f0f56a6f13db9a8feb414e744b45fd7
COMPONENT_ARCHIVE_URL= \
  https://gitlab.freedesktop.org/xorg/driver/xf86-video-intel/-/archive/$(COMPONENT_GIT_HASH)/$(COMPONENT_SRC).tar.bz2

CONFIGURE_DEFAULT_DIRS = no
include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lm -lsocket

LD_OPTIONS+= \
        -L$(X11_SERVERMODS_DIR) -R$(X11_SERVERMODS_DIR) \
        -L$(MESA_XSERVERMODS_EXTENSIONS_DIR) -R$(MESA_XSERVERMODS_EXTENSIONS_DIR) \
        -L$(X11_SERVERMODS_EXTENSIONS_DIR) -R$(X11_SERVERMODS_EXTENSIONS_DIR) \
        -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR) \
	-Wl,-M$(COMPONENT_DIR)/mapfile.externs

# Need to override install path for all the modules
DRIVER_DIR=$(X11_SERVERMODS_DRIVERS_DIR)
COMPONENT_COMMON_ARGS = \
	intel_drv_ladir='$(DRIVER_DIR)' \
	ch7017_ladir='$(DRIVER_DIR)' \
        ch7xxx_ladir='$(DRIVER_DIR)' \
        ivch_ladir='$(DRIVER_DIR)' \
        sil164_ladir='$(DRIVER_DIR)' \
        tfp410_ladir='$(DRIVER_DIR)'

CPPFLAGS += -DXF86DRI

CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-dri
CONFIGURE_OPTIONS += --enable-dri2
CONFIGURE_OPTIONS += --disable-dri3
CONFIGURE_OPTIONS += --enable-xvmc
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-kms
CONFIGURE_OPTIONS += --enable-sna 
CONFIGURE_OPTIONS += --enable-uxa
CONFIGURE_OPTIONS += --enable-xaa
CONFIGURE_OPTIONS += --with-default-accel=uxa
CONFIGURE_OPTIONS += --enable-rendernode
CONFIGURE_OPTIONS += --enable-create2
CONFIGURE_OPTIONS += --disable-tear-free
CONFIGURE_OPTIONS += --disable-async-swap
CONFIGURE_OPTIONS += --enable-backlight
CONFIGURE_OPTIONS += --enable-backlight-helper
CONFIGURE_OPTIONS += --disable-selective-werror
CONFIGURE_OPTIONS += --disable-silent-rules

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

COMPONENT_BUILD_ARGS += $(COMPONENT_COMMON_ARGS)
COMPONENT_INSTALL_ARGS += $(COMPONENT_COMMON_ARGS)

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/library/libpthread-stubs
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxfont
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxscrnsaver
REQUIRED_PACKAGES += x11/library/libxshmfence
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/library/libxv
REQUIRED_PACKAGES += x11/library/libxvmc
REQUIRED_PACKAGES += x11/library/xcb-util
REQUIRED_PACKAGES += x11/server/xorg
