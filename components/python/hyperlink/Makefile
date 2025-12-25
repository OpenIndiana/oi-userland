#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project hyperlink
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		hyperlink
HUMAN_VERSION =			21.0.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		A featureful, immutable, and correct URL for Python.
COMPONENT_PROJECT_URL =		https://github.com/python-hyper/hyperlink
COMPONENT_ARCHIVE_HASH =	\
	sha256:427af957daa58bc909471c6c40f74c5450fa123dd093fc53efd2e91d2705a56b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/python-hyper/hyperlink/issues/186
PYTEST_ADDOPTS += --deselect src/hyperlink/test/test_hypothesis.py::TestHypothesisStrategies::test_hostname_labels_valid_ascii
PYTEST_ADDOPTS += --deselect src/hyperlink/test/test_hypothesis.py::TestHypothesisStrategies::test_hostnames_ascii
PYTEST_ADDOPTS += --deselect src/hyperlink/test/test_hypothesis.py::TestHypothesisStrategies::test_hostnames_ascii_nolead

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/idna
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/idna
TEST_REQUIRED_PACKAGES.python += library/python/pytest
