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
# Copyright 2016 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=           dconf
COMPONENT_VERSION=        0.24.0
COMPONENT_REVISION=       1
COMPONENT_PROJECT_URL=    https://wiki.gnome.org/Projects/dconf
COMPONENT_SUMMARY=        GNOME Configuration Framework
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=        \
    sha256:4373e0ced1f4d7d68d518038796c073696280e22957babb29feb0267c630fec2
COMPONENT_ARCHIVE_URL=        http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.24/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_FMRI= gnome/config/dconf
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

CFLAGS += -std=c99
CFLAGS += -D__EXTENSIONS__

CONFIGURE_OPTIONS+=        --sysconfdir=/etc
CONFIGURE_OPTIONS+=        --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_INSTALL_ENV+=        GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1


# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
