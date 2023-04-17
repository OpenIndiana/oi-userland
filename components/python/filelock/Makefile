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
#   $WS_TOOLS/python-integrate-project filelock
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		filelock
HUMAN_VERSION =			3.11.0
COMPONENT_SUMMARY =		filelock - A platform independent file lock.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/py-filelock
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e6/3d/c80975c1028f54e4f0fe6f727d9271362b749321144ea833216b18bfda93/filelock-3.11.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3618c0da67adcc0506b015fd11ef7faf1b493f0b40d87728e19986b536890c37
COMPONENT_LICENSE =		Unlicense
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox (test bootstrap)
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
