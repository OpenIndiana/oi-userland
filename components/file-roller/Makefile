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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= file-roller
COMPONENT_VERSION= 2.30.2
COMPONENT_SUMMARY= GNOME archive manager
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:34e809ee4e11d85d314b9060a5641a68e55046d429bf8a435a24b777eec8b2f5
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= desktop/archive-manager/file-roller
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					libtoolize --copy --force &&\
					intltoolize --force --copy &&\
					aclocal -I. &&\
					autoheader &&\
					automake -c -f -a &&\
					autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        (chmod -R u+r $(SOURCE_DIR) && cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --localstatedir=/var/lib

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)
