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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xf86-video-intel
COMPONENT_VERSION= 2.99.917
COMPONENT_REVISION= 6
COMPONENT_SUMMARY= xf86-video-intel - Intel integrated graphics chipset driver for the Xorg X server
COMPONENT_GIT_DATE= 20171018
COMPONENT_GIT_HASH= 4798e18b2b2c8b0a05dc967e6140fd9962bc1a73
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-$(COMPONENT_VERSION)-$(COMPONENT_GIT_DATE).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:7a6de97d5ce275cf56519da5905d1b597215772ebf826792c44998657dc76185
COMPONENT_ARCHIVE_URL= \
  https://cgit.freedesktop.org/xorg/driver/xf86-video-intel/snapshot/$(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org

include $(WS_TOP)/make-rules/prep.mk

CONFIGURE_DEFAULT_DIRS = no

include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

LDFLAGS += -lm -lsocket

COMPONENT_PREP_ACTION = ( cd $(@D) && \
                          libtoolize --automake --copy --force && \
                          aclocal -Im4 && \
                          autoheader && \
                          automake -a -f -c && \
                          autoconf )

# Paths to find libraries/modules to link with 

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules
MESA_XSERVERMODS_DIR=/usr/lib/mesa/modules
X11_SERVERLIBS_DIR=/usr/lib

LDFLAGS += -R/usr/lib/xorg$(SERVERMOD_SUBDIR)

LD_OPTIONS+= \
        -L$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -L$(MESA_XSERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
        -L$(X11_SERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
        -L$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) \
        -R$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -R$(MESA_XSERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR) \
	-Wl,-M$(COMPONENT_DIR)/mapfile.externs

# Need to override install path for all the modules
DRIVER_DIR=$(X11_SERVERMODS_DIR)/drivers$(SERVERMOD_SUBDIR)
COMPONENT_COMMON_ARGS = ch7017_ladir='$(DRIVER_DIR)' \
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
CONFIGURE_OPTIONS += --libdir=$(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR)
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

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += x11/header/dri2proto
REQUIRED_PACKAGES += x11/header/dri3proto
REQUIRED_PACKAGES += x11/header/presentproto
REQUIRED_PACKAGES += x11/header/xf86driproto
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
