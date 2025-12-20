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
#   $WS_TOOLS/python-integrate-project tokenize_rt
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tokenize_rt
HUMAN_VERSION =			6.2.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A wrapper around the stdlib \`tokenize\` which roundtrips.
COMPONENT_PROJECT_URL =		https://github.com/asottile/tokenize-rt
COMPONENT_ARCHIVE_URL =		\
	https://github.com/asottile/tokenize-rt/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:31bb2c9c5a954cb6c29d60218f83ea07be08faac5e2f4431d0463f9adb63fb6e
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Github tarball use different source directory than sdist
COMPONENT_SRC=tokenize-rt-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
