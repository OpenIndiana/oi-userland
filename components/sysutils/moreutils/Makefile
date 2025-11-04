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
# Copyright 2023 Andreas Wacknitz
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		moreutils
COMPONENT_VERSION=	0.70
COMPONENT_SUMMARY=	moreutils is a collection of the unix tools that nobody thought to write long ago when unix was young
COMPONENT_PROJECT_URL=	https://joeyh.name/code/moreutils
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f2bf46d410ba567cc8d01507e94916994e48742722e690dc498fab59f5250132
COMPONENT_ARCHIVE_URL=	https://git.joeyh.name/index.cgi/moreutils.git/snapshot/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS   += $(XPG6MODE)
LDFLAGS  += -lsocket -lnsl

COMPONENT_BUILD_ENV += DOCBOOKXSL="/usr/share/sgml/docbook/xsl-stylesheets"

COMPONENT_TEST_TRANSFORMS = \
	' -n ' \
	' -e "/OK/p" '

# Manually added build dependencies
REQUIRED_PACKAGES += data/docbook/xsl

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
