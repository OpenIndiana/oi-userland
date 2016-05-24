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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libgsf
# This is the last version which provides python gsfgnomemodule
COMPONENT_VERSION= 1.14.21
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GNOME Structured File Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:eef0a9d6eca4e6af6c16b208947e3c958c428b94d22792bdd0b80c08a4b301db
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.14/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= library/desktop/libgsf
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING.LIB

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
                                        libtoolize --copy --force &&\
                                        aclocal -I m4 &&\
					autoheader &&\
                                        automake -c -f -a &&\
                                        autoconf &&\
					cp /usr/share/gettext/config.rpath .)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV+=	am_cv_python_pyexecdir=$(PYTHON.2.6.VENDOR_PACKAGES.$(BITS))
CONFIGURE_ENV+=	am_cv_python_pythondir=$(PYTHON.2.6.VENDOR_PACKAGES.$(BITS))
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --with-python
CONFIGURE_OPTIONS += --with-bz2
CONFIGURE_OPTIONS += --with-gnome-vfs
CONFIGURE_OPTIONS += --with-gio

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
