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
#   $WS_TOOLS/python-integrate-project pdm_backend
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pdm_backend
HUMAN_VERSION =			2.3.1
COMPONENT_SUMMARY =		The build backend used by PDM that supports latest packaging standards
COMPONENT_PROJECT_URL =		https://github.com/pdm-project/pdm-backend
COMPONENT_ARCHIVE_HASH =	\
	sha256:c03cfb3a803325c049b57ba2502b409479ebb22b6a4ee3746c1f688b939764e8
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += runtime/python
