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
#   $WS_TOOLS/python-integrate-project bleach
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		bleach
HUMAN_VERSION =			6.0.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		bleach - An easy safelist-based HTML-sanitizing tool.
COMPONENT_PROJECT_URL =		https://github.com/mozilla/bleach
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/7e/e6/d5f220ca638f6a25557a611860482cb6e54b2d97f0332966b1b005742e1f/bleach-6.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1a1a85c1595e07d8db14c5f09f09e6433502c51c595970edc090551f0db99414
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# bleach --> twine ==> readme_renderer ==> bleach
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/six
PYTHON_REQUIRED_PACKAGES += library/python/webencodings
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/twine
TEST_REQUIRED_PACKAGES.python += library/python/wheel
