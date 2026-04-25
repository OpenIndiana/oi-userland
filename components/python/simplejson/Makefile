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
#   $WS_TOOLS/python-integrate-project simplejson
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		simplejson
HUMAN_VERSION =			4.1.1
COMPONENT_SUMMARY =		Simple, fast, extensible JSON encoder/decoder for Python
COMPONENT_PROJECT_URL =		https://github.com/simplejson/simplejson
COMPONENT_ARCHIVE_HASH =	\
	sha256:c08eb9f7a90f77ae470e19a07472e9a79ebc0d1c2315d86a72767665bd5ba79f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
