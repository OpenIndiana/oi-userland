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
#   $WS_TOOLS/python-integrate-project yamlfix
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		yamlfix
HUMAN_VERSION =			1.16.0
COMPONENT_SUMMARY =		yamlfix - A simple opionated yaml formatter that keeps your comments!
COMPONENT_PROJECT_URL =		https://github.com/lyz-code/yamlfix
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2f/07/b0c1c5de14cd93428059c2f968c8639bf721d2201a074bbf52a8fe8e1d9d/yamlfix-1.16.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:72f7990e5b2b4459ef3249df4724dacbd85ce7b87f4ea3503d8a72c48574cc32
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

# Testing fails because of the this issue related to pydantic and/or maison:
# https://github.com/pydantic/pydantic/issues/7689
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/click
PYTHON_REQUIRED_PACKAGES += library/python/maison
PYTHON_REQUIRED_PACKAGES += library/python/pdm-backend
PYTHON_REQUIRED_PACKAGES += library/python/ruyaml
PYTHON_REQUIRED_PACKAGES += runtime/python
