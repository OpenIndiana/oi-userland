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
HUMAN_VERSION =			3.12.0
COMPONENT_SUMMARY =		Distribution-building parts of Flit. See flit package for more information
COMPONENT_ARCHIVE_HASH =	\
	sha256:18f63100d6f94385c6ed57a72073443e1a71a4acb4339491615d0f16d6ff01b2
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
