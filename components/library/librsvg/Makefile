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
# Copyright 2023,2024 Friedrich Kink
#

USE_DEFAULT_TEST_TRANSFORMS= yes
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		librsvg
COMPONENT_VERSION=	2.59.1
COMPONENT_REVISION=	1
COMPONENT_MAJOR_VERSION=$(basename $(COMPONENT_VERSION))
COMPONENT_SUMMARY=	Library for SVG support for GNOME
COMPONENT_PROJECT_URL= https://wiki.gnome.org/Projects/LibRsvg
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:6116267c7ddabfd4daaf1c341326da0a773139a7223e885ae40ee09bd6986ef6
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

COMPONENT_PRE_CONFIGURE_ACTION= ( CARGO_HOME=$(CARGO_HOME) cargo install --force cargo-c )

PATH=                   $(CARGO_HOME)/bin:$(PATH.gnu)

LDFLAGS=		-lsocket

COMPONENT_TEST_TRANSFORMS = \
	'-n ' \
	'-e "s/finished in.*s$$//"' \
    '-e "/^test result:/p" '

# Manually added dependencies
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += system/library/fontconfig
#needed to build the man page
REQUIRED_PACKAGES += library/python/docutils-39

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += service/gnome/desktop-cache
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
