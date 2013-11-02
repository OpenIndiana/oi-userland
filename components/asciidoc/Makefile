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

COMPONENT_NAME= 	asciidoc
COMPONENT_VERSION= 	8.6.8
COMPONENT_SUMMARY= 	Text based document generation tool
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:ffb67f59dccaf6f15db72fcd04fdf21a2f9b703d31f94fcd0c49a424a9fcfbc4
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/asciidoc/files/asciidoc/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://www.methods.co.nz/asciidoc/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CP) -a  $(SOURCE_DIR)/* $(@D))

CONFIGURE_OPTIONS +=  --sysconfdir=/etc

build: $(BUILD_32)

install: $(INSTALL_32)
