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
#   $WS_TOOLS/python-integrate-project flake8_2020
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flake8_2020
HUMAN_VERSION =			1.7.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		flake8_2020 - flake8 plugin which checks for misuse of \`sys.version\` or \`sys.version_info\`
COMPONENT_PROJECT_URL =		https://github.com/asottile/flake8-2020
COMPONENT_ARCHIVE_URL =		\
	https://github.com/asottile/flake8-2020/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4956bdfc5d63fb5c6e52404a6d8df877baa23631d2e00cb29b08d73669a6b0e8
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Github tarball use different source directory than sdist
COMPONENT_SRC=flake8-2020-$(HUMAN_VERSION)

# flake8_2020 >= 1.8.0 requires Python >= 3.8
PYTHON_VERSIONS = 3.7

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flake8
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
