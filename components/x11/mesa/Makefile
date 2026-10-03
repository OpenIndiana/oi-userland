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

BUILD_STYLE = meson
BUILD_BITS = 64

# Mesa's CLC compiler (needed by iris and anv) and llvmpipe/lavapipe use this
# LLVM; spirv-llvm-translator and libclc must match its major version.
CLANG_VERSION = 21

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mesa
COMPONENT_VERSION= 25.3.6
COMPONENT_SUMMARY= The Mesa 3-D Graphics Library
COMPONENT_SRC= mesa-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= mesa-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:59217efeac3b64e7ced958324b9db7494f1e0741aeb22d780276514cc1b8f206
COMPONENT_ARCHIVE_URL= https://archive.mesa3d.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.mesa3d.org/

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL= 0

X11_SERVERMODS_DIR= /usr/lib/xorg/modules
MESA_LIBDIR= /usr/lib/mesa/$(MACH64)
MESA_DRIDIR= $(X11_SERVERMODS_DIR)/dri/$(MACH64)

# libGL and libEGL are reached through ogl-select's links in /usr/lib/GL.
CONFIGURE_OPTIONS += --libdir='lib/mesa/$(MACH64)'
CONFIGURE_OPTIONS += -Ddri-drivers-path='$(MESA_DRIDIR)'

# crocus: Intel gen4-gen7.5, iris: gen8+, virgl: virtio-gpu (QEMU/KVM),
# llvmpipe and softpipe: software.  Hardware drivers need a DRM kernel driver
# with render nodes, PRIME and syncobj (virtio_gpu; a modern i915).
CONFIGURE_OPTIONS += -Dgallium-drivers='crocus,iris,virgl,llvmpipe,softpipe'
# intel: anv (gen9+), virtio: venus, swrast: lavapipe.
CONFIGURE_OPTIONS += -Dvulkan-drivers='intel,virtio,swrast'
# Ray tracing needs gen12.5+ (Arc) hardware, for which there is no kernel driver.
CONFIGURE_OPTIONS += -Dintel-rt=disabled
CONFIGURE_OPTIONS += -Dllvm=enabled
CONFIGURE_OPTIONS += -Dshared-llvm=enabled
# Wayland currently requires linux specific socket options and epoll for events.
CONFIGURE_OPTIONS += -Dplatforms='x11'
CONFIGURE_OPTIONS += -Dglx=dri
CONFIGURE_OPTIONS += -Degl=enabled
CONFIGURE_OPTIONS += -Dgbm=enabled
CONFIGURE_OPTIONS += -Dgles1=enabled
CONFIGURE_OPTIONS += -Dgles2=enabled
# ogl-select mediates between Mesa and the NVIDIA driver.
CONFIGURE_OPTIONS += -Dglvnd=disabled
CONFIGURE_OPTIONS += -Dshader-cache=enabled
CONFIGURE_OPTIONS += -Dzstd=enabled
CONFIGURE_OPTIONS += -Dexpat=enabled
CONFIGURE_OPTIONS += -Dgallium-va=disabled
CONFIGURE_OPTIONS += -Dgallium-rusticl=false
CONFIGURE_OPTIONS += -Dvalgrind=disabled
CONFIGURE_OPTIONS += -Dlibunwind=disabled
CONFIGURE_OPTIONS += -Dlmsensors=disabled
CONFIGURE_OPTIONS += -Dbuild-tests=false

# LLVMSPIRVLib.pc and libclc.pc live beside the LLVM they were built with.
PKG_CONFIG_PATH.prepend += $(CLANG_LIBDIR)/pkgconfig
PKG_CONFIG_PATH.prepend += $(CLANG_PREFIX)/share/pkgconfig

CFLAGS += $(XPG7MODE)
CFLAGS += -Wno-incompatible-pointer-types -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS += -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -Drestrict=__restrict__
# This code has init cycles and multiple C++ libraries, and misbehaves
# when lazy loading is used. Since we're unable to restructure third
# party code at that level, we must instead disable lazy loading.
LDFLAGS += -Wl,-znolazyload
LDFLAGS += -Wl,-z,rescan-now
CFLAGS += -Wstack-protector -fdata-sections -fstack-protector-all
LD_OPTIONS += -z ignore -lssp -lsocket -lnsl
# libgallium needs libLLVM at link time of libGL, libEGL, libgbm and the GLES libraries.
LD_OPTIONS += -R$(CLANG_LIBDIR)
CONFIGURE_ENV += PYTHON=$(PYTHON)

# libdrm is in /usr/lib/xorg, libLLVM in the clang prefix.
MESA_RUNPATH= $(MESA_LIBDIR):/usr/lib/xorg/$(MACH64):$(CLANG_LIBDIR):$(GCC_LIBDIR)
COMPONENT_POST_INSTALL_ACTION.64 += \
	for f in $$($(FIND) $(PROTO_DIR)$(MESA_LIBDIR) $(PROTO_DIR)$(MESA_DRIDIR) \
	    -type f -name '*.so*'); do \
		$(ELFEDIT) -e 'dyn:runpath $(MESA_RUNPATH)' $$f || exit 1; \
	done ; \
	$(RM) -r $(PROTOUSRDIR)/include/mesa ; \
	$(MV) $(PROTOUSRDIR)/include/GL $(PROTOUSRDIR)/include/mesa

# Manually added build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/library/libpthread-stubs
REQUIRED_PACKAGES += system/header/header-drm
# mesa_clc (CLC for the iris and anv shaders) and the Vulkan BVH shaders,
# used at build time only
REQUIRED_PACKAGES += $(CLANG_DEVELOPER_PKG)
REQUIRED_PACKAGES += developer/libclc-$(CLANG_VERSION)
REQUIRED_PACKAGES += developer/spirv-llvm-translator-$(CLANG_VERSION)
REQUIRED_PACKAGES += x11/library/glslang
REQUIRED_PACKAGES += x11/library/spirv-tools
REQUIRED_PACKAGES.python += library/python/mako
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pyyaml

# Auto-generated dependencies
REQUIRED_PACKAGES += $(CLANG_RUNTIME_PKG)
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
REQUIRED_PACKAGES += x11/library/libxshmfence
REQUIRED_PACKAGES += x11/library/libxxf86vm
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
