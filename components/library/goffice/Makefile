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
# Copyright 2018 Jason Martin
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     goffice
COMPONENT_VERSION=  0.10.43
COMPONENT_PROJECT_URL=  http://www.gnome.org
COMPONENT_SUMMARY=  goffice - Document centric set of APIs
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:550fceefa74622b8fe57dd0b030003e31db50edf7f87068ff5e146365108b64e
COMPONENT_ARCHIVE_URL=  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.10/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=  Development/System
COMPONENT_LICENSE=  GPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI=     library/desktop/goffice

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
                    libtoolize --copy --force &&\
                    aclocal -I . &&\
                    automake -c -f -a &&\
                    autoconf )

CFLAGS += $(XPG6MODE) -std=c99

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))

CONFIGURE_ENV+= PYTHON=$(PYTHON)

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

COMPONENT_TEST_ENV += CC=$(CC)
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
    '-ne "/^\# TOTAL:/p" ' \
    '-ne "/^\# PASS:/p" ' \
    '-ne "/^\# SKIP:/p" ' \
    '-ne "/^\# XFAIL:/p" ' \
    '-ne "/^\# FAIL:/p" ' \
    '-ne "/^\# XPASS:/p" ' \
    '-ne "/^\# ERROR::/p" '

# common targets
build:      $(BUILD_32_and_64)

install:    $(INSTALL_32_and_64)

# To prevent "libtool_install_magic: unbound variable"
unexport SHELLOPTS

test:       $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/atk
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
