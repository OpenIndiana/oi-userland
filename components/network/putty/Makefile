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

BUILD_BITS=				64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			putty
COMPONENT_VERSION=		0.74
COMPONENT_SUMMARY=		A terminal integrated SSH/Telnet client commandline tools
COMPONENT_PROJECT_URL=	https://www.chiark.greenend.org.uk/~sgtatham/putty/
COMPONENT_FMRI=			network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:ddd5d388e51dd9e6e294005b30037f6ae802239a44c9dc9808c779e6d11b847d
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE=	LICENCE

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lnsl -lsocket

CONFIGURE_OPTIONS+=--without-gssapi 
CONFIGURE_OPTIONS+=--without-gtk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
