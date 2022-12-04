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
# Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=	64
USE_OPENSSL11= yes
CLONEY_ARGS= CLONEY_MODE="copy"
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xmlsec
COMPONENT_VERSION=	1.2.37
COMPONENT_PROJECT_URL=	https://www.aleksey.com/xmlsec
COMPONENT_FMRI=		library/xmlsec
COMPONENT_SUMMARY=	XML Security Library
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SRC=	$(COMPONENT_NAME)1-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5f8dfbcb6d1e56bddd0b5ec2e00a3d0ca5342a9f57c24dffde5c796b2be2871c
COMPONENT_ARCHIVE_URL=	https://www.aleksey.com/xmlsec/download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	Copyright

PATH=	$(PATH.gnu)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--enable-static=no

COMPONENT_TEST_TRANSFORMS = \
	'-n ' \
	'-e "/^aleksey/p" ' \
	'-e "/^merlin/p" ' \
	'-e "/^phaos/p" ' \
	'-e "/xmldsig2ed/p" ' \
	'-e "/Test:/p" ' \
	'-e "/Fail/p" ' \
	'-e "/Skip/p" ' \
	'-e "/OK/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += system/library/security/libgcrypt
