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
#   $WS_TOOLS/python-integrate-project gprof2dot
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gprof2dot
HUMAN_VERSION =			2025.4.14
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Generate a dot graph from the output of several profilers.
COMPONENT_PROJECT_URL =		https://github.com/jrfonseca/gprof2dot
COMPONENT_ARCHIVE_URL =		\
	https://github.com/jrfonseca/gprof2dot/archive/refs/tags/$(GITHUB_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:47521b4fb13edeceb6af45503d1af84165fe84866a06c50e738e8a0b7a7bd924
COMPONENT_LICENSE =		LGPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This project uses custom testing.
# See https://github.com/jrfonseca/gprof2dot/blob/main/.github/workflows/build.yml
TEST_STYLE = custom

# Versions at github are with leading zeros
GITHUB_VERSION = $(shell echo $(HUMAN_VERSION) | $(GSED) -e 's/\.\(.\.\)/.0\1/' -e 's/\.\(.\)$$/.0\1/')
# Sources are located in non-default directory
COMPONENT_SRC = gprof2dot-$(GITHUB_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Custom testing
TEST_REQUIRED_PACKAGES += image/graphviz
COMPONENT_TEST_CMD = $(PYTHON) tests/test.py
COMPONENT_TEST_ARGS =
COMPONENT_TEST_TARGETS =

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
