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

COMPONENT_NAME=		gtk3-nocsd
COMPONENT_VERSION=	3
COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/desktop/gtk3/gtk3-nocsd
COMPONENT_SUMMARY=	A small module used to disable the client side decoration of Gtk+ 3
COMPONENT_CLASSIFICATION=Applications/Plug-ins and Run-times
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://github.com/PCMan/gtk3-nocsd
COMPONENT_ARCHIVE=	$(COMPONENT_NAME).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:779c47d894ee3b6751ddb02b62a76757b77eb81232c4f9335564654817889570
COMPONENT_ARCHIVE_URL=	https://github.com/PCMan/gtk3-nocsd/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

BINDIR.32 = /usr/bin
BINDIR.64 = /usr/bin/$(MACH64)

LIBDIR.32 = /usr/lib
LIBDIR.64 = /usr/lib/$(MACH64)

COMPONENT_INSTALL_ENV += mandir=/usr/share/man
COMPONENT_INSTALL_ENV += bindir=$(BINDIR.$(BITS))
COMPONENT_INSTALL_ENV += libdir=$(LIBDIR.$(BITS))
COMPONENT_INSTALL_ENV += bashcompletiondir=/usr/share/bash-completion/completions

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
