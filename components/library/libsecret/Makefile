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
# Copyright 2016 Alexander Pyhalov
#

BUILD_BITS= 64_and_32
BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_COMMON_TEST_MASTER= no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libsecret
HUMAN_VERSION=		0.21.7
COMPONENT_SUMMARY=	GObject-based library for storing and receiving secrets
COMPONENT_ARCHIVE_HASH=	sha256:6b452e4750590a2b5617adc40026f28d2f4903de15f1250e1d1c40bfd68ed55e
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Security
COMPONENT_LICENSE=      LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

COMPONENT_FMRI.$(COMPONENT_NAME)-32=	$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.$(COMPONENT_NAME)-32=	$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# There is no 32-bit gobject-introspection
CONFIGURE_OPTIONS.32 += -Dintrospection=false
# vapi files and man pages created during the 64-bit build are enough.  They
# would overlap otherwise anyway.
CONFIGURE_OPTIONS.32 += -Dvapi=false
CONFIGURE_OPTIONS.32 += -Dmanpage=false
# The documentation build is not possible without introspection.
# Also, the documentation built during the 64-bit build is enough.
CONFIGURE_OPTIONS.32 += -Dgtk_doc=false
# There is neither libgcrypt nor gnutls with 32-bit support
CONFIGURE_OPTIONS.32 += -Dcrypto=disabled

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRBINDIR32) ;
# Drop include and locale files created during the 32-bit build.  The 64-bit
# build produces same files at the same location so we will use those.
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRINCDIR) ;
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRSHARELOCALEDIR) ;

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :1 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Testing needs to find dbus-daemon
COMPONENT_TEST_ENV += PATH="$(PATH):$(USRLIBEXECDIR)"

# Some tests are using mlock(3c) and expects it to pass.  Since mlock() is
# restricted function in illumos we need to make sure the additional privileges
# are granted.
COMPONENT_PRE_TEST_ACTION += \
	/usr/bin/ppriv $$$$ | $(GNU_GREP) -q 'E:.*proc_lock_memory' || ( \
		/usr/bin/printf '\nERROR: The proc_lock_memory privilege is needed!!!\n\n' ; \
		/usr/bin/printf 'Use\n\n\tusermod -K defaultpriv=basic,%s %s\n' \
			'proc_lock_memory' '$(shell /usr/bin/id -u -n)' ; \
		/usr/bin/printf '\nto grant the required privileges.\n\n' ; \
		exit 1 ) ;

# Manually added dependencies
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
