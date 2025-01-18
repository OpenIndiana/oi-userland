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
# Copyright 2015 Ken Mays
#

BUILD_BITS = 64
BUILD_STYLE = meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mesa
COMPONENT_VERSION= 21.3.9
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= The Mesa 3-D Graphics Library
COMPONENT_SRC= mesa-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= mesa-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:91fe6f20339884e37a7c47bfba42fb1cd397512c9ed5ad423de369f047cd8b5c
COMPONENT_ARCHIVE_URL= https://archive.mesa3d.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mesa3d.org/

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL= 0

ARCHLIBSUBDIR.64= /$(MACH64)
ARCHLIBSUBDIR= $(ARCHLIBSUBDIR.$(BITS))

SERVERMOD_SUBDIR.64= /$(MACH64)
SERVERMOD_SUBDIR= $(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR= /usr/lib/xorg/modules
X11_SERVERLIBS_DIR= /usr/lib/xorg

# Identify source_file files in hard links for manifest generator.
#PKG_HARDLINKS +=	usr/lib/xorg/modules/dri/radeon_dri.so

CONFIGURE_OPTIONS += --libdir='lib/mesa/amd64'

PKG_HARDLINKS += usr/lib/xorg/modules/dri/$(MACH64)/kms_swrast_dri.so

# Command line options to GNU autoconf configure script
CONFIGURE_OPTIONS += -Dgallium-drivers='swrast, i915, r600'
CONFIGURE_OPTIONS += -Dvulkan-drivers=''
CONFIGURE_OPTIONS += -Dgbm=enabled
CONFIGURE_OPTIONS += -Dglvnd=false
# Wayland currently requires linux specific socket options and epoll for events.
CONFIGURE_OPTIONS += -Dplatforms='x11'
# llvm is disabled due to requiring llvm 16 we do not have 16
CONFIGURE_OPTIONS += -Dllvm=false
CONFIGURE_OPTIONS += -Dglx='auto'
CONFIGURE_OPTIONS += -Degl=enabled
CONFIGURE_OPTIONS += -Dgles1=enabled
CONFIGURE_OPTIONS += -Dgles2=enabled
CONFIGURE_OPTIONS += -Dosmesa=true
CONFIGURE_OPTIONS += -Dshared-glapi=enabled
CONFIGURE_OPTIONS += -Dgallium-xvmc=enabled
CONFIGURE_OPTIONS += -Dgallium-xa=enabled
CONFIGURE_OPTIONS += -Ddri-drivers=''
CONFIGURE_OPTIONS += -Ddri-drivers-path='$(X11_SERVERMODS_DIR)/dri$(SERVERMOD_SUBDIR)'
CONFIGURE_OPTIONS += -Delf-tls=false

CFLAGS += $(XPG7MODE)
CFLAGS += -Wno-incompatible-pointer-types -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS += -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -Drestrict=__restrict__ -DHAVE_NOATEXIT
#LDFLAGS += -Wl,-zgnu-version-script-compat
# This code has init cycles and multiple C++ libraries, and misbehaves
# when lazy loading is used. Since we're unable to restructure third
# party code at that level, we must instead disable lazy loading.
LDFLAGS += -Wl,-znolazyload
LDFLAGS += -Wl,-z,rescan-now
CFLAGS += -Wstack-protector -fdata-sections -fstack-protector-all
LD_OPTIONS += -z ignore -lssp -lsocket -lnsl
#LD_OPTIONS += -z discard-unused=dependencies
#LD_OPTIONS += -M $(COMPONENT_DIR)/mapfile.externs
CONFIGURE_ENV += PYTHON=$(PYTHON)
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Add RPATH to xorg lib directory where is libdrm.

COMPONENT_POST_INSTALL_ACTION.64 += \
	for f in libgbm.so.1.0.0 libEGL.so.1.0.0 libGL.so.1.2.0 libxatracker.so.2.5.0 libXvMCr600.so.1.0.0 vdpau/libvdpau_r600.so.1.0.0; do \
	elfedit -e "dyn:runpath /usr/lib/mesa/$(MACH64):/usr/lib/xorg/$(MACH64):$(GCC_LIBDIR)" \
	  $(PROTOUSRLIBDIR)/mesa/$(MACH64)/$$f ; \
	done ; \
	elfedit -e "dyn:runpath /usr/lib/mesa/$(MACH64):/usr/lib/xorg/$(MACH64):$(GCC_LIBDIR)" \
	  $(PROTOUSRLIBDIR)/xorg/modules/dri/$(MACH64)/i915_dri.so ; \
	mv $(PROTOUSRDIR)/include/GL $(PROTOUSRDIR)/include/mesa

# Manually added build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/library/libpthread-stubs
REQUIRED_PACKAGES += system/header/header-drm
REQUIRED_PACKAGES += library/graphics/libvdpau

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/library/glu
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxshmfence
REQUIRED_PACKAGES += x11/library/libxv
REQUIRED_PACKAGES += x11/library/libxvmc
REQUIRED_PACKAGES += x11/library/libxxf86vm
