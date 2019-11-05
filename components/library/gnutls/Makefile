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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gnutls
COMPONENT_VERSION= 2.12.24
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= GNU transport layer security library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:792e127c97e5b72bacbbdad16ba7532dc7d81a6197087a574549f473c1627ce7
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.gnutls.org/gcrypt/gnutls/v2.12/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=
  ftp://ftp.gnutls.org/gcrypt/gnutls/v2.12/$(COMPONENT_ARCHIVE).sig
COMPONENT_PROJECT_URL = http://www.gnutls.org
COMPONENT_FMRI = library/gnutls
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_LICENSE = GPLv3
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = /usr/gnu/bin:/usr/bin

CPPFLAGS += -I/usr/include/gmp

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-guile=no
CONFIGURE_OPTIONS += --disable-camellia
CONFIGURE_OPTIONS += --without-p11-kit
CONFIGURE_OPTIONS += --with-libgcrypt

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset set unexpectedly,
# and errors such as "libtool_install_magic: unbound variable"
unexport SHELLOPTS

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/security/libgcrypt
