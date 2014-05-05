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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#
export PARFAIT_BUILD=no

include ../../../make-rules/shared-macros.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin:/usr/perl5/bin

COMPONENT_NAME =	openssl-fips-140
# Note that this is the OpenSSL version that is used to build FIPS-140 certified
# libraries. However, we use the FIPS canister version for the IPS package.
COMPONENT_VERSION =	1.0.1g
IPS_COMPONENT_VERSION = 2.0.6
COMPONENT_PROJECT_URL=	http://www.openssl.org/
COMPONENT_SRC_NAME =	openssl
COMPONENT_SRC =		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:53cb818c3b90e507a8348f4f5eaedb05d8bfe5358aabb508b7263cc670c3e028
COMPONENT_ARCHIVE_URL =	$(COMPONENT_PROJECT_URL)source/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/openssl

# OpenSSL FIPS 2.0.5 directory
OPENSSL_FIPS_DIR = $(COMPONENT_DIR)/../openssl-fips

# Note that the SPARC patch above does not fit this pattern. That is intentional
# and a reason why we can add it to the EXTRA_PATCHES variable so that we use it
# only on SPARC.
PATCH_PATTERN = [0-9][0-9]*.patch

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/lint-libraries.mk

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
    sed -e 's/openssl-1.0.1-fips-140/openssl-fips/g' )
FIPS_BUILD_DIR_64 = $(shell echo $(BUILD_DIR_64) | \
    sed -e 's/openssl-1.0.1-fips-140/openssl-fips/g' )

CONFIGURE_OPTIONS =  -DSOLARIS_OPENSSL -DNO_WINDOWS_BRAINDEATH
CONFIGURE_OPTIONS += --openssldir=/etc/openssl
CONFIGURE_OPTIONS += --prefix=/usr
# We use OpenSSL install code for installing only manual pages and we do that
# for 32-bit version only.
CONFIGURE_OPTIONS += --install_prefix=$(PROTO_DIR)
CONFIGURE_OPTIONS += no-ec2m
CONFIGURE_OPTIONS += no-rc3
CONFIGURE_OPTIONS += no-rc5
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

# MD2 is not enabled by default in OpensSSL but some software we have in
# Userland needs it. One example is nmap.
CONFIGURE_OPTIONS += enable-md2
CONFIGURE_OPTIONS += no-seed

# We define our own compiler and linker option sets for Solaris. See Configure
# for more information.
CONFIGURE_OPTIONS32_i386 =	solaris-x86-cc-sunw
CONFIGURE_OPTIONS32_sparc =	solaris-sparcv8-cc-sunw
CONFIGURE_OPTIONS64_i386 =	solaris64-x86_64-cc-sunw
CONFIGURE_OPTIONS64_sparc =	solaris64-sparcv9-cc-sunw

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

# Enable ASLR for this component
ASLR_MODE =	$(ASLR_ENABLE)

# We must make sure that openssl-fips component is built before this 1.0.1
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
# of OpenSSL from FIPS module (openssl-fips-ecp-2.0.5).
COMPONENT_PRE_BUILD_ACTION = \
    ( $(LN) -fs $(COMPONENT_DIR)/engines/pkcs11/*     $(@D)/engines; \
      $(MKDIR) $(@D)/bin; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/openssl-fips-ecp-2.0.5/fips/fips.h $(@D)/include/openssl; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/openssl-fips-ecp-2.0.5/fips/fipssyms.h $(@D)/include/openssl; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/openssl-fips-ecp-2.0.5/fips/rand/fips_rand.h $(@D)/include/openssl; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/openssl-fips-ecp-2.0.5/fips/fipsld $(@D)/bin/; \
      $(LN) -fs $(OPENSSL_FIPS_DIR)/build/$(MACH$(BITS))/fips/fips_standalone_sha1 $(@D)/bin/; \
      $(LN) -fs $(COMPONENT_DIR)/build/$(MACH$(BITS))/fips_premain_dso $(@D)/bin/;)

# OpenSSL does not install into <dir>/$(MACH64) for 64-bit install so no such
# directory is created and Userland install code would fail when installing lint
# libraries.
COMPONENT_PRE_INSTALL_ACTION = ( $(MKDIR) $(PROTO_DIR)/usr/lib/$(MACH64); )

$(SOURCE_DIR)/.prep: $(COMPONENT_DIR)/../openssl-fips/build/$(MACH32)/.installed \
		     $(COMPONENT_DIR)/../openssl-fips/build/$(MACH64)/.installed

build:			$(BUILD_32_and_64)

# We follow what we do for install in openssl/openssl-1.0.0 component. Please
# see the comment in Makefile in there for more information.
install:	$(INSTALL_32_and_64)

# We need to modify the default lint flags to include patched opensslconf.h from
# the build directory. If we do not do that, lint will complain about md2.h
# which is not enabled by default but it is in our opensslconf.h.
LFLAGS_32 := -I$(BUILD_DIR_32)/include $(LINT_FLAGS)
LFLAGS_64 := -I$(BUILD_DIR_64)/include $(LINT_FLAGS)

# Set modified lint flags for our lint library targets.
$(BUILD_DIR_32)/llib-lcrypto.ln: LINT_FLAGS=$(LFLAGS_32)
$(BUILD_DIR_32)/llib-lssl.ln: LINT_FLAGS=$(LFLAGS_32)
$(BUILD_DIR_64)/llib-lcrypto.ln: LINT_FLAGS=$(LFLAGS_64)
$(BUILD_DIR_64)/llib-lssl.ln: LINT_FLAGS=$(LFLAGS_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
