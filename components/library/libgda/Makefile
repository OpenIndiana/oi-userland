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
# Copyright (c) 2017 Dariusz Sendkowski
#
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libgda
COMPONENT_MAJOR_VERSION=5.2
COMPONENT_MINOR_VERSION=4
COMPONENT_FMRI=         library/libgda 
COMPONENT_VERSION=      $(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_SUMMARY=      Libgda is a (relatively small) database access library.
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:2cee38dd583ccbaa5bdf6c01ca5f88cc08758b9b144938a51a478eb2684b765e
COMPONENT_ARCHIVE_URL=  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome-db.org
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-vala
CONFIGURE_OPTIONS += --disable-rpath
CONFIGURE_OPTIONS.32 = --sysconfdir=/etc
CONFIGURE_OPTIONS.64 = --sysconfdir=/etc/$(MACH64)

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

EXAMPLESDIR.32 = $(PROTOUSRSHAREDIR)/libgda-5.0/examples
EXAMPLESDIR.64 = $(PROTOUSRSHAREDIR)/libgda-5.0/examples/$(MACH64)

COMPONENT_POST_INSTALL_ACTION.64 = \
  /usr/bin/elfedit -e 'dyn:runpath /usr/lib/amd64' $(PROTO_DIR)$(USRLIBDIR.$(BITS))/libgda-xslt-5.0.so;\
  $(MV) $(PROTOETCDIR)/$(MACH64)/libgda-5.0/config $(EXAMPLESDIR.$(BITS))/;\
  $(MV) $(PROTOETCDIR)/$(MACH64)/libgda-5.0/sales_test.db $(EXAMPLESDIR.$(BITS))/;

COMPONENT_POST_INSTALL_ACTION.32 = \
  $(MV) $(PROTOETCDIR)/libgda-5.0/config $(EXAMPLESDIR.$(BITS))/;\
  $(MV) $(PROTOETCDIR)/libgda-5.0/sales_test.db $(EXAMPLESDIR.$(BITS))/;


COMPONENT_POST_INSTALL_ACTION += \
   $(MKDIR) $(EXAMPLESDIR.$(BITS));

COMPONENT_POST_INSTALL_ACTION += $(COMPONENT_POST_INSTALL_ACTION.$(BITS))


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TEST)

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtksourceview3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
