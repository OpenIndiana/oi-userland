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
COMPONENT_VERSION=	1.6.4
COMPONENT_PROJECT_URL=  ftp://ftp.gnupg.org/gcrypt/libgcrypt/ 
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:c9bc2c7fe2e5f4ea13b0c74f9d24bcbb1ad889bb39297d8082aebf23f4336026
COMPONENT_ARCHIVE_URL=  ftp://ftp.gnupg.org/gcrypt/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libgcrypt

TPNO=			26276

# Requires new pkgmogrify feature, available in S12 but not 11.3, so do not
# publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

COMPONENT_BUILD_TARGETS = all info

include $(WS_MAKE_RULES)/common.mk
#
# Any improvements made by the upstream to enable compilation of
# libgcrypt library on Solaris primarily reference GNU tools.  The
# library assembly source code contains ANSI notations currently not
# supported by Solaris C language preprocessor, cpp(1). Heavy manual
# patching in a potentially dangerous area would be needed to allow use
# of Solaris Studio as the component compiler.
COMPILER =		gcc

#
# The gcc deliverred with Solaris prior the gcc version 5.3 uses
# different assembler versions on x86 and SPARC platforms. This causes
# compilation issues. The GCC_ROOT explicitly sets the version of the
# compiler to version 5.3 which resolves this problem. The line should
# be removed once gcc on both platforms starts using the same assembler.
GCC_ROOT = /usr/gcc/5.3

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --enable-maintainer-mode 
CONFIGURE_OPTIONS += --disable-asm
CONFIGURE_OPTIONS += --enable-threads=posix
CONFIGURE_OPTIONS += --enable-ciphers=arcfour:blowfish:des:aes:twofish:serpent:rfc2268:seed:camellia:cast5

ASLR_MODE = $(ASLR_ENABLE)

include ../../make-rules/shared-targets.mk

#
# The following target is used during switch of the incompatible libgcrypt.11
# to libgcrypt.20.  Libgcrypt-15 is not delivered as a package. If it has not
# been built yet, we build the library as a target dependency from here and
# deliver a subset of the library (the shared objects only and the second
# level links) to satisfy the ABI compatibility requirements during the ABI
# upgrade period.
$(WS_COMPONENTS)/libgcrypt-15/build/$(MACH$(BITS))/.installed:
	$(GMAKE) -C $(WS_COMPONENTS)/libgcrypt-15 install

$(WS_COMPONENTS)/libgcrypt-15/build/$(MACH$(BITS))/.FRC_%:
	$(GMAKE) -C $(WS_COMPONENTS)/libgcrypt-15 $(@F:.FRC_%=%)

ifneq ($(BUILD_TYPE), evaluation)
install: $(WS_COMPONENTS)/libgcrypt-15/build/$(MACH$(BITS))/.installed
endif

clean clobber:: % : $(WS_COMPONENTS)/libgcrypt-15/build/$(MACH$(BITS))/.FRC_%

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-n -e "/PASS/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/All/p" '

REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
