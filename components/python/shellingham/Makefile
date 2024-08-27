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
#   $WS_TOOLS/python-integrate-project shellingham
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		shellingham
HUMAN_VERSION =			1.5.4
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Tool to Detect Surrounding Shell
COMPONENT_PROJECT_URL =		https://github.com/sarugaku/shellingham
COMPONENT_ARCHIVE_URL =		\
	https://github.com/sarugaku/shellingham/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9efba7106b6192be290b6ea1e92f6b2fb04d8059ff364cabf9c08fba1e4dae71
COMPONENT_LICENSE =		ISC
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# This project uses pipenv to manage test dependencies.
TEST_REQUIREMENTS_PIPENV += dev-packages

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/invoke
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/tox
