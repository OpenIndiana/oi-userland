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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../../make-rules/shared-macros.mk

# This is gcr-4 ABI series

COMPONENT_NAME=			gcr
HUMAN_VERSION=			4.4.0.1
# Unusual version format, so we need to set COMPONENT_VERSION_MAJOR explicitly
COMPONENT_VERSION_MAJOR=	4.4
COMPONENT_SUMMARY=		Library for displaying certificates and crypto UI, accessing key stores
COMPONENT_ARCHIVE_HASH=		sha256:0c3c341e49f9f4f2532a4884509804190a0c2663e6120360bb298c5d174a8098
COMPONENT_FMRI=			library/gnome/gcr-4
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.0-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH = $(PATH.gnu)

# socket related functions needs -lsocket -lnsl
LDFLAGS += -lsocket -lnsl

# This file conflicts with library/gnome/gcr
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRLIBEXECDIR)/gcr-ssh-agent ;

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Some tests are using libgcrypt and libgcrypt uses mlock(3c).  Since mlock()
# is restricted function in illumos we need to make sure the additional
# privileges are granted.
COMPONENT_PRE_TEST_ACTION += \
	/usr/bin/ppriv $$$$ | $(GNU_GREP) -q 'E:.*proc_lock_memory' || ( \
		/usr/bin/printf '\nERROR: The proc_lock_memory privilege is needed!!!\n\n' ; \
		/usr/bin/printf 'Use\n\n\tusermod -K defaultpriv=basic,%s %s\n' \
			'proc_lock_memory' '$(shell /usr/bin/id -u -n)' ; \
		/usr/bin/printf '\nto grant the required privileges.\n\n' ; \
		exit 1 ) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/p11-kit
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
