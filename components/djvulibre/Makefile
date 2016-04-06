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

COMPONENT_NAME= djvulibre
COMPONENT_MAJOR_VERSION=3.5.25
COMPONENT_MINOR_VERSION=3
COMPONENT_VERSION= $(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_SUMMARY= DjVu base libraries and utilities
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_MAJOR_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).$(COMPONENT_MINOR_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:898d7ed6dd2fa311a521baa95407a91b20a872d80c45e8245442d64f142cb1e0
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/project/djvu/DjVuLibre/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://djvu.sourceforge.net/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
