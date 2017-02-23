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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tox
COMPONENT_VERSION=	2.3.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bf7fcc140863820700d3ccd65b33820ba747b61c5fe4e2b91bb8c64cb21a47ee
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://tox.testrun.org/
COMPONENT_BUGDB=	python-mod/tox
COMPONENT_ANITYA_ID=	13221

TPNO=			29209

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_INSTALL_ACTION += (cd $(PROTO_DIR)/usr/bin ; \
	$(MV) -f tox tox-$(PYTHON_VERSION); \
	$(MV) -f tox-quickstart tox-quickstart-$(PYTHON_VERSION))

COMPONENT_TEST_ENV +=	HOME=$(HOME)
COMPONENT_TEST_ENV +=	PATH=/usr/bin
COMPONENT_TEST_DIR =	$(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =	$(PROTOUSRBINDIR)/tox-$(PYTHON_VERSION)
# Tox normally runs all test environments at once, which means that with one
# test target per Python version, we run all environments for each.  So we
# restrict the Python versions to the one corresponding to the test target.
PYV = $(shell echo $(PYTHON_VERSION) | tr -d .)
COMPONENT_TEST_ARGS =	-e $(PYV:%=py%)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
