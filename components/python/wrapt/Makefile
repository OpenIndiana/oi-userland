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
# Copyright 2021 Gary Mills
#

BUILD_BITS = 64
BUILD_STYLE= setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wrapt
COMPONENT_VERSION=	1.13.2
COMPONENT_SUMMARY=	A transparent object proxy for Python
COMPONENT_PROJECT_URL=	https://github.com/GrahamDumpleton/wrapt
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:dca56cc5963a5fd7c2aa8607017753f534ee514e09103a6c55d2db70b50e7447
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_FMRI=		library/python/wrapt
COMPONENT_LICENSE=	BSD

PYTHON_VERSIONS=	3.7 3.9

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =    $(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =    $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/in [0-9]*\.[0-9]*s //"' \
	'-n' \
	'-e "/===/p"' \
	'-e "/collected/p"' \
	'-e "/^test_/p"'

# Manually added test dependencies:
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
REQUIRED_PACKAGES += system/library
