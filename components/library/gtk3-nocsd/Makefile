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

BUILD_BITS=			64
BUILD_STYLE=		justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtk3-nocsd
COMPONENT_VERSION=	3
COMPONENT_REVISION=	3
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

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_INSTALL_ENV += bindir=$(USRBINDIR)
COMPONENT_INSTALL_ENV += libdir=$(USRLIBDIR.$(BITS))
COMPONENT_INSTALL_ENV += mandir=$(USRSHAREMANDIR)
COMPONENT_INSTALL_ENV += bashcompletiondir=$(BASH_COMPLETIONS_PATH)

# Manually added build dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
