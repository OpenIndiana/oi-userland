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
#   $WS_TOOLS/python-integrate-project -d python/jaraco.envs jaraco_envs
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jaraco_envs
HUMAN_VERSION =			2.6.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Classes for orchestrating Python (virtual) environments
COMPONENT_PROJECT_URL =		https://github.com/jaraco/jaraco.envs
COMPONENT_ARCHIVE_HASH =	\
	sha256:809195c406640db256ee01eebf4f6a369dd85759d8178c3921704308dd0360f5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =			jaraco.envs-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/path
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += library/python/tox
REQUIRED_PACKAGES.python += library/python/virtualenv
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
