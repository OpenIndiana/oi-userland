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
#   $WS_TOOLS/python-integrate-project contextvars
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		contextvars
HUMAN_VERSION =			2.4
COMPONENT_SUMMARY =		contextvars - PEP 567 Backport
COMPONENT_PROJECT_URL =		http://github.com/MagicStack/contextvars
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/83/96/55b82d9f13763be9d672622e1b8106c85acb83edd7cc2fa5bc67cd9877e9/contextvars-2.4.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f38c908aaa59c14335eeea12abea5f443646216c4e29380d7bf34d2018e2c39e
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/immutables
PYTHON_REQUIRED_PACKAGES += runtime/python
