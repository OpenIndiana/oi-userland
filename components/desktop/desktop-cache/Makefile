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
# Copyright 2023 Gary Mills
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= desktop-cache
COMPONENT_VERSION= 0.2.2
COMPONENT_REVISION= 22
COMPONENT_SUMMARY= desktop-cache is a set of SMF services used to update the various GNOME desktop caches.
COMPONENT_SRC= desktop-cache-smf-services-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:1be28add6bc1877fd1a9e2a57884a98729abe081033b98ef8bf8fd9c7d7062fb
COMPONENT_ARCHIVE_URL= \
  http://dlc.openindiana.org/oi/jds/downloads/sources/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			service/gnome/desktop-cache
COMPONENT_CLASSIFICATION=	System/Services
COMPONENT_LICENSE=		CDDL
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS = --libdir=/lib
CONFIGURE_OPTIONS += --datadir=/usr/share
CONFIGURE_OPTIONS += --sysconfdir=/lib

CONFIGURE_ENV += PYTHON=$(PYTHON)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
