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
# Copyright 2023,2026 Friedrich Kink
#

USE_DEFAULT_TEST_TRANSFORMS= yes
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		librsvg
COMPONENT_VERSION=	2.61.4
COMPONENT_MAJOR_VERSION=$(basename $(COMPONENT_VERSION))
COMPONENT_SUMMARY=	Library for SVG support for GNOME
COMPONENT_PROJECT_URL= https://wiki.gnome.org/Projects/LibRsvg
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:fca0ea28d1f28f95c8407d2579f4702dac085e7c758644daca8b40d1e072ca0c
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		image/library/librsvg
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING.LIB

include $(WS_MAKE_RULES)/common.mk

RUST_ARCH=              x86_64-unknown-illumos
CARGO_HOME=             $(@D)/.cargo
# if -z ignore is added to LD_OPTIONS the build will fail
LD_OPTIONS=-M /usr/lib/ld/map.noexstk -M /usr/lib/ld/map.noexdata -M /usr/lib/ld/map.pagealign -Bdirect

# Disable avif since it is encumbered
CONFIGURE_OPTIONS += -Davif=disabled
CONFIGURE_OPTIONS += -Dpixbuf-loader=enabled

COMPONENT_PRE_CONFIGURE_ACTION = $(GSED) -i -e 's/= .*version-script.*$$/= []/' $(SOURCE_DIR)/rsvg/meson.build

PATH=                   $(PATH.gnu)

LDFLAGS=		-lsocket

# Manually added dependencies
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += developer/cargo-c
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += system/library/fontconfig
#needed to build the man page
PYTHON_REQUIRED_PACKAGES += library/python/docutils

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
