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
# Copyright (c) 2014 Alexander Pyhalov. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=           avant-window-navigator
COMPONENT_VERSION=        0.3.2.1
COMPONENT_PROJECT_URL=    https://launchpad.net/awn
COMPONENT_SUMMARY=        Avant Window Navigator - fully customizable dock-like navigator
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=        \
    sha256:f10d728afcdf35c3f7e6cff57f478114f14d5db4b1c9bdc2dc2e582bcaedc21a
COMPONENT_ARCHIVE_URL=        https://launchpad.net/awn/0.2/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

CONFIGURE_OPTIONS+=        --sysconfdir=/etc
CONFIGURE_OPTIONS+=        --with-desktop=gnome

# common targets
build:		        $(BUILD_32)

install:     		$(INSTALL_32)

test:			$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
