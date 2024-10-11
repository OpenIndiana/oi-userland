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
# Copyright 2017 Gary Mills
# Copyright (c) 2014 Alexander Pyhalov
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		seahorse
COMPONENT_MJR_VERSION=	47
COMPONENT_MNR_VERSION=	0.1
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY=	Seahorse is a GNOME application for managing encryption keys
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/Seahorse
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:9c1917e4a61f7febb787849ce36ce717fce706c346880b991d056d54dadbcacc
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		gnome/security/seahorse
COMPONENT_CLASSIFICATION=System/Security
COMPONENT_LICENSE=	GPLv2, LGPLv2.1, Creative Commons Attribution-ShareAlike 3.0 Unported License

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Assumes GNU msgfmt in PATH.
CONFIGURE_ENV += PATH="$(PATH.gnu)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
COMPONENT_BUILD_ENV += PATH="$(PATH.gnu)"
COMPONENT_INSTALL_ENV += PATH="$(PATH.gnu)"
COMPONENT_TEST_ENV += PATH="$(PATH.gnu)"
CONFIGURE_OPTIONS += -Dhkp-support=false -Dmanpage=true

CPPFLAGS += -I/usr/include/openldap

LDFLAGS += -lldap-2.6 -llber-2.6

# Note that some gpgme tests fail because we don't have proper file monitoring solutions.
#
# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/libhandy
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += system/library
