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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openca-ocspd
COMPONENT_VERSION=	3.1.2
# The new form includes the commit as a disambiguator, but the current archive
# wasn't created with that in its name, so we use the old form until the next
# update.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.openca.org/projects/ocspd/
COMPONENT_ARCHIVE_SRC=	git
COMPONENT_BUGDB=	library/smartcard

GIT_REPO= https://github.com/openca/openca-ocspd
GIT_COMMIT_ID= 0f16341
GIT_HASH=  sha256:0f894c7f19d658bdbda88887a3d748e8a968c6fd5cfc5f7be8ace9399b2f878d

TPNO =			28048

# Skip test because of set up requirements.
#
# The upstream archive includes a test script (test.sh), which tries to run
# "openssl ocsp" command multiple times. However, it assumes that we already
# have necessary pem files (keys/certficates for CA, ocspd daemon, and others,
# and also the CRL), and those files are not included in the archive.
#
# To test manually, follow a guide document for the smartcard project.
TEST_TARGET= $(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

PKG_PROTO_DIRS += $(COMPONENT_SRC)/docs
PKG_PROTO_DIRS += $(COMPONENT_SRC)/etc/ca.d

POD2MAN_PATH = /usr/perl5/$(PERL_VERSION)/bin

COMPONENT_BUILD_ENV +=  PATH="$(PATH):$(POD2MAN_PATH)"

COMPONENT_PRE_BUILD_ACTION = $(CP) $(COMPONENT_SRC)/docs/ocspd.3.pod $(@D)/docs

REQUIRED_PACKAGES += library/security/ocsp/libpki
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
