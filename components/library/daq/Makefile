#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		daq
COMPONENT_VERSION=	2.0.6
COMPONENT_PROJECT_URL=	http://www.snort.org/
COMPONENT_SUMMARY=	Snort data acquisition library for packet I/O
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:d41da5f7793e66044e6927dd868c0525e7ee4ec1a3515bf74ef9a30cd9273af0
COMPONENT_ARCHIVE_URL=	https://snort.org/downloads/snort/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/daq
COMPONENT_LICENSE=	GPLv2
COMPONENT_FMRI=		system/library/libdaq
COMPONENT_CLASSIFICATION=	System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# error: tokdefs.h: No such file or directory
COMPONENT_BUILD_ARGS=

CONFIGURE_OPTIONS +=    --enable-static=no

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
