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
#   $WS_TOOLS/python-integrate-project pytest-relaxed
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-relaxed
HUMAN_VERSION =			2.0.1
COMPONENT_SUMMARY =		pytest-relaxed - Relaxed test discovery/organization for pytest
COMPONENT_PROJECT_URL =		https://pytest-relaxed.readthedocs.io/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/bitprophet/pytest-relaxed/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:caf4a7da34e922c0cd26fbf37b9aca1bc099a02668bcf83ebf6fe6717687e844
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/decorator
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += runtime/python
