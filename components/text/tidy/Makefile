#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2025 Klaus Ziegler
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

DROP_STATIC_LIBRARIES = yes

COMPONENT_NAME=		tidy
COMPONENT_VERSION=	5.8.0
COMPONENT_PROJECT_URL=	https://www.html-tidy.org
COMPONENT_SUMMARY=	The HTML Tidy Library.
COMPONENT_FMRI=		text/tidy
COMPONENT_SRC=		$(COMPONENT_NAME)-html5-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/htacg/$(COMPONENT_NAME)-html5/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
    sha256:59c86d5b2e452f63c5cdb29c866a12a4c55b1741d7025cf2f3ce0cde99b0660e
COMPONENT_CLASSIFICATION=Applications/System Utilities

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DTIDY_CONSOLE_SHARED=ON
CMAKE_OPTIONS += -DBUILD_TAB2SPACE=ON

# For some reason cmake does not install the tab2space binary,
# distribution 5.8.0 does not come with man-pages for libtidy.3
# and tab2space.1 therefore install at least the old ones.
COMPONENT_POST_INSTALL_ACTION += \
	($(CP) $(BUILD_DIR_64)/tab2space $(PROTOUSRBINDIR) ; \
	$(MKDIR) $(PROTOUSRSHAREMAN3DIR) ; \
	$(CP) $(COMPONENT_DIR)/files/tab2space.1 $(PROTOUSRSHAREMAN1DIR) ; \
	$(CP) $(COMPONENT_DIR)/files/libtidy.3 $(PROTOUSRSHAREMAN3DIR))


# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
