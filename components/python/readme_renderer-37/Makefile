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
#   $WS_TOOLS/python-integrate-project readme_renderer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		readme_renderer
HUMAN_VERSION =			37.3
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		readme_renderer - readme_renderer is a library for rendering \\\\\\\"readme\\\\\\\" descriptions for Warehouse
COMPONENT_PROJECT_URL =		https://github.com/pypa/readme_renderer
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/81/c3/d20152fcd1986117b898f66928938f329d0c91ddc47f081c58e64e0f51dc/readme_renderer-37.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:cd653186dfc73055656f090f227f5cb22a046d7f71a841dfa305f55c9a513273
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# readme_renderer >= 40.0 requires Python >= 3.8
PYTHON_VERSIONS = 3.7

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/bleach
PYTHON_REQUIRED_PACKAGES += library/python/docutils
PYTHON_REQUIRED_PACKAGES += library/python/pygments
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cmarkgfm
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
