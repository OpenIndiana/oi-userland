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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		python-ldap
COMPONENT_VERSION=	2.4.25
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:62d00dbc86f3f9b21beacd9b826e8f9895f900637a60a6d4e7ab59a1cdc64e56
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://www.python-ldap.org/
COMPONENT_BUGDB=	python-mod/python-ldap

TPNO=			29571

# This module has syntax issues and thus is not Python 3 ready.
PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR =    $(SOURCE_DIR)/Tests
COMPONENT_TEST_CMD =	$(SHELL)
COMPONENT_TEST_ARGS =   runtests.sh
COMPONENT_TEST_ENV +=	PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES.32)
# Needed to create a unique temporary directory.
COMPONENT_TEST_ENV +=	BUILD_DIR=$(BUILD_DIR)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Two tests are known to fail. These failures are not critical.
#
# One fails because it says the library does not throw a value error on a
# bad URL. This one fails, as the bad url it is trying is an edge case:
# ldap:///?????  and not that important.  The OpenLDAP library doesn't 
# have the necessary code to check for that case and error out.  We (or
# someone from the python-ldap team) would have to log an OpenLDAP bug,
# propose a fix to the code, see it integrated, wait for a release, and
# integrate the new release into Userland.
#
# The other failure is for a test case that has a comment before the test case:
# # these two constants are pointless? XXX
# The answer being yes.  And the constants are not defined in the latest
# version of python-ldap.
# 
test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/python/pyasn1-27
REQUIRED_PACKAGES += library/python/pyasn1-modules-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/network/ldap/openldap
