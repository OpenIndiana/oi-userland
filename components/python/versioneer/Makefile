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
#   $WS_TOOLS/python-integrate-project versioneer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		versioneer
HUMAN_VERSION =			0.29
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Easy VCS-based management of project version strings
COMPONENT_PROJECT_URL =		https://github.com/python-versioneer/python-versioneer
COMPONENT_ARCHIVE_HASH =	\
	sha256:5ab283b9857211d61b53318b7c792cf68e798e765ee17c27ade9f6c924235731
COMPONENT_LICENSE =		Unlicense
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Contains timestamp
COMPONENT_TEST_TRANSFORMS += "-e '/listing git files failed/d'"
# Random temporary directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/tmp\).\{8\}/|\1XXXXXXXX/|g'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/types-setuptools
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
