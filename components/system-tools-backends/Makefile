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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		system-tools-backends
COMPONENT_VERSION=	1.4.2
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://system-tools-backends.freedesktop.org/
COMPONENT_SUMMARY=	Backends for the GNOME System Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:88af681912f8b1a9f51fe00ce13e233d28ae279128d04318db1b7e626482d2a8
COMPONENT_ARCHIVE_URL=	http://system-tools-backends.freedesktop.org/downloads/1.4/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

COMPONENT_POST_INSTALL_ACTION  = ( \
     for file in $(PROTO_DIR)/usr/share/setup-tool-backends/scripts/* ; do \
        $(GSED) -i -e 's:\#!/usr/bin/env perl:\#!/usr/bin/perl:' $$file ;\
    done ; )


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
