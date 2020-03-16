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
# Copyright 2017 Gary Mills
# Copyright 2016 Alexander Pyhalov
#
BUILD_BITS=32
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		netifaces
COMPONENT_VERSION=	0.10.9
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/netifaces
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2dee9ffdd16292878336a58d04a20f0ffe95555465fee7c9bd23b3490ef2abf3
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/n/netifaces/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	2.7

TEST_TARGET=$(NO_TEST)
include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
