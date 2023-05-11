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

include ../../../make-rules/shared-macros.mk

# https://sourceforge.net/projects/codeblocks/files/Sources/20.03/codeblocks-20.03.tar.bz2

COMPONENT_NAME=         codeblocks
COMPONENT_VERSION=      20.3
HUMAN_VERSION=          20.03
COMPONENT_REVISION=     3
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_FMRI=         editor/codeblocks
COMPONENT_SUMMARY=      A fast and lightweight C/C++ IDE
COMPONENT_DESCRIPTION=  Small and fast IDE, with code analysis and refactoring
#COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
#COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
#COMPONENT_ARCHIVE_HASH= sha256:9c62817d65b1cbdd926438ea9f0647ca9c3a1e04e1b144fc87bde95f016f091c
#COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/$(COMPONENT_NAME)/files/Sources/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.codeblocks.org
COMPONENT_LICENSE=      GPLv2

SVN_REPO=		http://svn.code.sf.net/p/codeblocks/code/trunk
SVN_REV=		13046
SVN_SOURCE_INFO_URL = svn://svn.code.sf.net/p/codeblocks/code/trunk@$(SVN_REV)

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ( cd $(SOURCE_DIR); bash bootstrap )

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/graphics/wxwidgets-3
REQUIRED_PACKAGES += library/tinyxml
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
