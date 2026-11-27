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
COMPONENT_LICENSE_FILE=	COPYING

# The tests need a system bus
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

# POSIX getpwuid_r(), setnetgrent()
CFLAGS +=		-D_POSIX_PTHREAD_SEMANTICS -D__EXTENSIONS__

CONFIGURE_OPTIONS +=	-Dos_type=solaris
CONFIGURE_OPTIONS +=	-Dsession_tracking=ConsoleKit
CONFIGURE_OPTIONS +=	-Dpolkitd_uid=63
CONFIGURE_OPTIONS +=	-Dman=true

# systemd, sysusers.d, tmpfiles.d and pam.d files are not used on illumos
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTOUSRLIBDIR)/systemd $(PROTOUSRLIBDIR)/sysusers.d \
	    $(PROTOUSRLIBDIR)/tmpfiles.d $(PROTOUSRLIBDIR)/pam.d ;

COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/polkit.xml \
	    $(PROTOLIBDIR)/svc/manifest/system/polkit.xml ; \
	$(INSTALL) -D -m 0555 $(COMPONENT_DIR)/files/svc-polkit \
	    $(PROTOLIBDIR)/svc/method/svc-polkit ;

# man pages
REQUIRED_PACKAGES += data/docbook/xsl
REQUIRED_PACKAGES += library/libxslt
# session tracking
REQUIRED_PACKAGES += library/xdg/consolekit

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/duktape
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
