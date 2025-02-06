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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tokenize_rt
HUMAN_VERSION =			6.1.0
COMPONENT_SUMMARY =		A wrapper around the stdlib \`tokenize\` which roundtrips.
COMPONENT_PROJECT_URL =		https://github.com/asottile/tokenize-rt
COMPONENT_ARCHIVE_URL =		\
	https://github.com/asottile/tokenize-rt/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:67d25a612c7c08ddfa0ed273c81e9d180142a31b53141b0ee242d16fe5d4b641
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Github tarball use different source directory than sdist
COMPONENT_SRC=tokenize-rt-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
