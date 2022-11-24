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
#   $WS_TOOLS/python-integrate-project sphinxcontrib-htmlhelp
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sphinxcontrib-htmlhelp
COMPONENT_VERSION =		2.0.0
COMPONENT_SUMMARY =		sphinxcontrib-htmlhelp - sphinxcontrib-htmlhelp is a sphinx extension which renders HTML help files
COMPONENT_PROJECT_URL =		http://sphinx-doc.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/eb/85/93464ac9bd43d248e7c74573d58a791d48c475230bcf000df2b2700b9027/sphinxcontrib-htmlhelp-2.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f5f8bb2d0d629f398bf47d0d69c07bc13b65f75a81ad9e2f71a63d4b7a2f6db2
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# sphinxcontrib-htmlhelp needs sphinx to run tests, but sphinx needs
# sphinxcontrib-htmlhelp to build itself.  This is special case when we need to
# set PYTHON_TEST_BOOTSTRAP to make sure the sphinxcontrib-htmlhelp tests are
# not run when there is no sphinx available yet.
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/html5lib
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
