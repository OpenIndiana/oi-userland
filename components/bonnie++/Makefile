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

COMPONENT_NAME= bonnie++
COMPONENT_VERSION= 1.03e
IPS_COMPONENT_VERSION= 1.3.5
HUMAN_VERSION= $(COMPONENT_VERSION)
COMPONENT_SUMMARY= bonnie++ - Benchmark Harddrive utility
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
  sha256:cb3866116634bf65760b6806be4afa7e24a1cad6f145c876df8721f01ba2e2cb
COMPONENT_ARCHIVE_URL= \
  http://www.coker.com.au/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.coker.com.au/bonnie++/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV	+=  PERL=$(PERL)

build: $(BUILD_32)

install: $(INSTALL_32)
