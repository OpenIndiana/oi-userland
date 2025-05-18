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
# Copyright (c) 2008, 2019, Oracle and/or its affiliates. All rights reserved.
#

FONT_TYPE=X11
BUILD_STYLE=configure
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		font-misc-cyrillic
COMPONENT_VERSION= 	1.0.3
COMPONENT_REVISION=	3
COMPONENT_ARCHIVE_HASH=	\
	sha256:e40fe3e3323c62b738550795457ad555c70c008aa91b5912dfd46f8e745f5e60

# Use font-screen-cyrillic version number as solaris-userland does
IPS_COMPONENT_VERSION= 1.0.4

include $(WS_MAKE_RULES)/font.mk

CYRILLIC_FONT_DIR = $(USRSHAREX11FONTSDIR)/cyrillic

# Install to separate directory for easier packaging
CONFIGURE_OPTIONS += --with-fontdir=$(CYRILLIC_FONT_DIR)

# Auto-generated dependencies
