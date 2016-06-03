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

COMPONENT_NAME=		libpki
COMPONENT_VERSION=	0.8.9
COMPONENT_PROJECT_URL=	https://www.openca.org/projects/libpki/
COMPONENT_ARCHIVE_SRC=	git
COMPONENT_BUGDB=	library/smartcard

GIT_REPO= https://github.com/openca/libpki
GIT_COMMIT_ID= b46aebc
GIT_HASH=  sha256:16e84a529f0871dcff175c717cf472bdad0de0a4719bf1f204d49d9011eace2c

TPNO =			26905

include $(WS_MAKE_RULES)/common.mk

PKG_PROTO_DIRS += $(COMPONENT_SRC)/docs

# This is necessary because 'gmake install' tries to install some files under
# /usr/bin without it.
CONFIGURE_ENV +=	DESTDIR="$(PROTO_DIR)"

CONFIGURE_OPTIONS +=	--with-libdir=$(USRLIBDIR64)
CONFIGURE_OPTIONS +=	--with-lib-prefix=$(USRLIBDIR64)

COMPONENT_PRE_TEST_ACTION = files/setup_test.sh $(@D) $(COMPONENT_SRC)

# Tests may output some compilation lines, so just pull out the relevant test
# output lines for the test results comparison.
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/\# TOTAL:/p" ' \
	'-e "/\# PASS:/p" ' \
	'-e "/\# SKIP:/p" ' \
	'-e "/\# XFAIL:/p" ' \
	'-e "/\# FAIL:/p" ' \
	'-e "/\# XPASS:/p" ' \
	'-e "/\# ERROR:/p" '

REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/network/ldap/openldap
