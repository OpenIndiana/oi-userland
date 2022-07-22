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
# Copyright 2015 Alexander Pyhalov
#

BUILD_STYLE=configure
# The bitness should be changed in illumos-gate
BUILD_BITS=32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ospm
COMPONENT_VERSION=      1.4.11
COMPONENT_REVISION=     4
COMPONENT_SUMMARY=      Print Monitor
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:bad98c2e925d40d62cbcd64755f006ccbd8c1ea00fadae6520d9adb43da93699
COMPONENT_ARCHIVE_URL=  http://dlc.openindiana.org/oi/jds/downloads/sources/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         print/lp/print-manager
COMPONENT_CLASSIFICATION=System/Printing
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=$(ETCDIR)

CONFIGURE_ENV+=	PERL=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libglade
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += library/print/open-printing
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
