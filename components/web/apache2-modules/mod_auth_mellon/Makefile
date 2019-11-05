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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_auth_mellon
COMPONENT_VERSION=	0.14.2
COMPONENT_REVISION=	1
COMPONENT_FMRI=		web/server/apache-24/module/apache-mellon
COMPONENT_SUMMARY=	SAML2.0 authentication module for Apache
COMPONENT_CLASSIFICATION=	Web Services/Application and Web Servers
COMPONENT_PROJECT_URL=	https://github.com/Uninett/mod_auth_mellon
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8290ba57394fb7c551b9902c32bded8711f9656e2d36e351618b952f2c162afc
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

INSTALL_TARGET=	build
TEST_TARGET=	$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(CPP_XPG7MODE)
APXS = /usr/apache2/2.4/bin/apxs

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D)) && \
	(cd $(SOURCE_DIR); ./autogen.sh)

CONFIGURE_OPTIONS.APXS= --with-apxs2=$(APXS)
CONFIGURE_OPTIONS+=	--enable-diagnostics

REQUIRED_PACKAGES += web/server/apache-24

#Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lasso
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
