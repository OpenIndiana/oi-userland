#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2017 Dariusz Sendkowski
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libxdg-basedir
COMPONENT_VERSION=      1.2.0
COMPONENT_PROJECT_URL=  https://github.com/devnev/$(COMPONENT_NAME)
COMPONENT_SUMMARY=      An implementation of the XDG Base Directory specifications.
COMPONENT_FMRI=         library/xdg/libxdg-basedir 
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:1c2b0032a539033313b5be2e48ddd0ae94c84faf21d93956d53562eef4614868
COMPONENT_ARCHIVE_URL=  https://github.com/devnev/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk



COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -f -i)


build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TEST)

REQUIRED_PACKAGES += system/library
