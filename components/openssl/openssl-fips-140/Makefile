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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin:/usr/perl5/bin
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin:/usr/perl5/bin
endif

COMPONENT_NAME =	openssl-fips-140
# Note: COMPONENT_VERSION is the core OpenSSL version, and IPS_COMPONENT_VERSION
# is the FIPS module version. The COMPONENT_VERSION changes with the core
# OpenSSL version, but the IPS_COMPONENT_VERSION is purposely only to change if
# the FIPS module version changes.
COMPONENT_VERSION =	1.0.2k
IPS_COMPONENT_VERSION = 2.0.13
COMPONENT_PROJECT_URL=	http://www.openssl.org/
COMPONENT_SRC_NAME =	openssl
COMPONENT_SRC =		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6b3977c61f2aedf0f96367dcfb5c6e578cf37e7b8d913b4ecb6643c3cb88d8c0
COMPONENT_ARCHIVE_URL =	$(COMPONENT_PROJECT_URL)source/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/openssl

TPNO=			33605

# Clone the patch files to the patches-all dir.
# COPY_COMMON_FILES is there so that rsync is called as soon as
# the Makefile is parsed.
PATCH_DIR=patches-all
CLEAN_PATHS += $(PATCH_DIR)
COPY_COMMON_FILES:= $(shell rsync -ac ../common/patches/ patches/ $(PATCH_DIR))

# OpenSSL FIPS directory
OPENSSL_FIPS_DIR = $(COMPONENT_DIR)/../openssl-fips

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

# OpenSSL does not use autoconf but its own configure system.
CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure

# Used in the configure options below.
PKCS11_LIB32 = /usr/lib/libpkcs11.so.1
PKCS11_LIB64 = /usr/lib/64/libpkcs11.so.1
ENGINESDIR_32 = /lib/openssl/engines
ENGINESDIR_64 = /lib/openssl/engines/64

# Built openssl/openssl-fips component is used when building FIPS-140 libraries.
# What we do here follows the OpenSSL FIPS-140 User Guide instructions.
FIPS_BUILD_DIR_32 = $(shell echo $(BUILD_DIR_32) | \
    sed -e 's/openssl-fips-140/openssl-fips/g' )
FIPS_BUILD_DIR_64 = $(shell echo $(BUILD_DIR_64) | \
    sed -e 's/openssl-fips-140/openssl-fips/g' )

# Ignore default CC_FOR_BUILD, CC, and CXX in CONFIGURE_ENV.
CONFIGURE_ENV += CC_FOR_BUILD=
CONFIGURE_ENV += CC=
CONFIGURE_ENV += CXX=

CONFIGURE_OPTIONS =  -DSOLARIS_OPENSSL -DNO_WINDOWS_BRAINDEATH
CONFIGURE_OPTIONS += --openssldir=/etc/openssl
CONFIGURE_OPTIONS += --prefix=/usr
# We use OpenSSL install code for installing only manual pages and we do that
# for 32-bit version only.
CONFIGURE_OPTIONS += --install_prefix=$(PROTO_DIR)
CONFIGURE_OPTIONS += no-rc3
CONFIGURE_OPTIONS += no-rc5
CONFIGURE_OPTIONS += no-md2
CONFIGURE_OPTIONS += no-mdc2
CONFIGURE_OPTIONS += no-idea
CONFIGURE_OPTIONS += no-hw_4758_cca
CONFIGURE_OPTIONS += no-hw_aep
CONFIGURE_OPTIONS += no-hw_atalla
CONFIGURE_OPTIONS += no-hw_chil
CONFIGURE_OPTIONS += no-hw_gmp
CONFIGURE_OPTIONS += no-hw_ncipher
CONFIGURE_OPTIONS += no-hw_nuron
CONFIGURE_OPTIONS += no-hw_padlock
CONFIGURE_OPTIONS += no-hw_sureware
CONFIGURE_OPTIONS += no-hw_ubsec
CONFIGURE_OPTIONS += no-hw_cswift
CONFIGURE_OPTIONS += threads
CONFIGURE_OPTIONS += shared
CONFIGURE_OPTIONS += fips --with-fipslibdir="$(FIPS_BUILD_DIR_$(BITS))/fips/"
CONFIGURE_OPTIONS += --with-fipsdir="$(BUILD_DIR_$(BITS))"
CONFIGURE_OPTIONS += no-seed

# Disable SSLv2 and SSLv3 protocols
CONFIGURE_OPTIONS += no-ssl2
CONFIGURE_OPTIONS += no-ssl3 no-ssl3-method

# We define our own compiler and linker option sets for Solaris. See Configure
# for more information.
CONFIGURE_OPTIONS32_i386 =	solaris-fips-x86-cc-sunw
CONFIGURE_OPTIONS32_sparc =	solaris-fips-sparcv9-cc-sunw
CONFIGURE_OPTIONS64_i386 =	solaris64-fips-x86_64-cc-sunw
CONFIGURE_OPTIONS64_sparc =	solaris64-fips-sparcv9-cc-sunw

# Some additional options needed for our engines.
CONFIGURE_OPTIONS += --pk11-libname=$(PKCS11_LIB$(BITS))
CONFIGURE_OPTIONS += --enginesdir=$(ENGINESDIR_$(BITS))
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS$(BITS)_$(MACH))

