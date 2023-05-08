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
# Copyright 2018 Michal Nowak
#
BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtkmm3
COMPONENT_VERSION=	3.24.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	gtkmm - C++ Wrapper for the Gtk+ Library
COMPONENT_SRC=		gtkmm-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:6d71091bcd1863133460d4188d04102810e9123de19706fb656b7bb915b4adc3
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/gtkmm/3.24/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gtkmm.org/
COMPONENT_FMRI=		library/desktop/c++/gtkmm3
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/cairomm
REQUIRED_PACKAGES += library/desktop/c++/pangomm
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
