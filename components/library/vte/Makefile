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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vte
COMPONENT_VERSION=	0.28.2
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Terminal emulation widget for GTK+
COMPONENT_FMRI=		library/desktop/vte
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:8d04e202b617373dfb47689e5e628febe2c58840b34cccc4af4feb88c48df903
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.28/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					libtoolize --force &&\
					gtkdocize &&\
					aclocal -I . &&\
					autoconf &&\
					autoheader &&\
					automake -c -f -a )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-scrollkeeper
CONFIGURE_OPTIONS+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	--localstatedir=/var/lib
CONFIGURE_OPTIONS+=	--disable-Bsymbolic

CONFIGURE_ENV +=	PYTHON=$(PYTHON)

COMPONENT_POST_INSTALL_ACTION = (mv -f $(PROTO_DIR)/usr/lib/python2.6/site-packages/gtk-2.0/vtemodule.so \
	$(PROTO_DIR)/usr/lib/python2.6/site-packages/gtk-2.0/vtemodule-$(BITS).so)

# common targets

$(INSTALL_32):	$(INSTALL_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
