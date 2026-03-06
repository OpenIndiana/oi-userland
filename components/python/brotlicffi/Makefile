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
#   $WS_TOOLS/python-integrate-project brotlicffi
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		brotlicffi
HUMAN_VERSION =			1.2.0.1
COMPONENT_SUMMARY =		Python CFFI bindings to the Brotli library
COMPONENT_PROJECT_URL =		https://github.com/python-hyper/brotlicffi
COMPONENT_ARCHIVE_HASH =	\
	sha256:c20d5c596278307ad06414a6d95a892377ea274a5c6b790c2548c009385d621c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# https://github.com/python-hyper/brotlicffi/issues/191
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/cffi
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
