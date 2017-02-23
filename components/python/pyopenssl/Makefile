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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyOpenSSL
COMPONENT_VERSION=	16.2.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:7779a3bbb74e79db234af6a08775568c6769b5821faecf6e2f4143edb227516e
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_PROJECT_URL=  https://launchpad.net/pyopenssl
COMPONENT_BUGDB=	python-mod/pyopenssl
COMPONENT_ANITYA_ID=	5535

TPNO=			32834

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_PRE_TEST_ACTION = $(CP) -r $(COMPONENT_SRC)/tests $(@D)

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^\. lib/p" ' \
	'-e "/^\. tests/p" ' \
	'-e "/^s tests/p" ' \
	'-e "/^F tests/p" '

# In tests/test_crypto.py::FunctionTests::test_dump_certificate, the serial number line
# outputs the same hex as the key, so this is a false error.
# In tests/test_ssl.py::ConnectionTests::test_set_seesion_wrong_method, This test doesn't
# work for our version of OpenSSL, which is 1.0.2j; this test only supports OpenSSL 1.0.0
COMPONENT_TEST_DIR = $(@D)
COMPONENT_TEST_ENV += PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES.32):$(PYTHON_VENDOR_PACKAGES)
# Some tests require unicode characters, otherwise ~17 tests will fail
COMPONENT_TEST_ENV += LC_ALL=en_US.UTF-8
COMPONENT_TEST_CMD = py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS = --result-log=$(COMPONENT_TEST_OUTPUT)

# The pep8 and pyflakes output lines sometimes come in a different order.
COMPONENT_TEST_COMPARE_CMD = sort -o $(COMPONENT_TEST_SNAPSHOT) $(COMPONENT_TEST_SNAPSHOT); $(GDIFF) -uN

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		install $(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
