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
#   $WS_TOOLS/python-integrate-project -d python/zest.releaser zest_releaser
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zest_releaser
HUMAN_VERSION =			9.3.0
COMPONENT_SUMMARY =		Software releasing made easy and repeatable
COMPONENT_ARCHIVE_HASH =	\
	sha256:e66bc85d0edd6fc6f4317da2f00e6af05f33b4eb3c2086bf5217da8f7ae47c16
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	LICENSE.GPL

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/build
PYTHON_REQUIRED_PACKAGES += library/python/cmarkgfm
PYTHON_REQUIRED_PACKAGES += library/python/colorama
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/readme-renderer
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/twine
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/check-manifest
TEST_REQUIRED_PACKAGES.python += library/python/pep440
TEST_REQUIRED_PACKAGES.python += library/python/pyroma
TEST_REQUIRED_PACKAGES.python += library/python/wheel
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
