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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pdsh
COMPONENT_VERSION= 2.33
COMPONENT_FMRI= shell/pdsh
COMPONENT_SUMMARY= Parallel distributed shell
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_PROJECT_URL= https://github.com/chaos/pdsh/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:7368087429d6269f0a6313c406ef38c6a6a947bc003ca7368fc6481b139d942f
COMPONENT_ARCHIVE_URL= \
  https://github.com/chaos/pdsh/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
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
	'-e "/PASS/p"' \
	'-e "/XPASS/p"' \
	'-e "/FAIL/p"' \
	'-e "/XFAIL/p"' \
	'-e "/ERROR/p"' \
	'-e "/SKIP/p"'

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
