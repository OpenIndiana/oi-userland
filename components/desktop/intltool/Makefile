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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		intltool
COMPONENT_VERSION=	0.51.0
COMPONENT_PROJECT_URL=	http://freedesktop.org/wiki/Software/intltool/
COMPONENT_ARCHIVE_HASH= \
    sha256:67c74d94196b153b774ab9f89b2fa6c6ba79352407037c8c14d5aeb334e959cd
COMPONENT_ARCHIVE_URL=	https://launchpad.net/$(COMPONENT_NAME)/trunk/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)

TPNO=			25211

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += PERL="$(PERL)"
PKG_MACROS += PERLVER="$(PERL_VERSION)"

PERL_XML_PARSER_PKG = $(PERL_VERSION:5.%=library/perl-5/xml-parser-5%) 

REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += $(PERL_XML_PARSER_PKG)
REQUIRED_PACKAGES += text/gnu-gettext

