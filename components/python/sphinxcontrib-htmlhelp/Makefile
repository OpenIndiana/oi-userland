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

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sphinxcontrib-htmlhelp
HUMAN_VERSION =			2.0.1
COMPONENT_SUMMARY =		sphinxcontrib-htmlhelp - sphinxcontrib-htmlhelp is a sphinx extension which renders HTML help files
COMPONENT_PROJECT_URL =		https://www.sphinx-doc.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b3/47/64cff68ea3aa450c373301e5bebfbb9fce0a3e70aca245fcadd4af06cd75/sphinxcontrib-htmlhelp-2.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0cbdd302815330058422b98a113195c9249825d681e18f11e8b1f78a2f11efff
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# sphinxcontrib-htmlhelp --> Sphinx ==> sphinxcontrib-htmlhelp
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/html5lib
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
