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
#   $WS_TOOLS/python-integrate-project -d python/toml-fmt-common-39 toml_fmt_common
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		toml_fmt_common
HUMAN_VERSION =			1.0.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Common logic to the TOML formatter.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/toml-fmt-common
COMPONENT_ARCHIVE_HASH =	\
	sha256:7a29e99e527ffac456043296a0f1d8c03aaa1b06167bd39ad5e3cc5041f31c17
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# toml-fmt-common >= 1.1.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
