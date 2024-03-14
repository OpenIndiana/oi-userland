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
# Copyright 2021 Gary Mills
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtk-doc
COMPONENT_MAJOR_VERSION=        1.33
COMPONENT_MINOR_VERSION=        2
COMPONENT_VERSION=      $(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_REVISION=	5
COMPONENT_PROJECT_URL=	https://gitlab.gnome.org/GNOME/gtk-doc
COMPONENT_SUMMARY=	GTK+ DocBook Documentation Generator
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:cc1b709a20eb030a278a1f9842a362e00402b7f834ae1df4c1998a723152bf43
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/documentation-tool/gtk-doc
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPLv3, FDLv1.1

# The built-in tests assume the package has already been installed
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Build configure script
COMPONENT_PREP_ACTION += (cd $(@D); PATH="$(PATH)" autoreconf -fiv)

CONFIGURE_OPTIONS+=	--bindir=$(USRBINDIR)
CONFIGURE_OPTIONS+=	--sbindir=$(USRSBINDIR)
CONFIGURE_OPTIONS+=	--sysconfdir=$(ETCDIR)
CONFIGURE_ENV+=		PYTHON=$(PYTHON)

# Manually added build and runtime dependencies
REQUIRED_PACKAGES += text/itstool
PYTHON_REQUIRED_PACKAGES += library/python/pygments

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += shell/ksh93
