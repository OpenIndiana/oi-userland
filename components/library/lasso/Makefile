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

USE_OPENSSL11= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= lasso
COMPONENT_VERSION= 2.8.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Lasso - library implementing the SAML 2.0 and ID-FF 1.2 protocols
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL= https://dev.entrouvert.org/projects/lasso
COMPONENT_ARCHIVE_HASH= sha256:ffcbd5851d98586c7e1caf43bad66164211a3b61d12bf860a0598448ff9f2b38
COMPONENT_ARCHIVE_URL= https://dev.entrouvert.org/releases/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/lasso
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-perl
CONFIGURE_OPTIONS += --disable-java
CONFIGURE_OPTIONS += --disable-python
CONFIGURE_OPTIONS += --with-pkg-config=$(PKG_CONFIG_PATH.$(BITS))
CONFIGURE_OPTIONS += CPPFLAGS=-I$(OPENSSL_INCDIR)
CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_LIBDIR)

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/xmlsec
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
