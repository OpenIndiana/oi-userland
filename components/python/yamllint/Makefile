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
HUMAN_VERSION =			1.32.0
COMPONENT_SUMMARY =		yamllint - A linter for YAML files.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/29/50/fd0b7b1e1f36327521909236df2d6795baebc30b4a0cb943531ff6734eb7/yamllint-1.32.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d01dde008c65de5b235188ab3110bebc59d18e5c65fc8a58267cd211cd9df34a
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
