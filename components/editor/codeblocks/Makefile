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
# Copyright 2016-2017 Predrag Zečević.  All rights reserved.
# Copyright 2020 Andreas Wacknitz
# Copyright 2023 Stephan Althaus
#

USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         codeblocks
COMPONENT_VERSION=	25.03
IPS_COMPONENT_VERSION=	$(shell echo $(HUMAN_VERSION) | $(GSED) -e 's/\.0*/./g')
COMPONENT_SUMMARY=	Code::Blocks is a free C/C++ and Fortran IDE
COMPONENT_SRC=		$(COMPONENT_NAME)_$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:b0f6aa5908d336d7f41f9576b2418ac7d27efbc59282aa8c9171d88cea74049e
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/$(COMPONENT_NAME)/files/Sources/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.codeblocks.org
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_FMRI=         editor/codeblocks
COMPONENT_LICENSE=	GPL-3.0-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/graphics/wxwidgets-3
REQUIRED_PACKAGES += library/tinyxml
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
