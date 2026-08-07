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
#   $WS_TOOLS/python-integrate-project -d python/Mako-39 mako
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mako
HUMAN_VERSION =			1.3.12
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A super-fast templating language that borrows the best ideas from the existing templating languages.
COMPONENT_PROJECT_URL =		https://www.makotemplates.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:9f778e93289bd410bb35daadeb4fc66d95a746f0b75777b942088b7fd7af550a
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Mako >= 1.4.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/markupsafe
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/babel
TEST_REQUIRED_PACKAGES.python += library/python/dogpile-cache
TEST_REQUIRED_PACKAGES.python += library/python/lingua
TEST_REQUIRED_PACKAGES.python += library/python/markupsafe
TEST_REQUIRED_PACKAGES.python += library/python/pygments
TEST_REQUIRED_PACKAGES.python += library/python/pytest
