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

#
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgcrypt
COMPONENT_VERSION=	1.5.3
COMPONENT_PROJECT_URL=  ftp://ftp.gnupg.org/gcrypt/libgcrypt/ 
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:bcf5334e7da352c45de6aec5d2084ce9a1d30029ff4a4a5da13f1848874759d1
COMPONENT_ARCHIVE_URL=  ftp://ftp.gnupg.org/gcrypt/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libgcrypt

TPNO=			7588

COMPONENT_BUILD_TARGETS = all info

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --enable-maintainer-mode 
CONFIGURE_OPTIONS += --disable-asm 
CONFIGURE_OPTIONS += --enable-ciphers=arcfour:blowfish:des:aes:twofish:serpent:rfc2268:seed:camellia:cast5

#
# The following target is used during switch of the incompatible libgcrypt.11
# to libgcrypt.20.  Libgcrypt-15 is not delivered as a package. If it has not
# been built yet, we build the library as a target dependency from here and
# deliver a subset of the library (the shared objects only and the second
# level links) to satisfy the ABI compatibility requirements during the ABI
# upgrade period.
$(COMPONENT_DIR)/../libgcrypt/build/$(MACH32)/.installed \
$(COMPONENT_DIR)/../libgcrypt/build/$(MACH64)/.installed:
	$(GMAKE) install

include ../../make-rules/shared-targets.mk

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-n -e "/PASS/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/All/p" '

LIBGCRYPT_PROTO_USRLIB = \
	$(WS_COMPONENTS)/libgcrypt/build/prototype/$(MACH)$(USRLIB)
COMPONENT_POST_INSTALL_ACTION = \
	$(INSTALL) -D -m 644 \
		$(BUILD_DIR)/$(MACH$(BITS))/src/.libs/libgcrypt.so.11.8.2 \
		-t $(LIBGCRYPT_PROTO_USRLIB); \
	(cd $(LIBGCRYPT_PROTO_USRLIB); $(RM) -f libgcrypt.so.11; \
	$(LN) -s -f libgcrypt.so.11.8.2 libgcrypt.so.11)

REQUIRED_PACKAGES += library/security/libgpg-error
