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
# Copyright 2017 Gary Mills
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ipmitool
COMPONENT_VERSION= 1.8.17
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= IPMI management tool
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:97fa20efd9c87111455b174858544becae7fcc03a3cb7bf5c19b09065c842d02
COMPONENT_ARCHIVE_URL= \
  https://sourceforge.net/projects/ipmitool/files/ipmitool/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://sourceforge.net/projects/ipmitool/
COMPONENT_CLASSIFICATION= System/Hardware
COMPONENT_LICENSE = BSD
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_FMRI = system/management/ipmitool

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CPPFLAGS += -D__EXTENSIONS__

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

CONFIGURE_SBINDIR.32 = /usr/lib

CONFIGURE_OPTIONS += --enable-intf-free=yes
CONFIGURE_OPTIONS += --enable-intf-usb=no
CONFIGURE_OPTIONS += --enable-intf-lanplus
CONFIGURE_OPTIONS += --enable-solaris-opt

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/extended-system-utilities
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/freeipmi
