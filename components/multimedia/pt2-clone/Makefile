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
# Copyright 2026 Ignacio Soriano
#

BUILD_STYLE=cmake
USE_PARALLEL_BUILD=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pt2-clone
COMPONENT_VERSION=	1.93
COMPONENT_SUMMARY=	ProTracker 2 clone, an Amiga MOD music tracker
COMPONENT_PROJECT_URL=	https://16-bits.org/pt2.php
COMPONENT_FMRI=		audio/pt2-clone
COMPONENT_CLASSIFICATION=	Applications/Sound and Video
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/8bitbubsy/pt2-clone/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e5e5b9f2836f0482be3aef12d65229159e8024dc61e0339749e79f5641d3b0b8
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=Release

# Upstream installs only the executable; add its Freedesktop.org files and
# its default configuration (an example: pt2-clone reads protracker.ini
# from the current directory, ~/.config/protracker or ~/.protracker).
PT2_FDO=	$(SOURCE_DIR)/release/other/Freedesktop.org Resources
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D -m 0444 "$(PT2_FDO)/ProTracker 2 clone.desktop" \
		$(PROTO_DIR)$(USRSHAREDIR)/applications/pt2-clone.desktop ; \
	$(INSTALL) -D -m 0444 "$(PT2_FDO)/ProTracker 2 clone.png" \
		"$(PROTO_DIR)$(USRSHAREDIR)/icons/hicolor/512x512/apps/ProTracker 2 clone.png" ; \
	$(INSTALL) -D -m 0444 $(SOURCE_DIR)/release/other/protracker.ini \
		$(PROTO_DIR)$(USRSHAREDIR)/doc/pt2-clone/protracker.ini
# Auto-generated dependencies
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
