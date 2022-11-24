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
#   $WS_TOOLS/python-integrate-project sphinxcontrib-applehelp
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sphinxcontrib-applehelp
COMPONENT_VERSION =		1.0.2
COMPONENT_SUMMARY =		sphinxcontrib-applehelp - sphinxcontrib-applehelp is a sphinx extension which outputs Apple help books
COMPONENT_PROJECT_URL =		http://sphinx-doc.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/9f/01/ad9d4ebbceddbed9979ab4a89ddb78c9760e74e6757b1880f1b2760e8295/sphinxcontrib-applehelp-1.0.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a072735ec80e7675e3f432fcae8610ecf509c5f1869d17e2eecff44389cdbc58
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# sphinxcontrib-applehelp needs sphinx to run tests, but sphinx needs
# sphinxcontrib-applehelp to build itself.  This is special case when we need
# to set PYTHON_TEST_BOOTSTRAP to make sure the sphinxcontrib-applehelp tests
# are not run when there is no sphinx available yet.
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/html5lib
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
