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
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=         xorg-server
COMPONENT_VERSION=      21.1.24
COMPONENT_SUMMARY=      Xorg - X11R7 X server
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:1a4eb36ca65cc3b1b936566d677a9786e13c11cd5806e951ac55f3f5ce3984af
COMPONENT_ARCHIVE_URL=  $(XORG_XSERVER_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.x.org/
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_LICENSE=      MIT

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION +=  ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR))

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = (cp -a $(SOURCE_DIR)/* $(@D) &&\
                                  cd $(@D) && PATH="$(PATH)" autoreconf --install --force )

# Enabling gcc optimization leads to crashes
gcc_OPT =

# Make gcc-14 happy
CFLAGS += -Wno-error=incompatible-pointer-types
CFLAGS += -Wno-error=implicit-function-declaration

# Do not force-include system headers such as sys/socket.h here. configure
# (xtrans.m4) finds msghdr.msg_control, which xtrans' fd passing for DRI3
# needs, only by defining _XOPEN_SOURCE=600 before sys/socket.h; dix-config.h
# then carries that and __EXTENSIONS__ into os/xstrans.c.
CPPFLAGS += -DSUNSOFT -DTSOL
CPPFLAGS += -I$(USRINCDIR)/pixman-1
CPPFLAGS += -I$(USRINCDIR)/X11/dri
CPP = $(CC) -E -std=gnu99

# Default linker options cause crash in glx due to invalid DRI2Connect
LD_B_DIRECT=
LD_Z_IGNORE=

# Disable epoll on illumos
# autoconf 2.72+ selects -std=gnu23, where bool is a keyword; xf86Opt.h uses
# bool as a member name.
CONFIGURE_ENV+= ac_cv_prog_cc_c23=no
CONFIGURE_ENV+= ac_cv_func_epoll_ctl=no
CONFIGURE_ENV+= ac_cv_func_epoll_create1=no

# From X11 S12 module:
# Pass linker mapfile listing symbols that modules can count on resolving
# from the Xorg binary itself
XORG_EXTERNS_FILE = mapfile-Xorg-externs.$(MACH)
XORG_EXTERNS_FLAG = -Wl,-M,$(COMPONENT_DIR)/$(XORG_EXTERNS_FILE)
COMPONENT_BUILD_ENV += XORG_EXTERNS_FLAG='$(XORG_EXTERNS_FLAG)'
COMPONENT_BUILD_ENV += LD_SHARED_OPTIONS='-M $(COMPONENT_DIR)/$(XORG_EXTERNS_FILE)'

LDFLAGS += -L$(X11_SERVERLIBS_DIR) -R$(X11_SERVERLIBS_DIR)

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --disable-dependency-tracking
CONFIGURE_OPTIONS += --bindir=$(USRBINDIR)
CONFIGURE_OPTIONS += --disable-install-setuid
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-unit-tests
CONFIGURE_OPTIONS += --disable-xwin
CONFIGURE_OPTIONS += --disable-xnest
CONFIGURE_OPTIONS += --disable-systemd-logind
CONFIGURE_OPTIONS += --disable-input-thread
CONFIGURE_OPTIONS += --disable-xf86-input-inputtest
CONFIGURE_OPTIONS += --enable-dri
CONFIGURE_OPTIONS += --enable-dri2
CONFIGURE_OPTIONS += --enable-dri3
# glamor: OpenGL 2D acceleration and DRI3 for the modesetting driver through
# Mesa's EGL and GBM (patch 38 turns DRI3 on only with dma-buf support).
# Xwayland is no longer part of this source.
CONFIGURE_OPTIONS += --enable-glamor
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
CONFIGURE_OPTIONS += --with-module-dir=$(X11_SERVERMODS_DIR)
CONFIGURE_OPTIONS += --with-vendor-name="Project OpenIndiana"
CONFIGURE_OPTIONS += --with-vendor-web="http://openindiana.org"
CONFIGURE_OPTIONS += --with-xkb-output=/var/run/xkb
CONFIGURE_OPTIONS += --with-xkb-bin-directory=/usr/bin

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += CPP="$(CPP)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS) -lm"
CONFIGURE_ENV += GL_CFLAGS="-I/usr/include/mesa -L$(MESA_XSERVERLIBS_DIR)"
CONFIGURE_ENV += XSERVERCFLAGS_CFLAGS="-DHAS_FCHOWN -DHAS_STICKY_DIR_BIT -D_REENTRANT -D_POSIX_PTHREAD_SEMANTICS -DXTHREADS -DXUSE_MTSAFE_API"

COMPONENT_BUILD_ENV += SERVERMOD_SUBDIR="$(X11_SERVERMOD_SUBDIR)"

COMPONENT_POST_BUILD_ACTION += ( $(ENV) $(COMPONENT_BUILD_ENV) $(CONFIGURE_ENV) $(MAKE) -C $(BUILD_DIR_$(BITS))/os/solaris/mdb )
COMPONENT_POST_INSTALL_ACTION += ( $(ENV) $(COMPONENT_BUILD_ENV) $(CONFIGURE_ENV) $(MAKE) $(COMPONENT_INSTALL_ARGS) \
			-C $(BUILD_DIR_$(BITS))/os/solaris/mdb install )

# Build dependencies
REQUIRED_PACKAGES += x11/documentation/xorg-docs
REQUIRED_PACKAGES += x11/documentation/xorg-sgml-doctools
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/font-util
REQUIRED_PACKAGES += x11/library/libxkbfile
REQUIRED_PACKAGES += x11/library/libxres
REQUIRED_PACKAGES += x11/library/xcb-util-cursor
REQUIRED_PACKAGES += x11/library/xcb-util-errors
REQUIRED_PACKAGES += x11/library/xtrans
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += system/header/header-drm
REQUIRED_PACKAGES += developer/debug/mdb
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros

# Sustained dependencies
REQUIRED_PACKAGES += x11/library/libxfont
REQUIRED_PACKAGES += x11/library/libxv

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxcvt
REQUIRED_PACKAGES += x11/library/libxdmcp
REQUIRED_PACKAGES += x11/library/libxfont2
REQUIRED_PACKAGES += x11/library/libxshmfence
REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += x11/library/xcb-util
REQUIRED_PACKAGES += x11/library/xcb-util-image
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
REQUIRED_PACKAGES += x11/library/xcb-util-renderutil
REQUIRED_PACKAGES += x11/library/xcb-util-wm
