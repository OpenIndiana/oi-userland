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
# Copyright 2017 Gary Mills
# Copyright 2020 Michal Nowak
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 32_and_64
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME =	openssl
# When new version of OpenSSL comes in, you must update both COMPONENT_VERSION
# and HUMAN_VERSION.
COMPONENT_VERSION =	1.0.2.21
HUMAN_VERSION = 1.0.2u
COMPONENT_REVISION=	14
COMPONENT_FMRI =	library/security/openssl
COMPONENT_SUMMARY =	OpenSSL - a Toolkit for Secure Sockets Layer (SSL v2/v3) and Transport Layer (TLS v1) protocols and general purpose cryptographic library
COMPONENT_CLASSIFICATION = System/Security
COMPONENT_PROJECT_URL=	https://www.openssl.org
COMPONENT_SRC =		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ecd0c6ffb493dd06707d38b14bb4d8c2288bb7033735606569d8f90f89669d16
COMPONENT_ARCHIVE_URL =	$(COMPONENT_PROJECT_URL)/source/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =	OpenSSL, SSLeay
COMPONENT_LICENSE_FILE = openssl-1.0.2.license

include $(WS_MAKE_RULES)/common.mk

PATH= $(GCC_ROOT)/bin:$(PATH.illumos)

# OpenSSL does not use autoconf but its own configure system.
CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure

# This is to force OpenSSL's Configure script to use gmake for 'make links'. 
# Otherwise it fails with:
#     mksh: Fatal error in reader: Unmatched `(' on line
CONFIGURE_ENV += MAKE="$(GMAKE)"

# Used in the configure options below.
PKCS11_LIB32 = /usr/lib/libpkcs11.so.1
PKCS11_LIB64 = /usr/lib/64/libpkcs11.so.1
ENGINESDIR_32 = /lib/openssl/engines
ENGINESDIR_64 = /lib/openssl/engines/64

# Configure options common to OpenSSL
CONFIGURE_OPTIONS =  -DSOLARIS_OPENSSL -DNO_WINDOWS_BRAINDEATH
CONFIGURE_OPTIONS += --openssldir=/etc/openssl
CONFIGURE_OPTIONS += --prefix=/usr/openssl/1.0
CONFIGURE_OPTIONS += --libdir=lib/$(ARCHLIBSUBDIR)
# We use OpenSSL install code for installing only manual pages and headers.
CONFIGURE_OPTIONS += --install_prefix=$(PROTO_DIR)
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

# MD2 is not enabled by default in OpensSSL but some software we have in
# Userland needs it. One example is nmap.
CONFIGURE_OPTIONS += enable-md2
CONFIGURE_OPTIONS += no-seed

# Now we have to enable it explicitly
CONFIGURE_OPTIONS += enable-ssl2

# We use both no-whirlpool and no-whrlpool since there is an inconsistency in
# the OpenSSL code and one needs both to build OpenSSL successfully with
# Whirlpool implementation removed.
CONFIGURE_OPTIONS += no-whirlpool
CONFIGURE_OPTIONS += no-whrlpool

# Some additional options needed for our engines.
CONFIGURE_OPTIONS += --pk11-libname=$(PKCS11_LIB$(BITS))
CONFIGURE_OPTIONS += --enginesdir=$(ENGINESDIR_$(BITS))

# We define our own compiler and linker option sets for Solaris. See Configure
# for more information.
CONFIGURE_OPTIONS32_i386 =	solaris-x86-gcc-sunw
CONFIGURE_OPTIONS32_sparc =	solaris-sparcv9-gcc-sunw
CONFIGURE_OPTIONS64_i386 =	solaris64-x86_64-gcc-sunw
CONFIGURE_OPTIONS64_sparc =	solaris64-sparcv9-gcc-sunw

# Options specific to regular build.
# They must not be specified as common, as they cannot be overridden.
$(BUILD_DIR)/$(MACH32)/.configured:	CONFIGURE_OPTIONS += threads
$(BUILD_DIR)/$(MACH64)/.configured:	CONFIGURE_OPTIONS += threads
$(BUILD_DIR)/$(MACH32)/.configured:	CONFIGURE_OPTIONS += shared
$(BUILD_DIR)/$(MACH64)/.configured:	CONFIGURE_OPTIONS += shared
$(BUILD_DIR)/$(MACH32)/.configured:	CONFIGURE_OPTIONS += shared
$(BUILD_DIR)/$(MACH64)/.configured:	CONFIGURE_OPTIONS += shared
$(BUILD_DIR)/$(MACH32)/.configured:	CONFIGURE_OPTIONS += \
	$(CONFIGURE_OPTIONS32_$(MACH))
