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
# Copyright 2018 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nimbus
COMPONENT_VERSION=	1.0
COMPONENT_REVISION=	4
COMPONENT_COMMIT=	172733afb6156c59fcd57484854090b798460fd9
COMPONENT_PROJECT_URL=	https://openindiana.org
COMPONENT_SUMMARY=	Engine for Nimbus GTK2/3 Theme
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6815b90625b283a7f6af8763a7e27a182ec11017a825dc0a60ce59589ef747f5
COMPONENT_ARCHIVE_URL=	https://github.com/OpenIndiana/nimbus/archive/$(COMPONENT_COMMIT).tar.gz
COMPONENT_FMRI=		gnome/theme/nimbus
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Theming
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					$(MKDIR) m4 && \
					libtoolize --copy --force && \
					glib-gettextize -f && \
					intltoolize --force --copy --automake && \
					aclocal -I m4 && \
					autoheader && \
					automake --add-missing --copy --force && \
					autoconf)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=$(SOURCE_DIR)/autogen.sh

CONFIGURE_OPTIONS += --sysconfdir=/etc

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
