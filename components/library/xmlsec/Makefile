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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xmlsec
COMPONENT_VERSION=	1.2.29
COMPONENT_PROJECT_URL=	https://www.aleksey.com/xmlsec
COMPONENT_FMRI=		library/xmlsec
COMPONENT_SUMMARY=	XML Security Library
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SRC=	$(COMPONENT_NAME)1-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:b1d1deba966019930f608d1f2b95c40ca3450f1393bcd3a3c001a8ba1d2839ab
COMPONENT_ARCHIVE_URL=	http://www.aleksey.com/xmlsec/download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	Copyright

PATH=	$(PATH.gnu)

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Make docs does not like cloney, so a simple copy is used instead.
COMPONENT_PRE_CONFIGURE_ACTION= \
	$(CP) -rp $(SOURCE_DIR)/. $(@D)

CONFIGURE_OPTIONS +=	--enable-static=no

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += system/library/security/libgcrypt
