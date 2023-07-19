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
#   $WS_TOOLS/python-integrate-project pytest-black
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-black
HUMAN_VERSION =			0.3.12
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		pytest-black - A pytest plugin to enable format checking with black
COMPONENT_PROJECT_URL =		https://github.com/shopkeep/pytest-black
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/dc/cd/b64a3d5d2bc78c8aaff5b86abc6ae6a83e2cec02e751c5db351ca5100515/pytest-black-0.3.12.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1d339b004f764d6cd0f06e690f6dd748df3d62e6fe1a692d6a5500ac2c5b75a5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:cov
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/black
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/toml
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
