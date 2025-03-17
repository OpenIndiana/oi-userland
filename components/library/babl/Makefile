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
# Copyright 2017 Gary Mills
# Copyright 2020 Alexander Pyhalov
# Copyright 2021 Andreas Wacknitz
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		babl
COMPONENT_VERSION=	0.1.112
COMPONENT_SUMMARY=	Babl is a dynamic, any to any, pixel format conversion library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:fb696682421787c8fecc83e8aab48121dec8ee38d119b65291cfcbe315028a79
COMPONENT_ARCHIVE_URL=	https://download.gimp.org/pub/babl/0.1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://gegl.org/babl/
COMPONENT_FMRI=	image/library/babl
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE= LGLPv3
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Make gcc-14 happy
CPPFLAGS += -Wno-error=implicit-function-declaration

CPPFLAGS += -I/usr/include/lcms2

CONFIGURE_OPTIONS += --datadir=$(USRSHAREDIR)
CONFIGURE_OPTIONS += --infodir=$(USRSHAREDIR)/info

CONFIGURE_OPTIONS += -Dwith-docs=false
CONFIGURE_OPTIONS += -Denable-gir=true
CONFIGURE_OPTIONS += -Denable-vapi=true
# Support x86 extensions up to sse2 introduced with Pentium 4
CONFIGURE_OPTIONS += -Denable-mmx=true
CONFIGURE_OPTIONS += -Denable-sse=true
CONFIGURE_OPTIONS += -Denable-sse2=true
# sse4.1 has been introduced with the Penryn microarchitecture (2007)
CONFIGURE_OPTIONS += -Denable-sse4_1=true
# half float format is suported since ivy bridge
CONFIGURE_OPTIONS += -Denable-f16c=true
# advanced vector extensions format is supported since Sandy Bridge (2011)
CONFIGURE_OPTIONS += -Denable-avx2=true

# gobject-introspection requires this
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Without this we get issues with gobject-introspection
LD_B_DIRECT=
LD_Z_IGNORE=

# Manually added build dependencies
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += web/browser/w3m

# Auto-generated dependencies
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
