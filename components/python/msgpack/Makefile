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
#   $WS_TOOLS/python-integrate-project msgpack
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		msgpack
HUMAN_VERSION =			1.2.1
COMPONENT_SUMMARY =		MessagePack serializer
COMPONENT_PROJECT_URL =		https://msgpack.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:04c721c2c7448767e9e3f2520a475663d8ee0f09c31890f6d2bd70fd636a9647
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

# Python 3.9 is not supported by msgpack >= 1.2.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
