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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		planner
COMPONENT_VERSION=	0.14.6
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/action/show/Apps/Planner
COMPONENT_SUMMARY=	Planner is a project managment tool for the Gnome desktop
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:130d29e6d6b8c1994017deba2acca05a4bf83ba1e169635ec8c5c7878abe0696
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.14/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PYTHON_VERSION=2.7

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					aclocal -I. && \
					autoheader && \
					libtoolize --automake --copy --force && \
					automake -a -f -c &&\
					autoconf )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-update-mimedb

CONFIGURE_ENV+=	PERL=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)
CONFIGURE_ENV+= am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV+= am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += image/library/libart
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libglade
REQUIRED_PACKAGES += library/desktop/libgnomecanvas
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
