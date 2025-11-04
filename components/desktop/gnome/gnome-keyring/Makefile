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
# Copyright (c) 2017 Alexander Pyhalov
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018 Michal Nowak
# Copyright (c) 2021 Andreas Wacknitz
# Copyright (c) 2023 Klaus Ziegler
#

USE_PARALLEL_BUILD = yes

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-keyring
COMPONENT_VERSION=	46.2
COMPONENT_SUMMARY=	GNOME Keyring is a collection of components that store secrets, passwords, keys, certificates and make them available to applications
COMPONENT_ARCHIVE_HASH= sha256:bf26c966b8a8b7f3285ecc8bb3e467b9c20f9535b94dc451c9c559ddcff61925
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Sessions
COMPONENT_FMRI=		gnome/gnome-keyring
COMPONENT_LICENSE=	GPL-2.0-only AND LGPL-2.1-only

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Required due to patches.
COMPONENT_PREP_ACTION = ( cd $(@D) && PATH="$(PATH)" autoreconf -fiv )

PAM_MODULE_DIR = $(USRLIBDIR)/security/$(MACH64)

CONFIGURE_ENV += MAKE="$(GMAKE)"

CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-selinux
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gpg-agent
CONFIGURE_OPTIONS += --enable-pam
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-ssh-agent
CONFIGURE_OPTIONS += --with-pam-dir=$(PAM_MODULE_DIR)
CONFIGURE_OPTIONS += --with-pic
# Linux-specific capabilities support.
CONFIGURE_OPTIONS += --without-libcap-ng

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

COMPONENT_TEST_ARGS = -k -i

COMPONENT_TEST_TRANSFORMS = \
	'-e "s/scratch-test.*/scratch-test-import\*pkcs8/" ' \
	'-e "s/glib.*\//GLIB2\//" ' \
	"-e 's|$(SOURCE_DIR)|\$$(SOURCE_DIR)|g'" \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/ERROR:/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
