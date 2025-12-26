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
#   $WS_TOOLS/python-integrate-project pytest-xprocess
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-xprocess
HUMAN_VERSION =			1.0.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A pytest plugin for managing processes across test runs.
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-xprocess/
COMPONENT_ARCHIVE_HASH =	\
	sha256:15e270637586eabc56755ee5fcc81c48bdb46ba7ef7c0d5b1b64302d080cc60f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/psutil
REQUIRED_PACKAGES.python += library/python/pytest
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
