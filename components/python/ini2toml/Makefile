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
#   $WS_TOOLS/python-integrate-project ini2toml
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ini2toml
HUMAN_VERSION =			0.12
COMPONENT_SUMMARY =		ini2toml - Automatically conversion of .ini/.cfg files to TOML equivalents
COMPONENT_PROJECT_URL =		https://github.com/abravalheri/ini2toml/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/3a/ca/60ae0f9e348e0d13b2ec378f3af4cc7d448222b2e32361a12fb4d32dd546/ini2toml-0.12.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d459d535878e0fb95cd0b0c3889f056b7ff3903e82e919d394e9f85b7167f5ec
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Testing fails with the checkdocs plugin installed
PYTEST_ADDOPTS += -p no:checkdocs

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/configupdater
TEST_REQUIRED_PACKAGES.python += library/python/pyproject-fmt
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/tomli-w
TEST_REQUIRED_PACKAGES.python += library/python/tomlkit
TEST_REQUIRED_PACKAGES.python += library/python/validate-pyproject
