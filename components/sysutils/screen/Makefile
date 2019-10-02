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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2016, Adam Stevko. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		screen
COMPONENT_VERSION=	4.7.0
COMPONENT_SUMMARY=	GNU Screen terminal multiplexer
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/screen/
COMPONENT_FMRI=		terminal/screen
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:da775328fa783bd2a787d722014dbd99c6093effc11f337827604c2efc5d20c1
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/screen/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig	
COMPONENT_LICENSE= 	GPLv3+
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--enable-colors256
CONFIGURE_OPTIONS +=	--with-sys-screenrc=/etc/screenrc
CONFIGURE_OPTIONS +=	--disable-socket-dir
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)

PROTOTERMINFODIR=$(PROTOUSRSHAREDIR)/lib/terminfo

$(PROTOTERMINFODIR):
	$(MKDIR) $@

$(INSTALL_64):	$(PROTOTERMINFODIR)

# Build dependencies
REQUIRED_PACKAGES += text/texinfo

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
