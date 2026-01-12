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
#   $WS_TOOLS/python-integrate-project tomli
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tomli
HUMAN_VERSION =			2.4.0
COMPONENT_SUMMARY =		A lil' TOML parser
COMPONENT_PROJECT_URL =		https://github.com/hukkin/tomli
COMPONENT_ARCHIVE_URL =		\
	https://github.com/hukkin/tomli/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6d9e3a3f690db54a42eb9e98591ec5e9731779d3650c39668a220982f587a699
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - hatchling (test bootstrap)
# - setuptools-scm
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Force verbose test output via tox posargs
TOX_POSARGS += -v

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
