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
#   $WS_TOOLS/python-integrate-project email_validator
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		email_validator
HUMAN_VERSION =			2.4.0
COMPONENT_SUMMARY =		A robust email address syntax and deliverability validation library.
COMPONENT_PROJECT_URL =		https://github.com/JoshData/python-email-validator
COMPONENT_ARCHIVE_HASH =	\
	sha256:be487bc50bc3bd832a98515a55a15649d9bec06d954fa178663190714b6c4ee1
COMPONENT_LICENSE =		Unlicense
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# Python 3.9 is not supported by email-validator >= 2.4.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/dnspython
REQUIRED_PACKAGES.python += library/python/idna
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
