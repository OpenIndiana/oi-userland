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
#   $WS_TOOLS/python-integrate-project sphinxcontrib_applehelp
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sphinxcontrib_applehelp
HUMAN_VERSION =			1.0.8
COMPONENT_SUMMARY =		sphinxcontrib_applehelp - sphinxcontrib-applehelp is a Sphinx extension which outputs Apple help books
COMPONENT_PROJECT_URL =		https://www.sphinx-doc.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/26/6b/68f470fc337ed24043fec987b101f25b35010970bd958970c2ae5990859f/sphinxcontrib_applehelp-1.0.8.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:c40a4f96f3776c4393d933412053962fac2b84f4c99a7982ba42e09576a70619
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# sphinxcontrib-applehelp --> Sphinx ==> sphinxcontrib-applehelp
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
