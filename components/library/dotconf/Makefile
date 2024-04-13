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
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= dotconf
COMPONENT_VERSION= 1.4.1
COMPONENT_SUMMARY= Configuration file parser
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5922c46cacf99b2ecc4853d28a2bda4a489292e73276e604bd9cba29dfca892d
COMPONENT_PROJECT_URL=	https://github.com/williamh/dotconf
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI= library/desktop/dotconf
COMPONENT_CLASSIFICATION= Applications/Universal Access
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D) && PATH="$(PATH)" autoreconf -fi)

CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
