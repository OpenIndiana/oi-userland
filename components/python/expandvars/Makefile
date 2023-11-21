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
#   $WS_TOOLS/python-integrate-project expandvars
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		expandvars
HUMAN_VERSION =			0.11.0
COMPONENT_SUMMARY =		expandvars - Expand system variables Unix style
COMPONENT_PROJECT_URL =		https://github.com/sayanarijit/expandvars
COMPONENT_ARCHIVE_URL =		\
	https://github.com/sayanarijit/expandvars/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f28bb03159f611c59d98ff58595f0a236a68aeff072f6f117676bfd4c1208b06
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Manually added dependencies we are unable to detect automatically
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
