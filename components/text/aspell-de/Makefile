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
# Copyright 2022 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			aspell-de
COMPONENT_VERSION=		2016.12.7.7
HUMAN_VERSION=			20161207-7-0
COMPONENT_SUMMARY=		GNU Aspell spell english dictionaries
COMPONENT_PROJECT_URL=	https://ftp.gnu.org/gnu/aspell/dict/0index.html
COMPONENT_SRC=			aspell6-de-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:c2125d1fafb1d4effbe6c88d4e9127db59da9ed92639c7cbaeae1b7337655571
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/aspell/dict/de/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			text/aspell/de
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=		aspell-de Copyright
COMPONENT_LICENSE_FILE=	Copyright

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS= 

# Auto-generated dependencies
