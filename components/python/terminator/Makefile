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
# Copyright 2021 Gary Mills
# Copyright (c) 2014 Alexander Pyhalov
#

BUILD_STYLE= setup.py
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		terminator
COMPONENT_VERSION=	2.1.1
COMPONENT_PROJECT_URL=	https://gnome-terminator.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ee1907bc9bfe03244f6d8074b214ef1638a964b38e21ca2ad4cca993d0c1d31e
COMPONENT_ARCHIVE_URL=	https://github.com/gnome-terminator/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz

PYTHON_VERSIONS=	3.9

# Tests require an X environment
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

PYTHON_DATA=/usr

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTO_DIR)/usr/bin && \
	  $(MV) terminator terminator-$(PYTHON_VERSION) && \
	  $(MV) remotinator remotinator-$(PYTHON_VERSION) \
	)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/psutil-39
REQUIRED_PACKAGES += library/python/pygobject-3-39
REQUIRED_PACKAGES += library/python/python-dbus-39
REQUIRED_PACKAGES += runtime/python-39
