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
# Copyright 2019 Jason Martin
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     goffice
COMPONENT_VERSION=  0.10.59
COMPONENT_SUMMARY=  goffice - Document centric set of APIs
COMPONENT_PROJECT_URL=  https://www.gnome.org
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:b08f7173325594b71fbbea476a30b5b3120c3dadff5c0a26d140e4e524916622
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/0.10/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     library/desktop/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=  Development/System
COMPONENT_LICENSE=  GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D)  && \
    libtoolize --copy --force &&\
	aclocal -I . &&\
    automake -c -f -a &&\
    autoconf )

CFLAGS += $(XPG6MODE) -std=c99

CONFIGURE_ENV += PYTHON=$(PYTHON)

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

COMPONENT_TEST_ENV += CC=$(CC)

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgsf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libspectre
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
