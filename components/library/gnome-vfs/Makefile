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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gnome-vfs
COMPONENT_VERSION= 2.24.4
COMPONENT_REVISION= 5
COMPONENT_FMRI= library/gnome/gnome-vfs
COMPONENT_SUMMARY= GNOME virtual file system framework
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:62de64b5b804eb04104ff98fcd6a8b7276d510a49fbd9c0feb568f8996444faa
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.24/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= http://www.gnome.org
COMPONENT_CLASSIFICATION=  Desktop (GNOME)/Libraries
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -r $(SOURCE_DIR)/* $(@D) && \
					cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
					cd $(@D)/po-sun && $(MAKE) all &&\
					cd $(@D) && glib-gettextize --force --copy &&\
					libtoolize --automake --copy --force && \
					glib-gettextize --force &&\
					intltoolize --force --copy --automake &&\
					aclocal -I . &&\
					gtkdocize &&\
					autoheader &&\
					automake -a -f -c --gnu &&\
					autoconf )

CONFIGURE_SCRIPT=       $(@D)/configure

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-fam
CONFIGURE_OPTIONS += --enable-samba
CONFIGURE_OPTIONS += --with-samba-includes=/usr/include/libsmbclient
CONFIGURE_OPTIONS += --with-samba-libs=/usr/lib/libsmbclient
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS.64 += --disable-avahi

CONFIGURE_ENV+= PERL=$(PERL)

COMPONENT_INSTALL_ENV+=  GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += desktop/gnome-mime-data

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/samba/libsmbclient
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/network/avahi
