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
# Copyright 2019 Michal Nowak
#

BUILD_BITS = 32_and_64
BUILD_STYLE = meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glib
COMPONENT_MJR_VERSION=	2.62
COMPONENT_MNR_VERSION=	4
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY=	GNOME core libraries
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:4c84030d77fa9712135dfa8036ad663925655ae95b1d19399b6200e869925bbc
COMPONENT_ARCHIVE_URL= \
	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gtk.org/
COMPONENT_FMRI=		library/glib2

PATH=$(PATH.gnu)

include $(WS_MAKE_RULES)/common.mk

PYTHON_VERSION = 3.5

LDFLAGS += -lsocket -lsecdb -lnsl

# GCC 6
CFLAGS += -Wno-error=format-nonliteral
CPPFLAGS += $(CPP_XPG6MODE)

CONFIGURE_OPTIONS.32 = --sysconfdir=/etc
CONFIGURE_OPTIONS.64 = --sysconfdir=/etc/$(MACH64)
CONFIGURE_OPTIONS += -Dxattr=false
CONFIGURE_OPTIONS += -Dfam=true
CONFIGURE_OPTIONS += -Dman=true

CONFIGURE_ENV    += PERL=$(PERL)
CONFIGURE_ENV    += PYTHON=$(PYTHON)
CONFIGURE_ENV    += CPPFLAGS="$(CPPFLAGS)"

# Dtrace flags
DFLAGS.64 = -64
COMPONENT_BUILD_ENV += DFLAGS=$(DFLAGS.$(BITS))

# Otherwise tests fail
#ENV = /usr/bin/env -i

# We need to install libraries and set correct LD_LIBRARY_PATH before test
$(TEST_TARGET): $(INSTALL_TARGET)

COMPONENT_TEST_ENV.32 = LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib PATH=$(PATH):/usr/lib
COMPONENT_TEST_ENV.64 = LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib/$(MACH64) PATH=$(PATH)/usr/lib/$(MACH64)
COMPONENT_TEST_ENV = $(COMPONENT_TEST_ENV.$(BITS))

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/^(Fail|Ok|Expected Fail|Unexpected Pass|Skipped|Timeout)/'"

REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library/dbus

# Auto-generated dependencies
REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
