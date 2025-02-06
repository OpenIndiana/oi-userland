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
#   $WS_TOOLS/python-integrate-project unearth
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		unearth
HUMAN_VERSION =			0.17.2
COMPONENT_SUMMARY =		A utility to fetch and download python packages
COMPONENT_PROJECT_URL =		https://github.com/frostming/unearth
COMPONENT_ARCHIVE_HASH =	\
	sha256:0b8a2afd3476f1ab6155fc579501ac47fffe43547d88a70e5a5b76a7fe6caa2c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project uses pdm to manage test dependencies.
TEST_REQUIREMENTS_PDM += test

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/httpx
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pdm-backend
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flask
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-httpserver
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/requests-wsgi-adapter
TEST_REQUIRED_PACKAGES.python += library/python/trustme
