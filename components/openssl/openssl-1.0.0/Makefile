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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

# COMPONENT_NAME, COMPONENT_VERSION, IPS_COMPONENT_VERSION and some other
# related macros definitions were moved to ../openssl-1.0.0/Makefile.version
# in order to keep OpenSSL versions in ../openssl-1.0.0 and
# ../openssl-1.0.0-wanboot in sync
include Makefile.version

# Architecture-specific patches
EXTRA_PATCHES.i386 = $(PATCH_DIR)/openssl-1.0.0d-aesni-v4.i386-patch
EXTRA_PATCHES.sparc = $(PATCH_DIR)/openssl-1.0.0d-t4-engine.sparc-patch
EXTRA_PATCHES = $(EXTRA_PATCHES.$(MACH))

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/lint-libraries.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin:/usr/perl5/bin

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

CONFIGURE_OPTIONS =  -DSOLARIS_OPENSSL -DNO_WINDOWS_BRAINDEATH
CONFIGURE_OPTIONS += --openssldir=/etc/openssl
CONFIGURE_OPTIONS += --prefix=/usr
# We use OpenSSL install code for installing only manual pages and we do that
# for 32-bit version only.
CONFIGURE_OPTIONS += --install_prefix=$(PROTO_DIR)
CONFIGURE_OPTIONS += no-ec
CONFIGURE_OPTIONS += no-ecdh
CONFIGURE_OPTIONS += no-ecdsa
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
# MD2 is not enabled by default in OpensSSL but some software we have in
# Userland needs it. One example is nmap.
CONFIGURE_OPTIONS += enable-md2
CONFIGURE_OPTIONS += no-seed
# We use both no-whirlpool and no-whrlpool since there is an inconsistency in
# the OpenSSL code and one needs both to build OpenSSL successfully with
# Whirlpool implementation removed.
CONFIGURE_OPTIONS += no-whirlpool
CONFIGURE_OPTIONS += no-whrlpool

# We define our own compiler and linker option sets for Solaris. See Configure
# for more information.
CONFIGURE_OPTIONS32_i386 =	solaris-x86-cc-sunw
CONFIGURE_OPTIONS32_sparc =	solaris-sparcv9-cc-sunw
CONFIGURE_OPTIONS64_i386 =	solaris64-x86_64-cc-sunw
CONFIGURE_OPTIONS64_sparc =	solaris64-sparcv9-cc-sunw

# Some additional options needed for our engines.
CONFIGURE_OPTIONS += --pk11-libname=$(PKCS11_LIB$(BITS))
CONFIGURE_OPTIONS += --enginesdir=$(ENGINESDIR_$(BITS))
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS$(BITS)_$(MACH))

# OpenSSL has its own configure system which must be run from the fully
# populated source code directory. However, the Userland configuration phase is
# run from the build directory. So, we must get the full source code into the
# build directory.
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

# This conditional part triggers actions in ../openssl-1.0.0-wanboot directory
# in order to create static openssl bits for linking with wanboot.
# Specifically
#     - propagate clean and clobber targets to wanboot dir
#     - build wanboot bits and copy in wanboot-openssl.o to proto area
#     - cache (link) openssl tarball from wanboot dir
ifeq ($(MACH), sparc)
WANBOOT_DIR	= $(COMPONENT_DIR)/../openssl-1.0.0-wanboot
WANBOOT_TO	= $(PROTO_DIR)/lib/openssl/wanboot/$(MACH64)
clobber clean::
	(cd $(WANBOOT_DIR) ; $(GMAKE) $@)

# In order not to download the tarball twice (once here and once in 
# ../openssl-1.0.0-wanboot), there is a hacky caching applied.
# After having build in ../openssl-1.0.0-wanboot an attempt is made to create
# a soft-link in this directory pointing to the tarball. 
$(WANBOOT_DIR)/build/$(MACH64)/.built:
	(cd $(WANBOOT_DIR) ; $(GMAKE) build;)
	-$(LN) -s $(WANBOOT_DIR)/$(COMPONENT_ARCHIVE) $(COMPONENT_DIR)/ 

build: $(WANBOOT_DIR)/build/$(MACH64)/.built
install: $(WANBOOT_DIR)/build/$(MACH64)/.built

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION = \
    ( $(MKDIR) -p $(WANBOOT_TO); \
      $(CP) $(WANBOOT_DIR)/build/$(MACH64)/wanboot-openssl.o $(WANBOOT_TO); )
endif


# We do not ship our engines as patches since it would be more difficult to
# update the files which have been under continuous development. We rather copy
# the files to the right directories.
COMPONENT_PRE_BUILD_ACTION = \
    ( $(CP) -fp engines/aesni/eng_aesni.c	$(@D)/crypto/engine; \
      $(CP) -fp engines/aesni/aesni-x86*.pl	$(@D)/crypto/aes/asm; \
      $(CP) -fp engines/devcrypto/*.[ch]	$(@D)/engines; \
      $(CP) -fp engines/pkcs11/*.[ch]		$(@D)/crypto/engine; \
      $(CP) -fp engines/t4/eng_t4*.[ch]		$(@D)/crypto/engine; \
      $(CP) -fp engines/t4/t4_aes.S		$(@D)/crypto/aes/asm; \
      $(CP) -fp engines/t4/t4_des.S		$(@D)/crypto/des/asm; \
      $(CP) -fp engines/t4/t4_md5.S		$(@D)/crypto/md5/asm; \
      $(CP) -fp engines/t4/t4_sha?.S		$(@D)/crypto/sha/asm; )

build:		$(BUILD_32_and_64)

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

# We could run OpenSSL install code for 32 bits only to process header files and
# manual pages. However, link libraries depend on install stamps so we run
# install for 64 bit as well. Note that we must take built binary files from
# build directories, not from the proto area which contains whatever was
# installed first.
install:	$(INSTALL_32_and_64)

# We need to modify the default lint flags to include patched opensslconf.h from
# the build directory. If we do not do that, lint will complain about md2.h
# which is not enabled by default but it is in our opensslconf.h.
LFLAGS_32 := -I$(BUILD_DIR_32)/include $(LINT_FLAGS) -lsoftcrypto
LFLAGS_64 := -I$(BUILD_DIR_64)/include $(LINT_FLAGS) -lsoftcrypto

# Set modified lint flags for our lint library targets.
$(BUILD_DIR_32)/llib-lcrypto.ln: LINT_FLAGS="$(LFLAGS_32)"
$(BUILD_DIR_32)/llib-lssl.ln: LINT_FLAGS="$(LFLAGS_32)"
$(BUILD_DIR_64)/llib-lcrypto.ln: LINT_FLAGS="$(LFLAGS_64)"
$(BUILD_DIR_64)/llib-lssl.ln: LINT_FLAGS="$(LFLAGS_64)"

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
