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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zest.releaser
HUMAN_VERSION =			9.1.2
COMPONENT_SUMMARY =		zest.releaser - Software releasing made easy and repeatable
COMPONENT_ARCHIVE_HASH =	\
	sha256:3d0c832a452176a1767c6cc137f64a0e8f093cd330bfd9fb2251a633a8de5be4
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	LICENSE.GPL

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Normalize random temporary directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/testtemp\)......../|\1XXXXXXXX/|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/build
PYTHON_REQUIRED_PACKAGES += library/python/cmarkgfm
PYTHON_REQUIRED_PACKAGES += library/python/colorama
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
