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

COMPONENT_NAME= webkit
COMPONENT_VERSION= 1.2.7
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= WebKit rendering engine
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:228a80b3f0132db1342708e8ef7738996f05e30393e0187acf4cab987283718b
COMPONENT_ARCHIVE_URL= \
  http://webkitgtk.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=$(GCC_ROOT)/bin:/usr/g++/bin:/usr/gnu/bin:/usr/bin

COMPONENT_BUILD_ARGS =

CPPFLAGS += -D__EXTENSIONS__

CONFIGURE_ARGS += --x-includes=/usr/X11/include
CONFIGURE_ARGS.32 += --x-libraries=/usr/X11/lib
CONFIGURE_ARGS.64 += --x-libraries=/usr/X11/lib/$(MACH64)

CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV += PERL=$(PERL)
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
