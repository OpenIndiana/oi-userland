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
#   $WS_TOOLS/python-integrate-project defusedxml
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		defusedxml
HUMAN_VERSION =			0.7.1
COMPONENT_SUMMARY =		defusedxml - XML bomb protection for Python stdlib modules
COMPONENT_PROJECT_URL =		https://github.com/tiran/defusedxml
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/0f/d5/c66da9b79e5bdb124974bfe172b4daf3c984ebd9c2a06e2b8a4dc7331c72/defusedxml-0.7.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1bb3032db185915b62d7c6209c5a8792be6a32ab2fedacc84e01b52c51aa3e69
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/lxml
