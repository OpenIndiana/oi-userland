#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
# Copyright 2024 Andreas Wacknitz
#

BUILD_STYLE= configure
# 32 bit needs to be build first because we remove the contents of $(USRLIBEXECDIR) in COMPONENT_POST_INSTALL_ACTION.32
BUILD_BITS= 32_and_64
PREFERRED_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ConsoleKit
COMPONENT_VERSION=      0.4.6
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://www.freedesktop.org/wiki/Software/ConsoleKit
COMPONENT_SUMMARY=      Framework for tracking users, login sessions, and seats
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:b41d17e06f80059589fbeefe96ad07bcc564c49e65516da1caf975146475565c
COMPONENT_ARCHIVE_URL=  https://www.freedesktop.org/software/ConsoleKit/dist/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/xdg/consolekit
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Sessions
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= ( \
	cd $(@D) && \
	glib-gettextize -f && \
	libtoolize --copy --force && \
	aclocal -I . && \
	automake -c -f -a && \
	PATH="$(PATH)" autoconf )

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32) ;
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRSBINDIR32) ;
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRLIBEXECDIR32) ;

MACHBITS=$(patsubst /i86,,/$(MACH$(BITS)))

CONFIGURE_OPTIONS += --sysconfdir=/etc
# Use the following if libexec and libexec/amd64 should be used for 32 and 64 bit.
#CONFIGURE_OPTIONS += --libexecdir=/usr/libexec$(MACHBITS)
CONFIGURE_OPTIONS += --libexecdir=/usr/libexec
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --enable-pam-module
CONFIGURE_OPTIONS += --with-pam-module-dir=/usr/lib/security$(MACHBITS)
CONFIGURE_OPTIONS += --enable-rbac-shutdown=solaris.system.shutdown

# Manually added build dependencies
REQUIRED_PACKAGES+= x11/header/x11-protocols
REQUIRED_PACKAGES+= x11/library/libpthread-stubs

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += x11/library/libx11
