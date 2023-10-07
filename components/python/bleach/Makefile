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
HUMAN_VERSION =			6.1.0
COMPONENT_SUMMARY =		bleach - An easy safelist-based HTML-sanitizing tool.
COMPONENT_PROJECT_URL =		https://github.com/mozilla/bleach
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/6d/10/77f32b088738f40d4f5be801daa5f327879eadd4562f36a2b5ab975ae571/bleach-6.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0a31f1837963c41d46bbf1331b8778e1308ea0791db03cc4e7357b97cf42a8fe
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
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/twine
TEST_REQUIRED_PACKAGES.python += library/python/wheel
