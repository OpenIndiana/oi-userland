#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021 Aurelien Larcher
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pytest-benchmark
COMPONENT_VERSION=	3.4.1
COMPONENT_SUMMARY=	A pytest fixture for benchmarking code.
COMPONENT_PROJECT_URL=	https://github.com/ionelmc/pytest-benchmark
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:40e263f912de5a81d891619032983557d62a3d85843f9a9f30b98baea0cd7b47
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_FMRI=		library/python/$(COMPONENT_NAME)
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS= $(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION += \
($(MV) $(PROTOUSRBINDIR)/py.test-benchmark $(PROTOUSRBINDIR)/py.test-benchmark-$(PYTHON_VERSION); \
 $(MV) $(PROTOUSRBINDIR)/pytest-benchmark $(PROTOUSRBINDIR)/pytest-benchmark-$(PYTHON_VERSION))

COMPONENT_TEST_DIR =	$(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =	test_benchmark.py

COMPONENT_TEST_TRANSFORMS += '-n -e "/\.\.\./p"'

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
