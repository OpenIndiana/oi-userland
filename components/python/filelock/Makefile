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
# Copyright (c) 2021, Andreas Wacknitz
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		filelock
COMPONENT_VERSION=	3.3.1
COMPONENT_SUMMARY=	A platform independent file lock that supports the with-statement
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:34a9f35f95c441e7b38209775d6e0337f9a3759f3565f6c5798f19618527c76f
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/tox-dev/py-filelock
COMPONENT_FMRI=		library/python/filelock
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	Unlicense

PYTHON_VERSIONS=	3.7 3.9
include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/in [0-9]*\.[0-9]*s //"' \
	'-n' \
	'-e "/===/p"' \
	'-e "/collected/p"' \
	'-e "/test_/p"'

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/flaky
REQUIRED_PACKAGES += library/python/hypothesis
REQUIRED_PACKAGES += library/python/pluggy
REQUIRED_PACKAGES += library/python/py
REQUIRED_PACKAGES += library/python/pytest
REQUIRED_PACKAGES += library/python/pytest-benchmark
REQUIRED_PACKAGES += library/python/pytest-reporter

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
