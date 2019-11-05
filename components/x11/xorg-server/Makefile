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
# Copyright 2016-2018 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xorg-server
COMPONENT_VERSION= 1.19.6
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Xorg - X11R7 X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:a732502f1db000cf36a376cd0c010ffdbf32ecdd7f1fa08ba7f5bdf9601cc197
COMPONENT_ARCHIVE_URL= \
  http://ftp.x.org/pub/individual/xserver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.x.org/
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION +=  ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR))

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = (cp -a $(SOURCE_DIR)/* $(@D) &&\
                                  cd $(@D) && autoreconf --install --force )

# Enabling gcc optimization leads to crashes
gcc_OPT =

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

CPPFLAGS += -DSUNSOFT -DTSOL
CPPFLAGS += -I$(USRINCDIR)/pixman-1
CPPFLAGS += -I$(USRINCDIR)/X11/dri
CPP = $(CC) -E -std=gnu99

# Default linker options cause crash in glx due to invalid DRI2Connect
LD_B_DIRECT=
LD_Z_IGNORE=

# Disable epoll on illumos
CONFIGURE_ENV+= ac_cv_func_epoll_ctl=no
CONFIGURE_ENV+= ac_cv_func_epoll_create1=no

# From X11 S12 module:
# Pass linker mapfile listing symbols that modules can count on resolving
# from the Xorg binary itself
XORG_EXTERNS_FILE = mapfile-Xorg-externs.$(MACH)
XORG_EXTERNS_FLAG = -Wl,-M,$(COMPONENT_DIR)/$(XORG_EXTERNS_FILE)
COMPONENT_BUILD_ENV += XORG_EXTERNS_FLAG='$(XORG_EXTERNS_FLAG)'
COMPONENT_BUILD_ENV += LD_SHARED_OPTIONS='-M $(COMPONENT_DIR)/$(XORG_EXTERNS_FILE)'

LDFLAGS += -L/usr/lib/xorg/$(ARCHLIBSUBDIR) -R/usr/lib/xorg/$(ARCHLIBSUBDIR)

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --bindir=$(USRBINDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-install-setuid
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-unit-tests
CONFIGURE_OPTIONS += --disable-xwin
CONFIGURE_OPTIONS += --disable-xnest
CONFIGURE_OPTIONS += --disable-systemd-logind
CONFIGURE_OPTIONS += --disable-input-thread
CONFIGURE_OPTIONS += --enable-dmx
CONFIGURE_OPTIONS += --enable-dri
CONFIGURE_OPTIONS += --enable-dri2
CONFIGURE_OPTIONS += --enable-dri3
CONFIGURE_OPTIONS += --disable-glamor
CONFIGURE_OPTIONS += --enable-glx
CONFIGURE_OPTIONS += --enable-kdrive
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-xcsecurity
CONFIGURE_OPTIONS += --enable-xephyr
CONFIGURE_OPTIONS += --enable-xdm-auth-1
CONFIGURE_OPTIONS += --enable-xdmcp
CONFIGURE_OPTIONS += --prefix=/usr
CONFIGURE_OPTIONS += --with-builderstring="Solaris ABI: $(BITS)-bit"
CONFIGURE_OPTIONS += --with-default-font-path='catalogue:/etc/X11/fontpath.d'
CONFIGURE_OPTIONS += --with-default-xkb-model=pc105
CONFIGURE_OPTIONS += --with-log-dir=/var/log
CONFIGURE_OPTIONS += --with-module-dir=/usr/lib/xorg/modules$(SERVERMOD_SUBDIR)
CONFIGURE_OPTIONS += --with-os-name="`uname -srm`"
CONFIGURE_OPTIONS += --with-vendor-name="Project OpenIndiana"
CONFIGURE_OPTIONS += --with-vendor-web="http://openindiana.org"
CONFIGURE_OPTIONS += --with-xkb-output=/var/run/xkb
CONFIGURE_OPTIONS += --with-xkb-bin-directory=/usr/bin
#CONFIGURE_OPTIONS += --disable-selective-werror

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += CPP="$(CPP)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS) -lm"
CONFIGURE_ENV += GL_CFLAGS="-I/usr/include/mesa -L/usr/lib/mesa/$(LIBSUBDIR)"
CONFIGURE_ENV += XSERVERCFLAGS_CFLAGS="-DHAS_FCHOWN -DHAS_STICKY_DIR_BIT -D_REENTRANT -D_POSIX_PTHREAD_SEMANTICS -DXTHREADS -DXUSE_MTSAFE_API"

COMPONENT_BUILD_ENV += SERVERMOD_SUBDIR="$(SERVERMOD_SUBDIR)"

COMPONENT_POST_BUILD_ACTION += ( $(ENV) $(COMPONENT_BUILD_ENV) $(CONFIGURE_ENV) $(MAKE) -C $(BUILD_DIR_$(BITS))/os/solaris/mdb )
COMPONENT_POST_INSTALL_ACTION += ( $(ENV) $(COMPONENT_BUILD_ENV) $(CONFIGURE_ENV) $(MAKE) $(COMPONENT_INSTALL_ARGS) \
			-C $(BUILD_DIR_$(BITS))/os/solaris/mdb install )

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += x11/documentation/xorg-docs
REQUIRED_PACKAGES += x11/documentation/xorg-sgml-doctools
REQUIRED_PACKAGES += x11/header/dri2proto
REQUIRED_PACKAGES += x11/header/dri3proto
REQUIRED_PACKAGES += x11/header/glproto
REQUIRED_PACKAGES += x11/header/xf86driproto
REQUIRED_PACKAGES += x11/font-util
REQUIRED_PACKAGES += x11/library/libxres
REQUIRED_PACKAGES += x11/library/xcb-util
REQUIRED_PACKAGES += x11/library/xcb-util-cursor
REQUIRED_PACKAGES += x11/library/xcb-util-errors
REQUIRED_PACKAGES += x11/library/xcb-util-image
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
REQUIRED_PACKAGES += x11/library/xcb-util-renderutil
REQUIRED_PACKAGES += x11/library/xcb-util-wm
REQUIRED_PACKAGES += x11/library/xtrans
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += system/header/header-drm
REQUIRED_PACKAGES += developer/debug/mdb
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros

# Sustained dependencies
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxfont
REQUIRED_PACKAGES += x11/library/libxv

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libdmx
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxdmcp
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxfont2
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxmuu
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxshmfence
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
