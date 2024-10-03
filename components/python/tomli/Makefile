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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tomli
HUMAN_VERSION =			2.0.2
COMPONENT_SUMMARY =		A lil' TOML parser
COMPONENT_PROJECT_URL =		https://github.com/hukkin/tomli
COMPONENT_ARCHIVE_URL =		\
	https://github.com/hukkin/tomli/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a3a652f16bf326ba763ada67169165daf87ff9c465e21ad8264f2657beaf5264
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - flit_scm (test bootstrap)
# - hatchling (test bootstrap)
# - pyproject_api (test bootstrap)
# - pytest (test bootstrap)
# - setuptools-scm
# - tox (test bootstrap)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Force verbose test output via tox posargs
TOX_POSARGS += -v

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
