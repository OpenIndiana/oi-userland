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
#   $WS_TOOLS/python-integrate-project zest.releaser
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zest.releaser
HUMAN_VERSION =			8.0.0
COMPONENT_SUMMARY =		zest.releaser - Software releasing made easy and repeatable
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e9/24/35f528cbe655961c6e71cf479ce11d6acfebf74ae2f9619261800ffdc26c/zest.releaser-8.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9b6495d02e594b318862f35cec84c596bf3fe37842db0009c39201f2ebcef809
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	LICENSE.GPL

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# zest.releaser --> zest.releaser
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Normalize random temporary directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/testtemp\)......../|\1XXXXXXXX/|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/colorama
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/twine
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/zest-releaser
