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

#
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2017, Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkg-config
COMPONENT_VERSION=	0.29.2
COMPONENT_REVISION=	2
COMPONENT_FMRI=	developer/build/pkg-config
COMPONENT_SUMMARY=	A tool to query library build-time information
COMPONENT_CLASSIFICATION=	Development/System
COMPONENT_PROJECT_URL= \
  https://www.freedesktop.org/wiki/Software/pkg-config
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:6fc69c01688c9458a57eb9a1664c9aba372ccda420a02bf4429fe610e7e7d591
COMPONENT_ARCHIVE_URL= \
  https://pkgconfig.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

ASLR_MODE = $(ASLR_ENABLE)

# have pkg-config strip any of the default linker search directories
CONFIGURE_OPTIONS += --with-system-library-path='/lib:/usr/lib:/lib/${MACH64}:/usr/lib/${MACH64}:/lib/64:/usr/lib/64'

COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Strip make lines from test output
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^Making/d" ' \
	'-e "/^make/d" '

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/gnome/gettext
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
