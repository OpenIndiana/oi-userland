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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	glib
COMPONENT_MJR_VERSION=  2.57
COMPONENT_MNR_VERSION=  1
COMPONENT_VERSION=      $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY= GNOME core libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:d029e7c4536835f1f103472f7510332c28d58b9b7d6cd0e9f45c2653e670d9b4
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.gtk.org/
COMPONENT_FMRI=	library/glib2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

LDFLAGS += -lsocket -lsecdb -lnsl

COMPONENT_PREP_ACTION =	( cd $(@D) && autoreconf -f )

COMPONENT_PRE_CONFIGURE_ACTION = ( cp -a $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

# GCC 6
CFLAGS += -Wno-error=format-nonliteral
CPPFLAGS += $(CPP_XPG6MODE)

CONFIGURE_OPTIONS.32 = --sysconfdir=/etc
CONFIGURE_OPTIONS.64 = --sysconfdir=/etc/$(MACH64)
CONFIGURE_OPTIONS += --disable-dtrace
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

CONFIGURE_ENV    += PERL=$(PERL)
CONFIGURE_ENV    += PYTHON=$(PYTHON)
CONFIGURE_ENV    += CPPFLAGS="$(CPPFLAGS)"

DFLAGS.64 = -64
COMPONENT_BUILD_ENV += DFLAGS=$(DFLAGS.$(BITS))

# Otherwise tests fail
ENV = /usr/bin/env -i

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^FAIL:/p" ' \
	'-e "/^ERROR:/p" ' \
	'-e "/^\#/p" ' \


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
