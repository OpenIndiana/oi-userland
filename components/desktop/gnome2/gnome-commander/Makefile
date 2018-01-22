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
# Copyright (c) 2017 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-commander
COMPONENT_MJR_VERSION=	1.8
COMPONENT_MNR_VERSION=	0
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	https://gcmd.github.io/
COMPONENT_SUMMARY=	gnome commander file manager
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d0e73077fe22ae1e00d93f0112e0e019cf40b15419dfa82e51c9d5f30849946b
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/file-manager/gnome-commander
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/File Managers

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =      (cd $(@D) && autoreconf -fi)

COMPONENT_PRE_CONFIGURE_ACTION =      (cp -a $(SOURCE_DIR)/* $(@D))
CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-scrollkeeper
CONFIGURE_OPTIONS+=	--without-unique

CONFIGURE_ENV+=	PERL=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/exiv2
REQUIRED_PACKAGES += library/audio/taglib
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libgnome
REQUIRED_PACKAGES += library/desktop/libgnomeui
REQUIRED_PACKAGES += library/desktop/libgsf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-vfs
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/math
