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

COMPONENT_NAME= pdsh
COMPONENT_VERSION= 2.31
COMPONENT_FMRI= shell/pdsh
COMPONENT_SUMMARY= Parallel distributed shell
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_PROJECT_URL= https://github.com/grondo/pdsh/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:0ee066ce395703285cf4f6cf00b54b7097d12457a4b1c146bc6f33d8ba73caa7
COMPONENT_ARCHIVE_URL= \
  https://github.com/grondo/pdsh/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# Required for the test suite
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_BINDIR.64 = $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-ssh
CONFIGURE_OPTIONS += --with-rsh
CONFIGURE_OPTIONS += --with-readline
CONFIGURE_OPTIONS += --with-dshgroups

COMPONENT_TEST_TRANSFORMS= \
	'-n' \
	'-e "/^ok/p"' \
	'-e "/^not ok/p"' \
	'-e "/passed/p"' \
	'-e "/failed/p"' \
	'-e "/fixed/p"' \
	'-e "/breakage/p"'

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
