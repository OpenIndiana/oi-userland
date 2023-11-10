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
#   $WS_TOOLS/python-integrate-project yamllint
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		yamllint
HUMAN_VERSION =			1.33.0
COMPONENT_SUMMARY =		yamllint - A linter for YAML files.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/fd/98/ec541c8dff395b9e441d46ab678c9a0f00f5ca479f070a6ced3b425cce79/yamllint-1.33.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2dceab9ef2d99518a2fcf4ffc964d44250ac4459be1ba3ca315118e4a1a81f7d
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/adrienverge/yamllint/issues/605
COMPONENT_TEST_ENV += HOME=/tmp

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pathspec
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
