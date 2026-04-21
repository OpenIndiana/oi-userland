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
#   $WS_TOOLS/python-integrate-project pymongo
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pymongo
HUMAN_VERSION =			4.17.0
COMPONENT_REVISION =		19
COMPONENT_SUMMARY =		PyMongo - the Official MongoDB Python driver
COMPONENT_PROJECT_URL =		https://www.mongodb.org
COMPONENT_ARCHIVE_HASH =	\
	sha256:70ffa08ba641468cc068cf46c06b34f01a8ce3489f6411309fcb5ceabe6b2fc0
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# The 10.10.10.10 version was briefly available at PyPI and so we packaged it.
# It later disappeared because it was created mistakenly but since IPS cannot
# downgrade we need to keep it.
COMPONENT_VERSION =		10.10.10.10

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += requirements/test.txt

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/dnspython
REQUIRED_PACKAGES.python += library/python/hatch-requirements-txt
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
