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
HUMAN_VERSION =			3.1.0
COMPONENT_SUMMARY =		PasteDeploy - Load, configure, and compose WSGI applications and servers
COMPONENT_PROJECT_URL =		https://docs.pylonsproject.org/projects/pastedeploy/en/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e3/97/0c4a613ec96a54d21daa7e089178263915554320402e89b4e319436a63cb/PasteDeploy-3.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9ddbaf152f8095438a9fe81f82c78a6714b92ae8e066bed418b6a7ff6a095a95
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	license.txt

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/paste
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
