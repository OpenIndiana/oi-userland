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
# Copyright 2026 isoriano1968
#

# polkit 125 as in Solaris 11.4 (solaris-userland components/desktop/polkit
# @9d7a655), with two OpenIndiana differences:
#   - rules engine duktape (library/duktape), not mozjs-115;
#   - Solaris patch 07-CVE-2021-3560 dropped: 125 has that fix upstream.
# Session tracking is ConsoleKit (library/xdg/consolekit), as on Solaris.

BUILD_BITS=		64
BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		polkit
COMPONENT_VERSION=	125
COMPONENT_PROJECT_URL=	https://github.com/polkit-org/polkit
COMPONENT_SUMMARY=	polkit authorization toolkit
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:ea5cd6e6e2afa6bad938ee770bf0c2cd9317910f37956faeba2869adcf3747d1
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		system/library/polkit
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	LGPL-2.0-or-later
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

# polkit's tests need its mocklibc and a system bus; Solaris skips them too.
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CFLAGS +=		-std=gnu11
# illumos headers: POSIX getpwuid_r() (not the old Solaris draft), and the
# netgroup functions (setnetgrent & co. in <netdb.h>) need __EXTENSIONS__.
CFLAGS +=		-D_POSIX_PTHREAD_SEMANTICS -D__EXTENSIONS__

CONFIGURE_OPTIONS +=	-Dauthfw=pam
CONFIGURE_OPTIONS +=	-Dos_type=solaris
CONFIGURE_OPTIONS +=	-Djs_engine=duktape
CONFIGURE_OPTIONS +=	-Dsession_tracking=ConsoleKit
CONFIGURE_OPTIONS +=	-Dpolkitd_user=polkitd
CONFIGURE_OPTIONS +=	-Dpolkitd_uid=63
CONFIGURE_OPTIONS +=	-Dintrospection=true
CONFIGURE_OPTIONS +=	-Dman=true
CONFIGURE_OPTIONS +=	-Dgtk_doc=false
CONFIGURE_OPTIONS +=	-Dexamples=false
CONFIGURE_OPTIONS +=	-Dtests=false
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"

# Linux-only files: systemd unit, sysusers.d, tmpfiles.d.  The PAM file
# (usr/lib/pam.d/polkit-1) is not used either: illumos reads /etc/pam.conf,
# whose "other" entries cover the polkit-1 service.
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTOUSRLIBDIR)/systemd $(PROTOUSRLIBDIR)/sysusers.d \
	    $(PROTOUSRLIBDIR)/tmpfiles.d $(PROTOUSRLIBDIR)/pam.d ;

# SMF service, as on Solaris: polkitd starts as root and switches to the
# polkitd user itself.  (Solaris names the user _polkitd; OI's pkglint
# wants user names to start with a lower-case letter.)
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/polkit.xml \
	    $(PROTO_DIR)/lib/svc/manifest/system/polkit.xml ; \
	$(INSTALL) -D -m 0555 $(COMPONENT_DIR)/files/svc-polkit \
	    $(PROTO_DIR)/lib/svc/method/svc-polkit ;

# Build dependencies
REQUIRED_PACKAGES += data/docbook/xsl
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Dependencies (SUNWcs: the SMF milestones the manifest needs; ksh93:
# /sbin/sh for the method script)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += library/duktape
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/xdg/consolekit
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
