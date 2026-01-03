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
#   $WS_TOOLS/python-integrate-project -d python/dom-toml dom_toml
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dom_toml
HUMAN_VERSION =			2.2.0
COMPONENT_SUMMARY =		Dom's tools for Tom's Obvious, Minimal Language.
COMPONENT_PROJECT_URL =		https://github.com/domdfcoding/dom_toml
COMPONENT_ARCHIVE_URL =		\
	https://github.com/domdfcoding/dom_toml/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:30e7ea6beff628e7da9ebc01b4d6491a284a57943f4472868e391baf0a683c8c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# dom-toml --> coincidence ==> whey ==> dom-toml
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/domdf-python-tools
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/coincidence
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/numpy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/tomli-w
