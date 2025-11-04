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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyproject_fmt
HUMAN_VERSION =			2.7.0
COMPONENT_SUMMARY =		Format your pyproject.toml file
COMPONENT_ARCHIVE_URL =		\
	https://github.com/tox-dev/toml-fmt/archive/refs/tags/pyproject-fmt/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3dbe43d000a3f267e5b4365bc0eb144a6690de86b046b6ff903655bd71f830f9
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_SRC = toml-fmt-pyproject-fmt-$(HUMAN_VERSION)
COMPONENT_SUBDIR = pyproject-fmt

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# During testing the /usr/bin is added to PATH (due to a bug) and so when we
# try to run pyproject-fmt we always run the installed one, not the currently
# built one in the proto area.
#
# See also https://github.com/fedora-python/tox-current-env/issues/68
TEST_CONFLICTING_PACKAGES.python += library/python/pyproject-fmt

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/maturin
REQUIRED_PACKAGES.python += library/python/toml-fmt-common
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
