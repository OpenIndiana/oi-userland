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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flit_core
HUMAN_VERSION =			4.1.0
COMPONENT_SUMMARY =		Distribution-building parts of Flit. See flit package for more information
COMPONENT_ARCHIVE_HASH =	\
	sha256:62e12b63ead8335b37f59fabb977c7167fe476dafb5e41785dfa8c9aff843bc6
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - coherent.licensed
# - docutils
# - tomli_w (test bootstrap)
# - installer
# - packaging
# - pathspec (test bootstrap)
# - pyproject_hooks
# - tomli
# - typing_extensions
# - wheel (test bootstrap)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIRED_PACKAGES.python += library/python/testpath

# Auto-generated dependencies
REQUIRED_PACKAGES.python += runtime/python
