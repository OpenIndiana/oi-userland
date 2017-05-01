#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= gnome-mime-data

COMPONENT_VERSION= 2.18.0
COMPONENT_SUMMARY= MIME Type and Application Database for the GNOME Desktop
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:37196b5b37085bbcd45c338c36e26898fe35dd5975295f69f48028b1e8436fd7
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.18/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.gnome.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

gcc_OPT = -O2

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT =$(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV+= PERL=$(PERL)

COMPONENT_INSTALL_TARGET =  install-strip

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)

# Build dependencies
REQUIRED_PACKAGES += text/gnu-gettext
