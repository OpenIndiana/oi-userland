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
# Copyright (c) 2021, 2022 Andreas Wacknitz
#

BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tox
COMPONENT_VERSION=	3.25.1
COMPONENT_SUMMARY=	Command line driven CI frontend and development task automation tool
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c138327815f53bc6da4fe56baec5f25f00622ae69ef3fe4e1e385720e22486f9
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://tox.wiki/
COMPONENT_FMRI=		library/python/tox
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	MIT

# tox is a tool so we provide only a single package
PYTHON_VERSIONS=	3.9
PYTHON_VERSION=		3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/in [0-9]*\.[0-9]*s //"' \
	'-e "s/[0-9]*:[0-9]*:[0-9]*//"' \
	'-n' \
	'-e "/===/p"' \
	'-e "/collected/p"' \
	'-e "/^ERROR/p"' \
	'-e "/^FAILED/p"' \
	'-e "/^SKIPPED/p"' \
	'-e "/^test_/p"'

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Test note: library/python/pytest-randomly-39 let the tests fail because of internal errors.

# Manually added test dependencies according to setup.cfg
REQUIRED_PACKAGES += library/python/filelock-39
REQUIRED_PACKAGES += library/python/flaky-39
REQUIRED_PACKAGES += library/python/freezegun-39
REQUIRED_PACKAGES += library/python/hypothesis-39
REQUIRED_PACKAGES += library/python/pluggy-39
REQUIRED_PACKAGES += library/python/psutil-39
REQUIRED_PACKAGES += library/python/py-39
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/pytest-benchmark-39
REQUIRED_PACKAGES += library/python/pytest-cov-39
REQUIRED_PACKAGES += library/python/pytest-mock-39
# Our pytest-randomly doesn't seem to work
#REQUIRED_PACKAGES += library/python/pytest-randomly-39
REQUIRED_PACKAGES += library/python/pytest-reporter-39
REQUIRED_PACKAGES += library/python/virtualenv-39

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-39