$(BUILD_DIR)/$(MACH64)/.configured:	CONFIGURE_OPTIONS += \
	$(CONFIGURE_OPTIONS64_$(MACH))

# OpenSSL has its own configure system which must be run from the fully
# populated source code directory. However, the Userland configuration phase is
# run from the build directory. So, we must get the full source code into the
# build directory.

# We do not ship our engines as patches since it would be more difficult to
# update the files which have been under continuous development. We rather copy
# the files to the right directories.
COMPONENT_PRE_CONFIGURE_ACTION = \
    ( $(CLONEY) $(SOURCE_DIR) $(BUILD_DIR)/$(MACH$(BITS)); \
      echo "Cloning engines..."; \
      $(LN) -fs $(COMPONENT_DIR)/engines/pkcs11/*.[ch]		$(@D)/engines; )

# We deliver only one opensslconf.h file which must be suitable for both 32 and
# 64 bits. Depending on the configuration option, OpenSSL's Configure script
# creates opensslconf.h for either 32 or 64 bits. A patch makes the resulting
# header file usable on both architectures. The patch was generated against the
# opensslconf.h version from the 32 bit build.
COMPONENT_POST_CONFIGURE_ACTION = \
    ( [ $(BITS) -eq 32 ] && $(GPATCH) -p1 $(@D)/crypto/opensslconf.h \
      patches-post-config/opensslconf.patch; cd $(@D); $(MAKE) depend; )

COMPONENT_BUILD_TARGETS= depend all

# Build openssl-0.9.8 if not yet built.
$(COMPONENT_DIR)/../openssl-0.9.8/build/$(MACH32)/.built \
$(COMPONENT_DIR)/../openssl-0.9.8/build/$(MACH64)/.built:
	$(GMAKE) -C $(COMPONENT_DIR)/../openssl-0.9.8 build

$(PROTO_DIR)/.openssl-0.9.8:	$(COMPONENT_DIR)/../openssl-0.9.8/build/$(MACH32)/.built \
				$(COMPONENT_DIR)/../openssl-0.9.8/build/$(MACH64)/.built
	$(MKDIR) $(PROTO_DIR)/lib/$(MACH64)
	$(CP) -a $(COMPONENT_DIR)/../openssl-0.9.8/build/$(MACH32)/libssl.so.0.9.8 $(PROTO_DIR)/lib
	$(CP) -a $(COMPONENT_DIR)/../openssl-0.9.8/build/$(MACH32)/libcrypto.so.0.9.8 $(PROTO_DIR)/lib
	$(CP) -a $(COMPONENT_DIR)/../openssl-0.9.8/build/$(MACH64)/libssl.so.0.9.8 $(PROTO_DIR)/lib/$(MACH64)
	$(CP) -a $(COMPONENT_DIR)/../openssl-0.9.8/build/$(MACH64)/libcrypto.so.0.9.8 $(PROTO_DIR)/lib/$(MACH64)
	$(TOUCH) $@

# OpenSSL uses sections man[1357] by default so we must create the man
# directories we use for OpenSSL man pages in Solaris. Note that we patch the
# OpenSSL man page install script to use the correct directories.
MANDIR_SECTIONS =  $(PROTO_DIR)/usr/share/man/man1openssl
MANDIR_SECTIONS += $(PROTO_DIR)/usr/share/man/man3openssl
MANDIR_SECTIONS += $(PROTO_DIR)/usr/share/man/man5openssl
MANDIR_SECTIONS += $(PROTO_DIR)/usr/share/man/man7openssl

# We must create man page directories manually since we patched OpenSSL install
# code to install into manXopenssl instead of manX. Also, OpenSSL does not
# install into <dir>/$(MACH64) for 64-bit install so no such directory is
# created and Userland install code would fail when installing lint libraries.
COMPONENT_PRE_INSTALL_ACTION = ( $(MKDIR) $(MANDIR_SECTIONS); \
    $(MKDIR) $(PROTO_DIR)/usr/lib/$(MACH64); )

# The install_docs target will install man pages into $(PROTO_DIR)/$(MANDIR). We
# also add /usr/perl5/bin to PATH so that OpenSSL install code can locate the
# system pod2man. If not set, OpenSSL make would use an internal implementation
# from the tarball which would corrupt some man pages.
COMPONENT_INSTALL_ARGS += PATH=$(PATH) MANDIR=/usr/share/man

# Note that we take built binary files from
# build directories, not from the proto area which contains whatever was
# installed first.
install:	$(INSTALL_32_and_64) $(PROTO_DIR)/.openssl-0.9.8

# There are also separate STC test suites 'openssl' and 'openssl-engine'
# for regression testing. These internal tests are unit tests only.
COMPONENT_TEST_TARGETS = test

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += developer/build/makedepend
# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
