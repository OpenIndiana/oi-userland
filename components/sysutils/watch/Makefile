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
# Copyright 2016 Adam Stevko<
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		watch
COMPONENT_VERSION=	3.2.8
COMPONENT_SUMMARY=	The Linux watch utility
COMPONENT_PROJECT_URL=	http://procps.sourceforge.net
COMPONENT_FMRI=		utilities/watch
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		procps-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	procps-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=  http://procps.sourceforge.net/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:11ed68d8a4433b91cd833deb714a3aa849c02aea738c42e6b4557982419c1535
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_TARGETS= watch

COMPONENT_BUILD_ENV+= CC="$(CC)"
COMPONENT_BUILD_ENV+= CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ENV+= $(COMPONENT_BUILD_ENV)

$(INSTALL_32): $(BUILD_32)
	$(MKDIR) $(PROTOUSRBINDIR) $(PROTOUSRSHAREMAN1DIR)

	$(INSTALL) $(BUILD_DIR_32)/watch $(PROTOUSRBINDIR)/watch
	$(INSTALL) $(BUILD_DIR_32)/watch.1 $(PROTOUSRSHAREMAN1DIR)/watch.1

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
