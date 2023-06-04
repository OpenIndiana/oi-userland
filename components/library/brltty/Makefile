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
# Copyright 2021 Andreas Wacknitz
# Copyright 2022 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         brltty
COMPONENT_VERSION=      6.5
COMPONENT_REVISION=     2
COMPONENT_SUMMARY=      Braille support
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:2f173535291ba39b5a9fc8d80c349234333d92042d95d6dd88796c98a02f316b
COMPONENT_PROJECT_URL=  http://www.mielke.cc/brltty/
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/accessibility/brltty
COMPONENT_CLASSIFICATION=Applications/Universal Access
COMPONENT_LICENSE=      GPLv2,LGPLv2.1

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Missing files on install without this
COMPONENT_PRE_CONFIGURE_ACTION= ($(CLONEY) $(SOURCE_DIR) $(@D)) ;

# Needed because we patch configure.ac
COMPONENT_PRE_CONFIGURE_ACTION += (cd $(@D) ; ./autogen) ;

CC +=		$(CC_BITS)
CFLAGS +=	$(CC_PIC)
CFLAGS +=	-I /usr/include/pcre -I /usr/include/liblouis
CPPFLAGS +=	-D_SYS_UCONTEXT_H # Workaround Bug Id 15558893

# Disable python bindings for now.
CONFIGURE_ENV += PYTHON="$(PYTHON)"
PKG_MACROS += PYVER="$(PYTHON_VERSION)"

CONFIGURE_OPTIONS +=    --disable-python-bindings
CONFIGURE_OPTIONS +=    --disable-java-bindings
CONFIGURE_OPTIONS +=    --disable-lisp-bindings
CONFIGURE_OPTIONS +=    --disable-ocaml-bindings
CONFIGURE_OPTIONS +=    --disable-tcl-bindings
CONFIGURE_OPTIONS +=    --disable-speech-support
CONFIGURE_OPTIONS +=    --disable-stripping
CONFIGURE_OPTIONS +=    --disable-lua-bindings
CONFIGURE_OPTIONS +=    --disable-polkit # requires SO_PEERCRED support
CONFIGURE_OPTIONS +=    --without-midi-package
CONFIGURE_OPTIONS +=    --without-writable-directory
CONFIGURE_OPTIONS +=    --with-gui-toolkit=Xaw
CONFIGURE_OPTIONS +=    --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS +=    --sysconfdir=$(ETCDIR)

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += CYTHON="$(CYTHON)"
CONFIGURE_ENV += ac_cv_path_MSGFMT="/usr/gnu/bin/msgfmt"

# Needed by call to setup.py for python module in build phase
# (copied from make-rules/setup.py.mk)
PYTHON_ENV +=   CC="$(CC)"
PYTHON_ENV +=   CFLAGS="$(CFLAGS)"
PYTHON_ENV +=   LDFLAGS="$(LDFLAGS) -m64"
PYTHON_ENV +=   LDSHARED="$(CC) -shared -m64"
COMPONENT_BUILD_ENV += $(PYTHON_ENV)
COMPONENT_INSTALL_ENV += $(PYTHON_ENV)
COMPONENT_TEST_ENV += $(PYTHON_ENV)

# brltty's Makefile doesn't let us pass --install-lib to setup.py so we
# fake it with a symlink in the proto area
#COMPONENT_POST_INSTALL_ACTION += \
#    $(MKDIR) $(PROTO_DIR)$(PYTHON_DIR) && \
#    $(RM) $(PROTO_DIR)$(PYTHON_LIB) && \
#    $(SYMLINK) site-packages $(PROTO_DIR)$(PYTHON_LIB)

COMPONENT_INSTALL_ARGS += INSTALL_ROOT=$(PROTO_DIR)

# Build dependencies
REQUIRED_PACKAGES += system/header/header-ugen

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/liblouis
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
