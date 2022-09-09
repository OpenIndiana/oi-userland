#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Vincent Torri
#
BUILD_BITS=64
BUILD_STYLE=justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           samurai
COMPONENT_VERSION=        1.2
COMPONENT_SUMMARY=        samurai is a ninja-compatible build tool written in C99
COMPONENT_PROJECT_URL=    https://git.sr.ht/~mcf/samurai
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=    https://git.sr.ht/~mcf/samurai/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:37a2d9f35f338c53387eba210bab7e5d8abe033492664984704ad84f91b71bac
COMPONENT_FMRI=           developer/build/samurai
COMPONENT_CLASSIFICATION= Development/Distribution Tools
COMPONENT_LICENSE=        Apache 2.0

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ARGS += CC=$(CC)
COMPONENT_INSTALL_ARGS += PREFIX=/usr DESTDIR=$(PROTO_DIR)
# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
