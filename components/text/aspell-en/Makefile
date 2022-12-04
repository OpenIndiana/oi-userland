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
# Copyright 2013 Alexander Pyhalov
# Copyright 2022 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			aspell-en
COMPONENT_VERSION=		2020.12.7
HUMAN_VERSION=			2020.12.07-0
COMPONENT_SUMMARY=		GNU Aspell spell english dictionaries
COMPONENT_PROJECT_URL=	https://ftp.gnu.org/gnu/aspell/dict/0index.html
COMPONENT_SRC=			aspell6-en-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:4c8f734a28a088b88bb6481fcf972d0b2c3dc8da944f7673283ce487eac49fb3
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/aspell/dict/en/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			text/aspell/en
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=		aspell-en Copyright
COMPONENT_LICENSE_FILE=	Copyright

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS= 

# Auto-generated dependencies
