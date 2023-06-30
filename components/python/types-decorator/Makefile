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
#   $WS_TOOLS/python-integrate-project types-decorator
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		types-decorator
HUMAN_VERSION =			5.1.8.3
COMPONENT_SUMMARY =		types-decorator - Typing stubs for decorator
COMPONENT_PROJECT_URL =		https://github.com/python/typeshed
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/94/92/210380e99145be80044b8ef4922585ac639dd6a6574e73699156380cf44c/types-decorator-5.1.8.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:32dd380fc88d0e7a1f27a84ba1ce6e29ba0ad42caaa1b88e7b5d27e61f6e4962
COMPONENT_LICENSE =		Apache-2.0 AND MIT

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We are not interested in coverage reports
PYTEST_ADDOPTS += -p no:cov
# https://github.com/python/typeshed/issues/10386
PYTEST_ADDOPTS += -p no:black

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
