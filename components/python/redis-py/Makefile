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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS = NO_ARCH
BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		redis
COMPONENT_VERSION=	3.4.1
COMPONENT_SUMMARY=	'The Python interface to the Redis key-value store'
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0dcfb335921b88a850d461dc255ff4708294943322bd55de6cfd68972490ca1f
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/andymccurdy/redis-py
COMPONENT_FMRI=		library/python/redis
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSIONS=	2.7 3.5

include $(WS_MAKE_RULES)/common.mk

# Python 2.7 tests fail
COMPONENT_TEST_DIR =    $(SOURCE_DIR)/tests
COMPONENT_TEST_ENV +=   $(PYTHON_ENV)
COMPONENT_TEST_ENV +=   PYTHONPATH=$(PROTO_DIR)/$(PYTHON_LIB)
COMPONENT_TEST_CMD =    $(PYTHON.$(BITS)) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS = 
