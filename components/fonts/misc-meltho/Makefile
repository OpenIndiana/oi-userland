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
# Copyright (c) 2008, 2018, Oracle and/or its affiliates. All rights reserved.
# COpyright 2018, Aurelien Larcher
#
BUILD_STYLE=configure

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		font-misc-meltho
COMPONENT_VERSION= 	1.0.4
COMPONENT_SUMMARY=      Meltho Syriac fonts
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:63be5ec17078898f263c24096a68b43ae5b06b88852e42549afa03d124d65219
COMPONENT_LICENSE=      Meltho fonts license
COMPONENT_LICENSE_FILE= COPYING

FONT_TYPE = X11MISC

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_NAME = syriac
COMPONENT_FONT_PKG  = misc-meltho

# Install to separate directory for easier packaging
CONFIGURE_OPTIONS += --with-fontdir=$(USRSHARETTFFONTSDIR)/$(COMPONENT_FONT_NAME)

# Auto-generated dependencies
