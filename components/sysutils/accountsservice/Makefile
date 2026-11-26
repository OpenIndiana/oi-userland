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

# AccountsService 0.6.55 as in Solaris 11.4 (solaris-userland
# components/desktop/accountsservice @9d7a655), with its five patches.
# OpenIndiana differences:
#   - admin group "staff" (Solaris: sysadmin), the user's choice; note that
#     every OI user is in staff, so all show as administrators;
#   - daemon in /usr/libexec (OI convention), no gtk-doc.

BUILD_BITS=		64
BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		accountsservice
COMPONENT_VERSION=	0.6.55
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/AccountsService/
COMPONENT_SUMMARY=	AccountsService - D-Bus interface for user account query and manipulation
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:ff2b2419a7e06bd9cb335ffe391c7409b49a0f0130b890bd54692a3986699c9b
COMPONENT_ARCHIVE_URL=	https://www.freedesktop.org/software/accountsservice/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/library/accountsservice
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	GPL-3.0-or-later
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# illumos headers: POSIX getpwnam_r() & co., and the BSD/SVID extras.
CFLAGS +=		-D_POSIX_PTHREAD_SEMANTICS -D__EXTENSIONS__

CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBEXECDIR)
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	-Dsystemd=false
CONFIGURE_OPTIONS +=	-Delogind=false
CONFIGURE_OPTIONS +=	-Dsystemdsystemunitdir=no
CONFIGURE_OPTIONS +=	-Dadmin_group=staff
CONFIGURE_OPTIONS +=	-Dminimum_uid=100
CONFIGURE_OPTIONS +=	-Dintrospection=true
CONFIGURE_OPTIONS +=	-Ddocbook=false
CONFIGURE_OPTIONS +=	-Dgtk_doc=false

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"

COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/accountsservice.xml \
	    $(PROTO_DIR)/lib/svc/manifest/system/accountsservice.xml ; \
	$(INSTALL) -D -m 0555 $(COMPONENT_DIR)/files/svc-accountsservice \
	    $(PROTO_DIR)/lib/svc/method/svc-accountsservice ;

# Build dependencies
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Dependencies (SUNWcs: SMF milestones; ksh93: /sbin/sh for the method)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/polkit
