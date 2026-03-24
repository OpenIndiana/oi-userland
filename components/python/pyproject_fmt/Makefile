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
#   $WS_TOOLS/python-integrate-project pyproject_fmt
#

BUILD_STYLE = pyproject
CARGO_VENDOR = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyproject_fmt
HUMAN_VERSION =			2.11.1
COMPONENT_SUMMARY =		Format your pyproject.toml file
COMPONENT_ARCHIVE_HASH =	\
	sha256:86f4ebc71d658b848bd14da5f2d2f156a238687e5c9adc0e787ecbf925fd24b1
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

# Python 3.9 is not supported by pyproject-fmt >= 2.9.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# During testing the /usr/bin is added to PATH (due to a bug) and so when we
# try to run pyproject-fmt we always run the installed one, not the currently
# built one in the proto area.
#
# See also https://github.com/fedora-python/tox-current-env/issues/68
TEST_CONFLICTING_PACKAGES.python += library/python/pyproject-fmt

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += test

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/maturin
REQUIRED_PACKAGES.python += library/python/toml-fmt-common
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
