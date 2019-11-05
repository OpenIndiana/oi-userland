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
# Copyright 2015 Alexander Pyhalov
# Copyright 2019 Jason Martin
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libgsf
COMPONENT_VERSION= 1.14.45
COMPONENT_SUMMARY= GNOME Structured File Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:5cbc2c0f1dc44d202fa0c6e3a51e9f17b0c2deb8711ba650432bfde3180b69fa
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.14/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= http://www.gnome.org
COMPONENT_FMRI= library/desktop/libgsf
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE = COPYING.LIB

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D)  && \
                            libtoolize --copy --force &&\
                            aclocal -I m4 &&\
                            autoheader &&\
                            automake -c -f -a &&\
                            autoconf &&\
                            cp /usr/share/gettext/config.rpath .)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-static=no

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

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# To prevent "libtool_install_magic: unbound variable"
unexport SHELLOPTS

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
