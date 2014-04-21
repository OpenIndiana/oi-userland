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

COMPONENT_NAME= gvfs

COMPONENT_VERSION= 1.6.7
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GNOME virtual file system framework
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:fe5f6181eac14d5147794389bf57717226a15ddf8283631b434c2d9ec120d659
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

gcc_OPT = -O2

PATH = /usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        (cd $(@D) && \
					libtoolize --force &&\
					aclocal -I . &&\
					autoheader &&\
					automake &&\
					autoconf )

CFLAGS += -D_XPG4_2
CFLAGS += -D__EXTENSIONS__
CFLAGS += -I/usr/sfw/include
LDFLAGS += -lxml2
LDFLAGS.32 = -L/usr/sfw/lib -R/usr/sfw/lib
LDFLAGS.64 = -L/usr/sfw/lib/$(MACH64) -R/usr/sfw/lib/$(MACH64)
LDFLAGS += $(LDFLAGS.$(BITS))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS.64 += --disable-avahi

CONFIGURE_ENV+= PERL=$(PERL)

$(INSTALL_32):	$(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
