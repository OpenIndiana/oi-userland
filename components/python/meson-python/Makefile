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
#   $WS_TOOLS/python-integrate-project -d python/meson-python meson_python
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		meson_python
HUMAN_VERSION =			0.17.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Meson Python build backend (PEP 517)
COMPONENT_ARCHIVE_HASH =	\
	sha256:efb91f69f2e19eef7bc9a471ed2a4e730088cc6b39eacaf3e49fc4f930eb5f83
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/meson
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pyproject-metadata
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += developer/object-file
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/cython
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
TEST_REQUIRED_PACKAGES.python += library/python/wheel
