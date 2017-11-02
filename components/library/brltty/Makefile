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
# Copyright 2017 Gary Mills
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= brltty
COMPONENT_VERSION= 5.5
COMPONENT_SUMMARY= Braille support
COMPONENT_FMRI= library/accessibility/brltty
COMPONENT_CLASSIFICATION= Applications/Universal Access
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:915d87d122f7795a201d217ba903cbdf1c83bb4962dd0c283e9525c9adc2996a
COMPONENT_ARCHIVE_URL= \
  http://www.mielke.cc/brltty/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mielke.cc/brltty/
COMPONENT_LICENSE = GPLv2,LGPLv2.1

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
                                        autoconf -f )

# Missing files on install without this
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

ICU_CONFIG.32=/usr/bin/icu-config
ICU_CONFIG.64=/usr/bin/$(MACH64)/icu-config

# Orca uses python 3.4, so we need to match
PYTHON_VERSION = 3.4
CONFIGURE_ENV += PYTHON="$(PYTHON)"
PKG_MACROS += PYVER="$(PYTHON_VERSION)"

CYTHON.32 = /usr/bin/cython-$(PYTHON_VERSION)
CYTHON.64 = /usr/bin/$(MACH64)/cython-$(PYTHON_VERSION)

CFLAGS +=	$(CC_PIC)

CONFIGURE_OPTIONS +=    --enable-python-bindings
CONFIGURE_OPTIONS +=    --disable-java-bindings
CONFIGURE_OPTIONS +=    --disable-lisp-bindings
CONFIGURE_OPTIONS +=    --disable-ocaml-bindings
CONFIGURE_OPTIONS +=    --disable-tcl-bindings
CONFIGURE_OPTIONS +=    --disable-speech-support
CONFIGURE_OPTIONS +=    --disable-stripping
CONFIGURE_OPTIONS +=    --disable-polkit # requires SO_PEERCRED support
CONFIGURE_OPTIONS +=    --without-midi-package
CONFIGURE_OPTIONS +=    --without-writable-directory
CONFIGURE_OPTIONS +=    --with-gui-toolkit=Xaw
CONFIGURE_OPTIONS +=    --localstatedir=/var
CONFIGURE_OPTIONS +=    --sysconfdir=/etc

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += CYTHON="$(CYTHON)"
CONFIGURE_ENV += ICU_CONFIG="$(ICU_CONFIG.$(BITS))"
CONFIGURE_ENV += ac_cv_path_MSGFMT="/usr/gnu/bin/msgfmt"

PYTHON_ENV +=   CC="$(CC)"
PYTHON_ENV +=   CFLAGS="$(CFLAGS)"
PYTHON_ENV +=   LDFLAGS="$(LDFLAGS)"
PYTHON_ENV +=   LDSHARED="$(CC) -shared"
COMPONENT_BUILD_ENV += $(PYTHON_ENV)
COMPONENT_INSTALL_ENV += $(PYTHON_ENV)
COMPONENT_TEST_ENV += $(PYTHON_ENV)

COMPONENT_INSTALL_ARGS += INSTALL_ROOT=$(PROTO_DIR)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += system/header/header-ugen

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/python/cython-34
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
