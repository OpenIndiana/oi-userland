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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		redshift
COMPONENT_VERSION=	1.12
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://jonls.dk/redshift/
COMPONENT_SUMMARY=	Redshift adjusts the color temperature of your screen according to your surroundings
COMPONENT_FMRI=         x11/redshift
COMPONENT_CLASSIFICATION=       System/X11
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d2f8c5300e3ce2a84fe6584d2f1483aa9eadc668ab1951b2c2b8a03ece3a22ba
COMPONENT_ARCHIVE_URL=	https://github.com/jonls/redshift/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPL-3.0-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# configure expects GNU gettext
PATH = $(PATH.gnu)

CONFIGURE_OPTIONS += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_OPTIONS += --enable-gui

# MATE won't load SVG icons for Redshift, PNG ones work though
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) -p $(PROTOUSRSHAREDIR)/icons/hicolor/24x24/apps/ ;\
	for img in redshift redshift-status-on redshift-status-off; do \
		convert \
		    $(PROTOUSRSHAREDIR)/icons/hicolor/scalable/apps/$$img.svg \
		    -resize 24x24 \
		    $(PROTOUSRSHAREDIR)/icons/hicolor/24x24/apps/$$img.png ; \
	done ;

# Update Python shebang to point to version we build for
PYTHON_SCRIPTS += $(USRBINDIR)/redshift-gtk

# Build dependencies
REQUIRED_PACKAGES += image/editor/inkscape
REQUIRED_PACKAGES += image/imagemagick
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxxf86vm
