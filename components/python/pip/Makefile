#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Adam Stevko. All rights reserved.
# Copyright 2019 Michal Nowak
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pip
COMPONENT_VERSION= 	19.1.1
COMPONENT_REVISION=	2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:cce3a3a4cc6f7e1f1d52d0dbe843ebca153ee42660a01acd9248d110c374efa2
COMPONENT_ARCHIVE_URL=	https://github.com/pypa/pip/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://github.com/pypa/pip

PYTHON_VERSIONS=	2.7 3.5

TEST_TARGET=		$(NO_TESTS)
include $(WS_TOP)/make-rules/common.mk


# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
