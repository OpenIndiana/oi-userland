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
#   $WS_TOOLS/python-integrate-project pip
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pip
HUMAN_VERSION =			23.3.1
COMPONENT_SUMMARY =		pip - The PyPA recommended tool for installing Python packages.
COMPONENT_PROJECT_URL =		https://pip.pypa.io/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/pypa/pip/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4192f1ed5f8f1e01557d8c02ffd845c64d4a4567e0864ca78b74b0b5456c0f62
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# usr/bin/pip3.x needs to be handled separately because we have no generic
# rules covering it
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's/\(usr\/bin\/pip\)3\.[0-9]\{1,\}$$/\1$$(PYVER)/' | uniq

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += tests/requirements.txt

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cryptography
TEST_REQUIRED_PACKAGES.python += library/python/freezegun
TEST_REQUIRED_PACKAGES.python += library/python/installer
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-rerunfailures
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/scripttest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/tomli-w
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/werkzeug
TEST_REQUIRED_PACKAGES.python += library/python/wheel
