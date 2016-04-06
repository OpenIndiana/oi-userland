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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= devhelp
COMPONENT_VERSION= 2.32.0
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= API documentation browser for GNOME 2
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:61b342cbaf27379be9baa5df1f34c9464916601ec4378fa7e1c76fcc686553e4
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/devhelp/2.32/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://wiki.gnome.org/Apps/Devhelp

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS+= -std=gnu++0x

COMPONENT_PREP_ACTION =        (cd $(@D); autoreconf --install --force)

# We get Werror without building in separate directory, and it's not good
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV    += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV    += MSGFMT=/usr/gnu/bin/msgfmt

build: $(BUILD_32)

install: $(INSTALL_32)
