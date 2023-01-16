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
#   $WS_TOOLS/python-integrate-project PasteDeploy
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PasteDeploy
HUMAN_VERSION =			3.0.1
COMPONENT_SUMMARY =		PasteDeploy - Load, configure, and compose WSGI applications and servers
COMPONENT_PROJECT_URL =		https://docs.pylonsproject.org/projects/pastedeploy/en/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/af/8f/1b09eac08a9a77706f30aa530ecf833bc1b3c05c4693eee9e37f91690614/PasteDeploy-3.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5f4b4d5fddd39b8947ea727161e366bf55b90efc60a4d1dd7976b9031d0b4e5f
COMPONENT_LICENSE =		MIT

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/paste
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
