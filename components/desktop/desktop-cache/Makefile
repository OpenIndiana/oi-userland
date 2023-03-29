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
# Copyright 2019 Alexander Pyhalov
# Copyright 2023 Klaus Ziegler
# Copyright 2023 Gary Mills
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= desktop-cache
COMPONENT_VERSION= 0.2.2
COMPONENT_REVISION= 9
COMPONENT_SUMMARY= desktop-cache is a set of SMF services used to update the various GNOME desktop caches.
COMPONENT_SRC= desktop-cache-smf-services-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:9cf7328ffddbf86945bef630d8b8fdd61ffcfcac3972b9d0af8668642735de0d
COMPONENT_ARCHIVE_URL= \
  http://dlc.openindiana.org/oi/jds/downloads/sources/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS = --libdir=/lib
CONFIGURE_OPTIONS += --datadir=/usr/share
CONFIGURE_OPTIONS += --sysconfdir=/lib

CONFIGURE_ENV += PYTHON=$(PYTHON)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
