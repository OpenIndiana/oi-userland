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
#   $WS_TOOLS/python-integrate-project pyproject_hooks
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyproject_hooks
HUMAN_VERSION =			1.2.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Wrappers to call pyproject.toml-based build backend hooks.
COMPONENT_ARCHIVE_HASH =	\
	sha256:1e859bd5c40fae9448642dd871adf459e5e2084186e8d2c2a79a824c970da1f8
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += dev-requirements.txt

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/testpath
TEST_REQUIRED_PACKAGES.python += library/python/tomli
