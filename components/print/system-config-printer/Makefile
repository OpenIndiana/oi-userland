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
# Copyright 2018 Michal Nowak
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= system-config-printer
COMPONENT_VERSION= 1.5.12
COMPONENT_REVISION= 3
IPS_COMPONENT_VERSION= 2.30.0
COMPONENT_SUMMARY= Print Manager for CUPS
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:6b16717dfe1f64ada6ef9398dcab07b8b7c864f006588d03002e41b743cf1e14
COMPONENT_ARCHIVE_URL= \
  https://github.com/OpenPrinting/system-config-printer/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://cyberelk.net/tim/software/system-config-printer/

PYTHON_VERSION= 3.5

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION =	(chmod -R u+r  $(SOURCE_DIR) && \
					cp -rp $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV	+= PYTHON=$(PYTHON)

# Build dependencies
REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pycups-35
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += library/python/python-dbus-35
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += SUNWcs
