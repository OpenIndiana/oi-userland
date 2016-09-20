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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		M2Crypto
COMPONENT_VERSION=	0.24.0
COMPONENT_PROJECT_URL=	http://chandlerproject.org/Projects/MeTooCrypto/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:80a56441a1d2c0cf27e725be7554c92598b938fc8767ee2c71fdbc2fdc055ee8
COMPONENT_ARCHIVE_URL=	http://pypi.python.org/packages/source/M/M2Crypto/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/m2crypto

# Syntax issues: not Python 3 ready.
PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_ARGS =	setup.py test
COMPONENT_TEST_DIR =	$(COMPONENT_SRC)
COMPONENT_TEST_ENV=	CC=$(CC)
COMPONENT_TEST_ENV +=	PATH=/usr/bin
COMPONENT_TEST_ENV +=	PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES.32)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# tests.test_x509.X509TestCase fails with
# No such file or directory: 'tests/bad_date_cert.crt'
test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += developer/swig
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
