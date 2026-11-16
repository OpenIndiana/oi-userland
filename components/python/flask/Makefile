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
#   $WS_TOOLS/python-integrate-project flask
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flask
HUMAN_VERSION =			3.1.3
COMPONENT_SUMMARY =		A simple framework for building complex web applications.
COMPONENT_ARCHIVE_HASH =	\
	sha256:0ef0e52b8a9cd932855379197dd8f94047b359ca0a78695144304cb45f87c9eb
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pallets/flask/issues/6092
PYTEST_ADDOPTS += --deselect tests/test_reqctx.py::test_bad_environ_raises_bad_request

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/blinker
REQUIRED_PACKAGES.python += library/python/click
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += library/python/importlib-metadata
REQUIRED_PACKAGES.python += library/python/itsdangerous
REQUIRED_PACKAGES.python += library/python/jinja2
REQUIRED_PACKAGES.python += library/python/markupsafe
REQUIRED_PACKAGES.python += library/python/werkzeug
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/asgiref
TEST_REQUIRED_PACKAGES.python += library/python/greenlet
TEST_REQUIRED_PACKAGES.python += library/python/pytest
