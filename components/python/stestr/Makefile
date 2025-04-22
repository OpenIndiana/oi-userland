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
#   $WS_TOOLS/python-integrate-project stestr
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		stestr
HUMAN_VERSION =			4.2.0
COMPONENT_SUMMARY =		A parallel Python test runner built around subunit
COMPONENT_PROJECT_URL =		https://stestr.readthedocs.io/en/stable/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/mtreinish/stestr/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ed533155fe0ab4dd10840037b9f8fcad697e269c655545a24efa756b3ac2a622
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# stestr is used to test stestr
USE_STESTR = yes

# Ignore stdout and stderr of successfull tests
TOX_POSARGS += --suppress-attachments

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cliff
PYTHON_REQUIRED_PACKAGES += library/python/fixtures
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/python-subunit
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/testtools
PYTHON_REQUIRED_PACKAGES += library/python/tomlkit
PYTHON_REQUIRED_PACKAGES += library/python/voluptuous
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/ddt
TEST_REQUIRED_PACKAGES.python += library/python/iso8601
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
