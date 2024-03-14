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

BUILD_BITS = 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mesa
COMPONENT_VERSION= 13.0.6
COMPONENT_REVISION= 8
COMPONENT_SUMMARY= The Mesa 3-D Graphics Library
COMPONENT_SRC= mesa-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= mesa-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:29ef104a7fc082d352b1599bd6cb1d040be424ccd22f5e0eb7ee9b0e9acd3597
COMPONENT_ARCHIVE_URL= \
  https://mesa.freedesktop.org/archive/older-versions/13.x/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mesa3d.org/

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

ARCHLIBSUBDIR.64=/$(MACH64)
ARCHLIBSUBDIR=$(ARCHLIBSUBDIR.$(BITS))

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

COMPONENT_POST_UNPACK_ACTION +=  ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) )
COMPONENT_PREP_ACTION += ( cd $(SOURCE_DIR) && \
                           libtoolize --copy --force && \
                           aclocal -I m4 && \
                           automake -c -f -a && \
                           autoconf)

CONFIGURE_SCRIPT = $(@D)/configure


# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D) )

# Identify source_file files in hard links for manifest generator.
PKG_HARDLINKS +=	usr/lib/xorg/modules/dri/radeon_dri.so

# Add include paths and linker paths needed for DRM modules
CPPFLAGS = -I/usr/X11/include/drm -D__EXTENSIONS__

LDFLAGS= -L$(PROTODIR)$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) \
                -R$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) 

# Default linker options cause libGL.so.1 to be not linked to libglapi.so
# which should be done
LD_B_DIRECT=
LD_Z_IGNORE=

LD_OPTIONS += -M $(COMPONENT_DIR)/mapfile.externs

DRI_DRIVER_LIST=i915 i965 r200 radeon swrast

# Command line options to GNU autoconf configure script
CONFIGURE_OPTIONS += --disable-dri3
CONFIGURE_OPTIONS += --with-dri-driverdir='$(X11_SERVERMODS_DIR)/dri$(SERVERMOD_SUBDIR)'
CONFIGURE_OPTIONS += --with-dri-drivers='$(DRI_DRIVER_LIST)'
CONFIGURE_OPTIONS += --disable-gallium-llvm
CONFIGURE_OPTIONS += --enable-egl
CONFIGURE_OPTIONS += --enable-gbm
CONFIGURE_OPTIONS += --with-gallium-drivers=
CONFIGURE_OPTIONS += --enable-shared-glapi
CONFIGURE_OPTIONS += --enable-texture-float
CONFIGURE_OPTIONS += --enable-osmesa
CONFIGURE_OPTIONS += --with-sha1=libcrypto
CONFIGURE_OPTIONS += --disable-glx-tls
CONFIGURE_OPTIONS += --disable-shader-cache
CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV+=PYTHON=$(PYTHON)
CONFIGURE_ENV+=CPPFLAGS="$(CPPFLAGS)"

COMPONENT_BUILD_ARGS =

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/library/libpthread-stubs
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxxf86vm
