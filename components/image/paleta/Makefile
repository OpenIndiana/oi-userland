#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2025 Geoff Weiss
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         paleta
COMPONENT_VERSION=      0.3.1
COMPONENT_SUMMARY=      Extract the dominant colors from any image. 
COMPONENT_PROJECT_URL=  https://flathub.org/apps/io.github.nate_xyz.Paleta
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:9c4e856d7af8a896b513c1bb30a72b4a5eeb682aae4cf86870eca7fd453bbbb1
COMPONENT_ARCHIVE_URL=  https://github.com/nate-xyz/paleta/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         image/paleta
COMPONENT_CLASSIFICATION=Applications/Graphics and Imaging
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Need GNU msgfmt
PATH= $(PATH.gnu)

# Need for memset_s in gettext in gettext-sys crate
CFLAGS += -D__STDC_WANT_LIB_EXT1__=1
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"

# Need to compile dynamic rust crates. See https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# Need to patch gettext-sys dependency crate contents.  The gettext C
# source does not have #include <stdlib.h> in locating-rule.c .  So patch
# build.rs which then patches gettext after extraction from archive.
# Download all dependency crates and then apply patch.
CRATE_PATCH_FLAG = --backup --version-control=numbered -p0
COMPONENT_PRE_BUILD_ACTION= \
	CARGO_HOME=$(@D)/cargo-home cargo fetch --manifest-path $(SOURCE_DIR)/Cargo.toml ; \
	for patchfile in patches-crate/*.patch; do \
 		gpatch $(CRATE_PATCH_FLAG) < $$patchfile ; \
 	done ;


# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/libadwaita
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
