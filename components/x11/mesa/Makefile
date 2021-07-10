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

BUILD_STYLE=meson
BUILD_TYPE=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mesa
COMPONENT_VERSION= 19.1.8
COMPONENT_SUMMARY= The Mesa 3-D Graphics Library
COMPONENT_SRC= mesa-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= mesa-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:f0fe8289b7d147943bf2fc2147833254881577e8f9ed3d94ddb39e430e711725
COMPONENT_ARCHIVE_URL= \
  https://mesa.freedesktop.org/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mesa3d.org/

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

ARCHLIBSUBDIR.64=/$(MACH64)
ARCHLIBSUBDIR=$(ARCHLIBSUBDIR.$(BITS))

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

#COMPONENT_POST_UNPACK_ACTION +=  ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) )
#COMPONENT_PREP_ACTION += ( cd $(SOURCE_DIR) && \
#                           libtoolize --copy --force && \
#                           aclocal -I m4 && \
#                           automake -c -f -a && \
#                           autoconf)

CONFIGURE_SCRIPT = $(@D)/configure


# Missing files in build dir for configure without this.
#COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D) )

# Identify source_file files in hard links for manifest generator.
#PKG_HARDLINKS +=	usr/lib/xorg/modules/dri/radeon_dri.so

# Add include paths and linker paths needed for DRM modules
CPPFLAGS = -I/usr/X11/include/drm $(CPP_XPG6MODE)

LDFLAGS= -L$(PROTODIR)$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) \
                -R$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) 

# Default linker options cause libGL.so.1 to be not linked to libglapi.so
# which should be done
LD_B_DIRECT=
LD_Z_IGNORE=

LD_OPTIONS += -M $(COMPONENT_DIR)/mapfile.externs

DRI_DRIVER_LIST=i915,i965,r100,r200,swrast

CONFIGURE_OPTIONS += -D platforms=x11,drm
CONFIGURE_OPTIONS += -D dri3=true
CONFIGURE_OPTIONS += -D dri-drivers='$(DRI_DRIVER_LIST)'
CONFIGURE_OPTIONS += -D dri-driverdir='$(X11_SERVERMODS_DIR)/dri$(SERVERMOD_SUBDIR)'
CONFIGURE_OPTIONS += -D gallium-drivers=
CONFIGURE_OPTIONS += -D swr-arches=avx,avx2
CONFIGURE_OPTIONS += -D egl=true
CONFIGURE_OPTIONS += -D gbm=true
CONFIGURE_OPTIONS += -D gles1=false
CONFIGURE_OPTIONS += -D gles2=true
CONFIGURE_OPTIONS += -D glvnd=false
CONFIGURE_OPTIONS += -D glx=dri
CONFIGURE_OPTIONS += -D libunwind=false
CONFIGURE_OPTIONS += -D llvm=true
CONFIGURE_OPTIONS += -D lmsensors=false

CONFIGURE_ENV+=PYTHON=$(PYTHON)
CONFIGURE_ENV+=CPPFLAGS="$(CPPFLAGS)"

COMPONENT_BUILD_ARGS =

# Build dependencies
REQUIRED_PACKAGES += library/graphics/libvdpau
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
