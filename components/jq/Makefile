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
# Copyright 2013, Jon Tibble.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         jq
COMPONENT_VERSION=      1.3
COMPONENT_PROJECT_URL=	https://stedolan.github.io/jq/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:623f23c36abfc1d96d85020cf421b56f90a229d566f26a4a0d3e8536244bfed7
COMPONENT_ARCHIVE_URL=	ftp://tux.rainside.sk/gentoo/distfiles/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPILER =	gcc

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
