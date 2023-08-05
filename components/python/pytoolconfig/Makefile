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
#   $WS_TOOLS/python-integrate-project pytoolconfig
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytoolconfig
HUMAN_VERSION =			1.2.5
COMPONENT_SUMMARY =		pytoolconfig - Python tool configuration
COMPONENT_PROJECT_URL =		https://github.com/bageljrkhanofemus/pytoolconfig
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/aa/ce/ac21cf0549ae05d8924e91f02f8b406e43beb42e605dc732fdf700f8cd8c/pytoolconfig-1.2.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a50f9dfe23b03a9d40414c1fdf902fefbeae12f2ac75a3c8f915944d6ffac279
COMPONENT_LICENSE =		LGPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# pytoolconfig --> pytoolconfig
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pdm-pep517
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/platformdirs
TEST_REQUIRED_PACKAGES.python += library/python/pytoolconfig
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/sphinx-autodoc-typehints
TEST_REQUIRED_PACKAGES.python += library/python/sphinx-rtd-theme
