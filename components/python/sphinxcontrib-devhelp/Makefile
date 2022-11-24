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
#   $WS_TOOLS/python-integrate-project sphinxcontrib-devhelp
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sphinxcontrib-devhelp
COMPONENT_VERSION =		1.0.2
COMPONENT_SUMMARY =		sphinxcontrib-devhelp - sphinxcontrib-devhelp is a sphinx extension which outputs Devhelp document.
COMPONENT_PROJECT_URL =		http://sphinx-doc.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/98/33/dc28393f16385f722c893cb55539c641c9aaec8d1bc1c15b69ce0ac2dbb3/sphinxcontrib-devhelp-1.0.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ff7f1afa7b9642e7060379360a67e9c41e8f3121f2ce9164266f61b9f4b338e4
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# sphinxcontrib-devhelp needs sphinx to run tests, but sphinx needs
# sphinxcontrib-devhelp to build itself.  This is special case when we need to
# set PYTHON_TEST_BOOTSTRAP to make sure the sphinxcontrib-devhelp tests are
# not run when there is no sphinx available yet.
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