# OpenSSL has its own configure system which must be run from the fully
# populated source code directory. However, the Userland configuration phase is
# run from the build directory. The easiest way to workaround it is to copy all
# the source files there.
COMPONENT_PRE_CONFIGURE_ACTION = \
    ( $(CLONEY) $(SOURCE_DIR) $(BUILD_DIR)/$(MACH$(BITS)); )

# We deliver only one opensslconf.h file which must be suitable for both 32 and
# 64 bits. Depending on the configuration option, OpenSSL's Configure script
# creates opensslconf.h for either 32 or 64 bits. A patch makes the resulting
# header file usable on both architectures. The patch was generated against the
# opensslconf.h version from the 32 bit build.
COMPONENT_POST_CONFIGURE_ACTION = \
   ( [ $(BITS) -eq 32 ] && $(GPATCH) -p1 $(@D)/crypto/opensslconf.h \
      patches-post-config/opensslconf.patch; cd $(@D); $(MAKE) depend; )

# We must make sure that openssl-fips component is built before this openssl-fips-140
# component since in order to build FIPS-140 certified libraries, the canister
# is needed. Note that we must unset BITS that would override the same variable
# used in openssl-fips' Makefile, and we would end up up with both canisters
# built in 64 (or 32) bits.
$(COMPONENT_DIR)/../openssl-fips/build/$(MACH32)/.installed \
$(COMPONENT_DIR)/../openssl-fips/build/$(MACH64)/.installed:
	( unset BITS; \
	$(MAKE) -C $(COMPONENT_DIR)/../openssl-fips install; )

# download, clean, and clobber should all propogate to the fips bits
download clobber clean::
	(cd ../openssl-fips ; $(GMAKE) $@)

# We do not ship our engines as patches since it would be more difficult to
# update the files which have been under continuous development. We rather copy
# the files to the right directories and let OpenSSL makefiles build it.
# We also copy some FIPS specific header files needed to build FIPS version
# of OpenSSL from FIPS module.
COMPONENT_PRE_BUILD_ACTION = \
    ( $(LN) -fs $(COMPONENT_DIR)/../common/engines/pkcs11/*     $(@D)/engines; \
      $(MKDIR) $(@D)/bin; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/openssl-fips-$(IPS_COMPONENT_VERSION)/fips/fips.h $(@D)/include/openssl; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/openssl-fips-$(IPS_COMPONENT_VERSION)/fips/fipssyms.h $(@D)/include/openssl; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/openssl-fips-$(IPS_COMPONENT_VERSION)/fips/rand/fips_rand.h $(@D)/include/openssl; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/openssl-fips-$(IPS_COMPONENT_VERSION)/fips/fipsld $(@D)/bin/; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/build/$(MACH$(BITS))/fips/fips_standalone_sha1 $(@D)/bin/; \
      $(LN) -fs $(COMPONENT_DIR)/build/$(MACH$(BITS))/fips_premain_dso $(@D)/bin/;)

# OpenSSL does not install into <dir>/$(MACH64) for 64-bit install so no such
# directory is created and Userland install code would fail when installing lint
# libraries.
COMPONENT_PRE_INSTALL_ACTION = ( $(MKDIR) $(PROTO_DIR)/usr/lib/$(MACH64); )

# Remove unnecessary RUNPATH/RPATH for libcrypto.so.1.0.0
COMPONENT_POST_INSTALL_ACTION.32 = \
    $(ELFEDIT) -e "dyn:delete RUNPATH" -e "dyn:delete RPATH" \
        $(BUILD_DIR_32)/libcrypto.so.1.0.0;
COMPONENT_POST_INSTALL_ACTION.64 = \
    $(ELFEDIT) -e "dyn:delete RUNPATH" -e "dyn:delete RPATH" \
        $(BUILD_DIR_64)/libcrypto.so.1.0.0;
COMPONENT_POST_INSTALL_ACTION += $(COMPONENT_POST_INSTALL_ACTION.$(BITS))

$(SOURCE_DIR)/.prep: $(COMPONENT_DIR)/../openssl-fips/build/$(MACH32)/.installed \
		     $(COMPONENT_DIR)/../openssl-fips/build/$(MACH64)/.installed

configure:	$(CONFIGURE_32_and_64)

build:			$(BUILD_32_and_64)

# We follow what we do for install in openssl/openssl-1.0.0 component. Please
# see the comment in Makefile in there for more information.
install:	$(INSTALL_32_and_64)

# Set modified lint flags for our lint library targets.
$(BUILD_DIR_32)/llib-lcrypto.ln: LINT_FLAGS=$(LFLAGS_32) -I$(PROTOUSRINCDIR)
$(BUILD_DIR_32)/llib-lssl.ln: LINT_FLAGS=$(LFLAGS_32) -I$(PROTOUSRINCDIR)
$(BUILD_DIR_64)/llib-lcrypto.ln: LINT_FLAGS=$(LFLAGS_64) -I$(PROTOUSRINCDIR)
$(BUILD_DIR_64)/llib-lssl.ln: LINT_FLAGS=$(LFLAGS_64) -I$(PROTOUSRINCDIR)

# There are also separate STC test suites 'openssl' and 'openssl-engine'
# for regression testing. These internal tests are unit tests only.
COMPONENT_TEST_TARGETS = test
test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += developer/build/makedepend
REQUIRED_PACKAGES += network/rsync
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/linker
REQUIRED_PACKAGES += system/library/security/crypto
