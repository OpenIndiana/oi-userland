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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	xmlto
COMPONENT_VERSION= 	0.0.25
COMPONENT_SUMMARY= 	xmlto is a shell-script tool for converting XML files to various formats
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:361cb70d5d0b4b753db00b67ed8bc1d53d0bc96c407d0310aefe854470b7e536
COMPONENT_ARCHIVE_URL= \
  https://fedorahosted.org/releases/x/m/xmlto/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://fedorahosted.org/xmlto/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# Missing files in build dir for configure without this.
#COMPONENT_PRE_CONFIGURE_ACTION =        ($(CP) -a  $(SOURCE_DIR)/* $(@D))

#CONFIGURE_OPTIONS +=  --sysconfdir=/etc

CONFIGURE_ENV += GETOPT=/usr/gnu/bin/getopt

build: $(BUILD_32)

install: $(INSTALL_32)
