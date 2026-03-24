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
#   $WS_TOOLS/python-integrate-project plaster
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		plaster
HUMAN_VERSION =			1.1.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A loader interface around multiple config file formats.
COMPONENT_PROJECT_URL =		https://docs.pylonsproject.org/projects/plaster/en/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:f8befc54bf8c1147c10ab40297ec84c2676fa2d4ea5d6f524d9436a80074ef98
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# With plaster installed the testing finds both the installed and the currently
# built plaster which is unexpected and so some tests fails.
TEST_CONFLICTING_PACKAGES.python += library/python/plaster

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
