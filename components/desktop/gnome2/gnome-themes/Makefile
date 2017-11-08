##
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
# Copyright (c) 2014 Ken Mays
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gnome-themes
COMPONENT_VERSION=      2.32.1
COMPONENT_PROJECT_URL=  http://www.gnome.org
COMPONENT_SUMMARY=      Gnome themes
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:8601ee24c2e096593221cbd6ebdb6686042225a03c02a01c0d67c163f9febd1a
COMPONENT_ARCHIVE_URL=  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D) &&\
                                        autoreconf -f -i)

COMPONENT_PRE_CONFIGURE_ACTION = ( cp -a $(COMPONENT_DIR)/files/* $(BUILD_DIR_$(BITS)) )

CONFIGURE_OPTIONS+=	--enable-all-themes

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += gnome/theme/gtk2-engines
