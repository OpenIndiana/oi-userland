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
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= The Mesa 3-D Graphics Library
COMPONENT_SRC= mesa-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= mesa-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:91fe6f20339884e37a7c47bfba42fb1cd397512c9ed5ad423de369f047cd8b5c
COMPONENT_ARCHIVE_URL= https://archive.mesa3d.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mesa3d.org/

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL= 0

# Mesa 21.x requires 2.4.100 - 2.4.109
# Mesa 22.x requires 2.4.9 - 2.4.110
# Mesa 24.x requires 2.4.110 - 2.4.119
# Mesa 25.x requires 2.4.121
# Note: See below if ever downgrading libdrm
# Mesa's dri.pc specifies a version requirement in dri.pc for >= the version of libdrm ..
# .. that Mesa was built against, thus preventing packages from being rebuilt with the older version
# Note2: see https://gitweb.gentoo.org/repo/gentoo.git/commit?id=a117c20f1b3127d4c397dddef4a7680359f1c9a3 
LIBDRM_DEPENDENCY='2.4.109'

ARCHLIBSUBDIR.64= /$(MACH64)
ARCHLIBSUBDIR= $(ARCHLIBSUBDIR.$(BITS))

SERVERMOD_SUBDIR.64= /$(MACH64)
SERVERMOD_SUBDIR= $(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR= /usr/lib/xorg/modules
X11_SERVERLIBS_DIR= /usr/lib/xorg

# Identify source_file files in hard links for manifest generator.
#PKG_HARDLINKS +=	usr/lib/xorg/modules/dri/radeon_dri.so

CONFIGURE_OPTIONS += --libdir='lib/mesa/amd64'

PKG_HARDLINKS += usr/lib/xorg/modules/dri/kms_swrast_dri.so
PKG_HARDLINKS += usr/lib/xorg/modules/dri/i915_dri.so

# 'Classic' DRI drivers
# Only add Intel i915 for now as these start getting removed in Mesa 22.x
# Other Intel classic DRI drivers: i965, iris
# Other AMD classic DRI drivers: r100, r200, r300, r600
# Other NVIDIA classic DRI drivers: nv, nouveau
DRI_DRIVERS='i915'

# 'Gallium' DRI drivers
# Initially add Intel i915 and crocus drivers as a starting point
# Other Intel Gallium drivers: i915g (future i915), crocus, iris
# Note: crocus (at a minimum) depends on glslang
# Other AMD Gallium drivers: r300, r600, radeonsi
# Other NVIDIA Gallium drivers: nouveau
# swrast Gallium driver: swrast
# Note: swrast gallium driver in future splits to softpipe and llvmpipe (v24)
# Other Gallium drivers: virgl (virtip-gpu), svga (vmware)
GALLIUM_DRIVERS='i915'

# 'Vulkan' DRI drivers
# We have some work to do before these can be enabled
# Intel: intel, intel_hasvk
# AMD: amd
# nvidia: nouveau, nvk
# swrast: swrast
# virtio-gpu: virtio
VULKAN_DRIVERS=''

# Command line options to GNU autoconf configure script
CONFIGURE_OPTIONS += -Dgallium-drivers=$(GALLIUM_DRIVERS)
CONFIGURE_OPTIONS += -Dvulkan-drivers=$(VULKAN_DRIVERS)
CONFIGURE_OPTIONS += -Dgbm=enabled
CONFIGURE_OPTIONS += -Dglvnd=false
# Wayland currently requires linux specific socket options and epoll for events.
CONFIGURE_OPTIONS += -Dplatforms='x11'
# llvm is disabled due to requiring llvm 16 we do not have 16
CONFIGURE_OPTIONS += -Dllvm=false
CONFIGURE_OPTIONS += -Dglx='dri'
CONFIGURE_OPTIONS += -Degl=enabled
CONFIGURE_OPTIONS += -Dgles1=enabled
CONFIGURE_OPTIONS += -Dgles2=enabled
CONFIGURE_OPTIONS += -Dopengl=true
CONFIGURE_OPTIONS += -Ddri3=enabled
CONFIGURE_OPTIONS += -Dosmesa=true
CONFIGURE_OPTIONS += -Dshared-glapi=enabled
CONFIGURE_OPTIONS += -Dgallium-xvmc=disabled
CONFIGURE_OPTIONS += -Dgallium-xa=disabled
CONFIGURE_OPTIONS += -Ddri-drivers=$(DRI_DRIVERS)
CONFIGURE_OPTIONS += -Ddri-drivers-path=$(X11_SERVERMODS_DIR)/dri
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
	for f in libgbm.so.1.0.0 libEGL.so.1.0.0 libGL.so.1.2.0 vdpau/libvdpau_r600.so.1.0.0; do \
	elfedit -e "dyn:runpath /usr/lib/mesa/$(MACH64):/usr/lib/xorg/$(MACH64):$(GCC_LIBDIR)" \
	  $(PROTOUSRLIBDIR)/mesa/$(MACH64)/$$f ; \
	done ; \
	elfedit -e "dyn:runpath /usr/lib/mesa/$(MACH64):/usr/lib/xorg/$(MACH64):$(GCC_LIBDIR)" \
	  $(PROTOUSRLIBDIR)/xorg/modules/dri/i915_dri.so ; \
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
