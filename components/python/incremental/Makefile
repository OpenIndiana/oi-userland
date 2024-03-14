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
#   $WS_TOOLS/python-integrate-project incremental
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		incremental
COMPONENT_VERSION =		22.10.0
COMPONENT_SUMMARY =		incremental - \\\\\\\"A small library that versions your Python projects.\\\\\\\"
COMPONENT_PROJECT_URL =		https://github.com/twisted/incremental
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/86/42/9e87f04fa2cd40e3016f27a4b4572290e95899c6dce317e2cdb580f3ff09/incremental-22.10.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:912feeb5e0f7e0188e6f42241d2f450002e11bbc0937c65865045854c24c0bd0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Testing is currently not possible
# https://github.com/twisted/incremental/issues/80
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
