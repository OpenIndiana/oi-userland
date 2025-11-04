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

CLONEY_ARGS= CLONEY_MODE="copy"
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xmlsec
COMPONENT_VERSION=	1.3.7
COMPONENT_SUMMARY=	XML Security Library
COMPONENT_PROJECT_URL=	https://www.aleksey.com/xmlsec
COMPONENT_SRC=	$(COMPONENT_NAME)1-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:d82e93b69b8aa205a616b62917a269322bf63a3eaafb3775014e61752b2013ea
COMPONENT_ARCHIVE_URL=	https://www.aleksey.com/xmlsec/download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/xmlsec
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	Copyright

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --enable-static=no

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^aleksey/p" ' \
	'-e "/^merlin/p" ' \
	'-e "/^phaos/p" ' \
	'-e "/xmldsig2ed/p" ' \
	'-e "/Test:/p" ' \
	'-e "/Skip/p" ' \
	'-e "/OK/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/mozilla-nss
