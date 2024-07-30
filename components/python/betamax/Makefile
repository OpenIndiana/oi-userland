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
#   $WS_TOOLS/python-integrate-project betamax
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		betamax
HUMAN_VERSION =			0.9.0
COMPONENT_SUMMARY =		A VCR imitation for python-requests
COMPONENT_PROJECT_URL =		https://github.com/sigmavirus24/betamax
COMPONENT_ARCHIVE_URL =		\
	https://github.com/betamaxpy/betamax/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:971bcaffce5ce8fdc67fb207fb0d12657d2ac169e0086428b5acdf8d54d8a8d5
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# force verbose test output via tox posargs
TOX_POSARGS += --verbose

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/requests
