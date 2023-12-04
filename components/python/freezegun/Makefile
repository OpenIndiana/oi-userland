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
#   $WS_TOOLS/python-integrate-project freezegun
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		freezegun
HUMAN_VERSION =			1.3.0
COMPONENT_SUMMARY =		freezegun - Let your Python tests travel through time
COMPONENT_PROJECT_URL =		https://github.com/spulec/freezegun
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/1a/16/4891239e9f05aa2630d5dfd6609f1b7b5720c20ab5c97be4ef9805049a77/freezegun-1.3.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:56cc5dc34de38fe28a4d19bea65bbd3af6fd66020df8141b92bdb45c9be9f503
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/python-dateutil
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coveralls
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/python-dateutil
