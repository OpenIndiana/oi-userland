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
#   $WS_TOOLS/python-integrate-project -d python/msgpack-39 msgpack
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		msgpack
HUMAN_VERSION =			1.1.2
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		MessagePack serializer
COMPONENT_PROJECT_URL =		https://msgpack.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:3b60763c1373dd60f398488069bcdc703cd08a711477b5d480eecc9f9626f47e
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

# msgpack >= 1.2.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
