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
# Copyright 2025 Marcel Telka
#

BUILD_STYLE=cmake
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			fast_float
COMPONENT_VERSION=		8.0.2
COMPONENT_SUMMARY=		Fast and exact implementation of the C++ from_chars functions for number types
COMPONENT_PROJECT_URL=		https://github.com/fastfloat/fast_float
COMPONENT_FMRI=			library/fast_float
COMPONENT_CLASSIFICATION=	Development/C++
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=		https://github.com/fastfloat/fast_float/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=		sha256:7954fb5aa3aea74d054968d0765c88f970dbba17d3bb4aeef36a8b3df3647042
COMPONENT_LICENSE=		Apache-2.0 OR MIT OR BSL-1.0

include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		$(CAT) $(SOURCE_DIR)/README.md | markdown_py \
			| elinks -no-home -dump -no-numbering \
			| $(GSED) -e '0,/^License/d' -e '/^References/,$$d' ; \
		printf -- '--- LICENSE-APACHE --------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/LICENSE-APACHE ; \
		printf '\n--- LICENSE-MIT -----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/LICENSE-MIT ; \
		printf '\n--- LICENSE-BOOST ---------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/LICENSE-BOOST ; \
		printf '\n' \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# Enable tests
CMAKE_OPTIONS += -DFASTFLOAT_TEST=ON

# Auto-generated dependencies
