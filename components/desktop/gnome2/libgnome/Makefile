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

COMPONENT_NAME= libgnome

COMPONENT_VERSION= 2.32.1
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= GNOME Base Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:b2c63916866485793b87398266dd7778548c1734923c272a94d84ee011b6f7a4
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
				libtoolize --copy --force &&\
				aclocal -I m4 &&\
				automake -c -f -a &&\
				autoconf )
gcc_OPT = -O2

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-esd

COMPONENT_INSTALL_ENV+=  GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-vfs
REQUIRED_PACKAGES += library/libbonobo
REQUIRED_PACKAGES += library/orbit2
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += system/library
