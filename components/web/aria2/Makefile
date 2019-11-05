#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2016 Predrag Zečević
# Copyright (c) 2019 Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           aria2
COMPONENT_VERSION=        1.34.0
COMPONENT_REVISION=       2
COMPONENT_FMRI=           web/aria2
COMPONENT_PROJECT_URL=    https://aria2.github.io/
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_SUMMARY= \
    aria2 - lightweight multi-protocol and multi-source download utility
COMPONENT_SRC=         $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=     $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:aa8cbe4c8408229b9dbd62bf2d7cc38dd1ebe41e9614db17460e564f76f2f246
COMPONENT_ARCHIVE_URL= \
    https://github.com/aria2/aria2/releases/download/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LD_OPTIONS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

CXXFLAGS += -I/usr/include/gmp

LDFLAGS += -lsocket -lnsl

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-ca-bundle=/etc/certs/ca-certificates.crt
CONFIGURE_OPTIONS += --with-bashcompletiondir=/usr/share/bash-completion/completions/

CONFIGURE_ENV += LD_OPTIONS="$(LD_OPTIONS)"

COMPONENT_TEST_ENV += LD_OPTIONS="$(LD_OPTIONS)"

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += database/sqlite-3
# cppunit is for tests
REQUIRED_PACKAGES += developer/cppunit
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
