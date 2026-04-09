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
# Copyright (c) 2013, Louis M. Picciano. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         joe
COMPONENT_VERSION=      4.7
COMPONENT_SUMMARY=		Joe's Own Editor - a full featured terminal-based screen editor
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://joe-editor.sourceforge.net/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:712b23a83a3757a93d2b4a76325b9dabba554c182b209d2675537c272867fcba
COMPONENT_ARCHIVE_URL=  http://downloads.sourceforge.net/project/joe-editor/JOE%20sources/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         editor/joe
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -Wno-error=incompatible-pointer-types

COMPONENT_PREP_ACTION += ( cd $(@D) && autoreconf -f )

# Joe uses incorrect relative paths
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
