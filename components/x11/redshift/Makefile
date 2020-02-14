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
# Copyright (c) 2016 Sergey Avseyev
# Copyright (c) 2019 Michal Nowak
#

BUILD_BITS=	64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		redshift
COMPONENT_VERSION=	1.12
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://jonls.dk/redshift/
COMPONENT_SUMMARY=	Redshift adjusts the color temperature of your screen according to your surroundings
COMPONENT_FMRI=         x11/redshift
COMPONENT_CLASSIFICATION=       System/X11
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d2f8c5300e3ce2a84fe6584d2f1483aa9eadc668ab1951b2c2b8a03ece3a22ba
COMPONENT_ARCHIVE_URL=	https://github.com/jonls/redshift/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPL-3
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PYTHON_VERSION	= 3.5

CONFIGURE_ENV	+= XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV	+= MSGFMT=/usr/gnu/bin/msgfmt
CONFIGURE_ENV	+= PYTHON=$(PYTHON)

# There are no binary python modules, install them in 32-bit path
CONFIGURE_OPTIONS	+= am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES.32)"
CONFIGURE_OPTIONS	+= --enable-gui

# MATE won't load SVG icons for Redshift, PNG ones work though
COMPONENT_POST_INSTALL_ACTION = \
	$(MKDIR) -p $(PROTOUSRSHAREDIR)/icons/hicolor/24x24/apps/ ;\
	for img in redshift redshift-status-on redshift-status-off; do \
		inkscape -z -e $(PROTOUSRSHAREDIR)/icons/hicolor/24x24/apps/$$img.png -w 24 -h 24 $(PROTOUSRSHAREDIR)/icons/hicolor/scalable/apps/$$img.svg ;\
	done ;

# Build dependencies
REQUIRED_PACKAGES += image/editor/inkscape
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxxf86vm
