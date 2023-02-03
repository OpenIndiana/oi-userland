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
COMPONENT_VERSION=	2.55.91
COMPONENT_MAJOR_VERSION=$(basename $(COMPONENT_VERSION))
COMPONENT_FMRI=		image/library/librsvg
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SUMMARY=	Library for SVG support for GNOME
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:796a43965c0e33547f5c42268f7ee3f50573236061b6e7710cae028586dca0c2
COMPONENT_ARCHIVE_URL= \
	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://www.gnome.org/
COMPONENT_LICENSE= LGPLv2

include $(WS_MAKE_RULES)/common.mk

RUST_ARCH=              x86_64-unknown-illumos
RUSTUP_HOME=            $(BUILD_DIR)/.rust_up
CARGO_HOME=             $(BUILD_DIR)/.cargo

PATH=                   $(CARGO_HOME)/bin:$(PATH.gnu)

# Cloning is required for gmake test to pass
COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
        cd $(@D); \
	gtkdocize; \
        export RUSTUP_HOME=$(RUSTUP_HOME); \
        export CARGO_HOME=$(CARGO_HOME); \
        export RUSTUP_INIT_SKIP_PATH_CHECK=yes; \
        curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- --no-modify-path --default-toolchain  stable-$(RUST_ARCH) -y; \
        rustup show; \
        );

ENV+=                   RUSTUP_HOME=$(RUSTUP_HOME)
ENV+=                   CARGO_HOME=$(CARGO_HOME)

CONFIGURE_ENV=          $(ENV)
COMPONENT_BUILD_ENV=    $(ENV)

CONFIGURE_OPTIONS += --sysconfdir=/etc/$(MACH64)
CONFIGURE_OPTIONS += --disable-Bsymbolic
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-vala

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_TEST_TRANSFORMS = \
        '-n ' \
	'-e "s/finished in.*s$$//"' \
        '-e "/^test result:/p" '


# To prevent "ERROR: loading - missing test plan"
#unexport SHELLOPTS

# Manually added dependencies
REQUIRED_PACKAGES += developer/vala
#REQUIRED_PACKAGES += developer/lang/rustc
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
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
