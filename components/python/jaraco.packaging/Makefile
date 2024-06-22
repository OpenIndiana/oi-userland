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
#   $WS_TOOLS/python-integrate-project jaraco.packaging
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jaraco.packaging
HUMAN_VERSION =			10.2.2
COMPONENT_SUMMARY =		tools to supplement packaging Python releases
COMPONENT_PROJECT_URL =		https://github.com/jaraco/jaraco.packaging
COMPONENT_ARCHIVE_HASH =	\
	sha256:05302a4f8457b74971e7cc220df30fdf79b4fac31601e1b0dc439fff985a3040
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =			jaraco_packaging-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/build
PYTHON_REQUIRED_PACKAGES += library/python/domdf-python-tools
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-context
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/sphinx
PYTHON_REQUIRED_PACKAGES += library/python/virtualenv
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
TEST_REQUIRED_PACKAGES.python += library/python/types-docutils
