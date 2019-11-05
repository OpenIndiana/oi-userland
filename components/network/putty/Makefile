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
# Copyright 2017 Till Wegmueller
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=putty
COMPONENT_VERSION=0.70
COMPONENT_SUMMARY=A terminal integrated SSH/Telnet client commandline tools
COMPONENT_PROJECT_URL=http://www.chiark.greenend.org.uk/~sgtatham/putty/
COMPONENT_FMRI=network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=sha256:bb8aa49d6e96c5a8e18a057f3150a1695ed99a24eef699e783651d1f24e7b0be
COMPONENT_LICENSE=MIT
COMPONENT_LICENSE_FILE=LICENCE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

LDFLAGS += -lnsl -lsocket

CONFIGURE_OPTIONS+=--without-gssapi 
CONFIGURE_OPTIONS+=--without-gtk
CONFIGURE_BINDIR.64=$(CONFIGURE_PREFIX)/bin

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
