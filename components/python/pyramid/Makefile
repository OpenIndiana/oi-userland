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
#   $WS_TOOLS/python-integrate-project pyramid
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyramid
HUMAN_VERSION =			2.0.1
COMPONENT_SUMMARY =		pyramid - The Pyramid Web Framework, a Pylons project
COMPONENT_PROJECT_URL =		https://trypyramid.com
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/05/c5/65f290930d67fafd38383571cffe69c38f42edc3026dcbfed60c527221e5/pyramid-2.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fabfd745039e26ad5b0915fc396e8725c0f8a3d17b941f9611ecd1ed76cfe7da
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hupper
PYTHON_REQUIRED_PACKAGES += library/python/plaster
PYTHON_REQUIRED_PACKAGES += library/python/plaster-pastedeploy
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/translationstring
PYTHON_REQUIRED_PACKAGES += library/python/venusian
PYTHON_REQUIRED_PACKAGES += library/python/webob
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += library/python/zope-deprecation
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/webtest
TEST_REQUIRED_PACKAGES.python += library/python/zope-component
