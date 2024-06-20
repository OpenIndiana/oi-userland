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
#   $WS_TOOLS/python-integrate-project psutil
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		psutil
HUMAN_VERSION =			6.0.0
COMPONENT_SUMMARY =		Cross-platform lib for process and system monitoring in Python.
COMPONENT_PROJECT_URL =		https://github.com/giampaolo/psutil
COMPONENT_ARCHIVE_HASH =	\
	sha256:8faae4f310b6d969fa26ca0545338b21f73c6b15db7c4a8d934a5482faa818f2
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We need to run tests in proto area to get access to compiled modules
COMPONENT_TEST_DIR = $(PROTO_DIR)/$(PYTHON_LIB)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
