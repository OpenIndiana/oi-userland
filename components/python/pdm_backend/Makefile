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
HUMAN_VERSION =			2.4.3
COMPONENT_SUMMARY =		The build backend used by PDM that supports latest packaging standards
COMPONENT_PROJECT_URL =		https://github.com/pdm-project/pdm-backend
COMPONENT_ARCHIVE_HASH =	\
	sha256:dbd9047a7ac10d11a5227e97163b617ad5d665050476ff63867d971758200728
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Current date
COMPONENT_TEST_TRANSFORMS += "-e 's/d$(shell /usr/bin/date +%Y%m%d)]/d\$$(DATE)]/'"
# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += runtime/python
