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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2018 Michal Nowak
# Copyright 2023 Friedrich Kink
#

BUILD_BITS= 64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		librsvg
COMPONENT_VERSION=	2.55.3
COMPONENT_MAJOR_VERSION=$(basename $(COMPONENT_VERSION))
COMPONENT_FMRI=		image/library/librsvg
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SUMMARY=	Library for SVG support for GNOME
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:630f43ae9140506a91835a91d1487a0b61e3fdf5fdbed3d2f2053a677208b1c6
COMPONENT_ARCHIVE_URL= \
	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://www.gnome.org/
COMPONENT_LICENSE= LGPLv2

include $(WS_MAKE_RULES)/common.mk

RUST_ARCH=              x86_64-unknown-illumos
CARGO_HOME=             $(@D)/.cargo
# if -z ignore is added to LD_OPTIONS the build will fail
LD_OPTIONS=-M /usr/lib/ld/map.noexstk -M /usr/lib/ld/map.noexdata -M /usr/lib/ld/map.pagealign -Bdirect

PATH=                   $(PATH.gnu)

# Cloning is required for gmake test to pass
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D); )

CONFIGURE_OPTIONS += --sysconfdir=/etc/$(MACH64)
CONFIGURE_OPTIONS += --disable-Bsymbolic
CONFIGURE_OPTIONS += --disable-static
# does not build
CONFIGURE_OPTIONS += --disable-gtk-doc
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-vala

COMPONENT_BUILD_ENV += CARGO_HOME=$(CARGO_HOME)

COMPONENT_TEST_TRANSFORMS = \
        '-n ' \
	'-e "s/finished in.*s$$//"' \
        '-e "/^test result:/p" '


# To prevent "ERROR: loading - missing test plan"
unexport SHELLOPTS

# Manually added dependencies
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += service/gnome/desktop-cache
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
