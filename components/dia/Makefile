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

COMPONENT_NAME=           dia
COMPONENT_VERSION=        0.97.2
COMPONENT_PROJECT_URL=    https://wiki.gnome.org/Apps/Dia
COMPONENT_SUMMARY=        Dia Diagram Editor
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=        \
    sha256:a761478fb98697f71b00d3041d7c267f3db4b94fe33ac07c689cb89c4fe5eae1
COMPONENT_ARCHIVE_URL=        http://ftp.gnome.org/pub/GNOME/sources/dia/0.97/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION = (cd $(@D) ; autoconf)

CONFIGURE_OPTIONS +=        --sysconfdir=/etc
CONFIGURE_OPTIONS +=        --enable-gnome
CONFIGURE_OPTIONS +=        --with-cairo
CONFIGURE_OPTIONS +=        --disable-static

# common targets
build:		        $(BUILD_32)

install:     		$(INSTALL_32)

test:			$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
