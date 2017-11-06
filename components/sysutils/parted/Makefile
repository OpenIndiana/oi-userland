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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= parted
# It's illumos-gate version based on parted 1.8.8
# For IPS to perfer it we bumped COMPONENT_VERSION
COMPONENT_VERSION= 1.8.8.1
COMPONENT_SUMMARY= GNU Parted - Partition Editor
COMPONENT_SRC = src
COMPONENT_PROJECT_URL = http://www.gnu.org/software/parted/

include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

clobber: clean

$(SOURCE_DIR)/.prep:
	$(TOUCH) $@

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

clean::
	$(RM) $(SOURCE_DIR)/.prep

download:

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += system/library/libdiskmgt/header-libdiskmgt

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdiskmgt
