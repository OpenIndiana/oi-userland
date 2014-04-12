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

COMPONENT_NAME= system-config-printer

COMPONENT_VERSION= 1.0.16
IPS_COMPONENT_VERSION= 2.30.0
COMPONENT_SUMMARY= Print Manager for CUPS
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:721c66e0f02aba245db7625d63a141b2f5229a6ba9c1e4a0f300a2a21ce0bfaf
COMPONENT_ARCHIVE_URL= \
  http://cyberelk.net/tim/data/$(COMPONENT_NAME)/1.0.x/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://cyberelk.net/tim/software/system-config-printer/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CFLAGS += -I/usr/X11/include

COMPONENT_PRE_CONFIGURE_ACTION =	(chmod -R u+r  $(SOURCE_DIR) && \
					cp -r $(SOURCE_DIR)/* $(@D) && \
					cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all &&\
                                        cd $(@D) && libtoolize --force &&\
                                        aclocal &&\
                                        automake -a -f -c --gnu &&\
                                        autoconf )

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV    += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV    += MSGFMT=/usr/gnu/bin/msgfmt
CONFIGURE_ENV    += PYTHON=$(PYTHON)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
