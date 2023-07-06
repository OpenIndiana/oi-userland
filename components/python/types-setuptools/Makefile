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
#   $WS_TOOLS/python-integrate-project types-setuptools
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		types-setuptools
HUMAN_VERSION =			68.0.0.1
COMPONENT_SUMMARY =		types-setuptools - Typing stubs for setuptools
COMPONENT_PROJECT_URL =		https://github.com/python/typeshed
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/12/cf/0b2798b98ef1aa9009bbd03bae5fe76fd653ef99afe804db3bc16df600d2/types-setuptools-68.0.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a0454ea7ad0711f63a602caa87929003a83cab89224ae1506ed44bb5be8fe7d7
COMPONENT_LICENSE =		Apache-2.0 AND MIT

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We are not interested in coverage reports
PYTEST_ADDOPTS += -p no:cov
# https://github.com/python/typeshed/issues/10386
PYTEST_ADDOPTS += -p no:black

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
