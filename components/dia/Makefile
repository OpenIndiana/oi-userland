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
# Copyright 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=           dia
COMPONENT_VERSION=        0.97.3
COMPONENT_PROJECT_URL=    https://wiki.gnome.org/Apps/Dia
COMPONENT_SUMMARY=        Dia Diagram Editor
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=        \
    sha256:22914e48ef48f894bb5143c5efc3d01ab96e0a0cde80de11058d3b4301377d34
COMPONENT_ARCHIVE_URL=        http://ftp.gnome.org/pub/GNOME/sources/dia/0.97/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION = (cd $(@D) ; autoconf)

CONFIGURE_OPTIONS +=        --enable-gnome
CONFIGURE_OPTIONS +=        --with-cairo
CONFIGURE_OPTIONS +=        --disable-static
CONFIGURE_OPTIONS +=        --enable-db2html

# common targets
build:		        $(BUILD_32)

install:     		$(INSTALL_32)

test:			$(NO_TESTS)

include $(WS_MAKE_RULES)/depend.mk
