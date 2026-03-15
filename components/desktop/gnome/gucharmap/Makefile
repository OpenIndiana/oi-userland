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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=			gucharmap
HUMAN_VERSION=			17.0.2
COMPONENT_SUMMARY=		GNOME Character Map
COMPONENT_ARCHIVE_HASH= \
	sha256:4723972cafab688af4dd927cf458e579ddaea54865d81b7c1e868f3ebbdf00aa
COMPONENT_FMRI=			desktop/character-map/gucharmap
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Documentation
COMPONENT_LICENSE=		GPL-3.0-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH = $(PATH.gnu)

# see README.md
CONFIGURE_OPTIONS += -Ducd_path=$(USRSHAREDIR)/unicode/ucd

# Build dependencies
REQUIRED_PACKAGES += data/unicode-ucd
REQUIRED_PACKAGES += data/unicode-ucd-unihan
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += system/library
