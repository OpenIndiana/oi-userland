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
#   $WS_TOOLS/python-integrate-project platformdirs
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		platformdirs
HUMAN_VERSION =			4.14.8
COMPONENT_SUMMARY =		A small Python package for determining appropriate platform-specific dirs, e.g. a \`user data dir\`.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/platformdirs
COMPONENT_ARCHIVE_HASH =	\
	sha256:96893d686e84e9e6f358a9ea41a8de544df66dbf2ba6cda250e7dc73acf85b9b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox (test bootstrap)
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

# Python 3.9 is not supported by platformdirs >= 4.5.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Testing needs the XDG_RUNTIME_DIR variable pointing to own runtime directory
# with permissions 0700
COMPONENT_PRE_TEST_ACTION += $(MKDIR) $(COMPONENT_TEST_BUILD_DIR)/.xdg_runtime_dir ;
COMPONENT_PRE_TEST_ACTION += $(CHMOD) 0700 $(COMPONENT_TEST_BUILD_DIR)/.xdg_runtime_dir ;
COMPONENT_TEST_ENV += XDG_RUNTIME_DIR=$(COMPONENT_TEST_BUILD_DIR)/.xdg_runtime_dir
COMPONENT_POST_TEST_ACTION += $(RM) -r $(COMPONENT_TEST_BUILD_DIR)/.xdg_runtime_dir ;

# Testing needs the XDG_CONFIG_HOME variable
COMPONENT_TEST_ENV += XDG_CONFIG_HOME=$(COMPONENT_TEST_BUILD_DIR)/.xdg_config_home

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-fancy-pypi-readme
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/python-sbom
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/appdirs
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
