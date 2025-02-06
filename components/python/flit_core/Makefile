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
#   $WS_TOOLS/python-integrate-project flit_core
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flit_core
HUMAN_VERSION =			3.10.1
COMPONENT_SUMMARY =		Distribution-building parts of Flit. See flit package for more information
COMPONENT_ARCHIVE_HASH =	\
	sha256:66e5b87874a0d6e39691f0e22f09306736b633548670ad3c09ec9db03c5662f7
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - flit_scm (test bootstrap)
# - installer
# - packaging
# - pathspec (test bootstrap)
# - pyproject_hooks
# - typing_extensions
# - wheel
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
