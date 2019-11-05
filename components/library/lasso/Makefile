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

COMPONENT_NAME=	lasso
COMPONENT_VERSION=	2.6.0
COMPONENT_FMRI=	library/lasso
COMPONENT_SUMMARY=	Lasso - library implementing the SAML 2.0 and ID-FF 1.2 protocols
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://dev.entrouvert.org/projects/lasso
COMPONENT_ARCHIVE_HASH=	sha256:146bff7a25166467d960003346cbc3291f3f29067e305cb82ebb12354c7d0acf
COMPONENT_ARCHIVE_URL=	https://dev.entrouvert.org/releases/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

PATH=	$(PATH.gnu)
TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--disable-perl
CONFIGURE_OPTIONS +=	--disable-java
CONFIGURE_OPTIONS +=	--disable-python
CONFIGURE_OPTIONS +=	--with-pkg-config=$(PKG_CONFIG_PATH.$(BITS))

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/xmlsec
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
