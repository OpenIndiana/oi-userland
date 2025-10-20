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
#   $WS_TOOLS/python-integrate-project UkPostcodeParser
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		UkPostcodeParser
HUMAN_VERSION =			1.1.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		UK Postcode parser
COMPONENT_PROJECT_URL =		https://github.com/hamstah/ukpostcodeparser
COMPONENT_ARCHIVE_HASH =	\
	sha256:930264efa293db80af0103a4fe9c161b06365598d24bb6fe5403f3f57c70530e
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Tests use non-default naming convention
PYTEST_ADDOPTS += -o python_files=test/*.py

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
