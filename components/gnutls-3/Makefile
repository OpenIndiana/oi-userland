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
# Copyright (c) 2010, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnutls
COMPONENT_VERSION=	3.4.15
COMPONENT_PROJECT_URL=  ftp://ftp.gnutls.org/gcrypt/gnutls/v3.4
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:eb2a013905f5f2a0cbf7bcc1d20c85a50065063ee87bd33b496c4e19815e3498 
COMPONENT_ARCHIVE_URL=  ftp://ftp.gnutls.org/gcrypt/gnutls/v3.4/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/gnutls
COMPONENT_ANITYA_ID=	1221

TPNO=			32471

COMPONENT_BUILD_TARGETS = all info

# The GnuTLS API and ABI have incompatible changes between versions 2.8.6
# and 3.4.1; but the basic symlink name 'libgnutls.so' and pkg-config file
# name 'gnutls.pc' are unchanged.  As a result, it's not possible to have
# both versions installed at the same time in the default paths in a way
# that makes it possible to build programs that are only compatible with
# one version of the API.  As a result, GnuTLS version 3 delivered to a folder
# called gnutls-3 temporarily.  The plan is to integrate 3.4.1 and move all
# programs to 3.4.1; after all usage of 2.8.6  excised, move 3.4.1 to the
# default location.

# We need to build an extra static version of this library for
# GRUB/Wanboot support.

ifeq ($(MACH),i386)

WANBOOT_CONFIGURE = $(BUILD_DIR)/wanboot-amd64/.configured
WANBOOT_BUILD = $(BUILD_DIR)/wanboot-amd64/.built
WANBOOT_INSTALL = $(BUILD_DIR)/wanboot-amd64/.installed

CONFIGURE_32_and_64 += $(WANBOOT_CONFIGURE)
BUILD_32_and_64 += $(WANBOOT_BUILD)
INSTALL_32_and_64 += $(WANBOOT_INSTALL)

endif

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -I$(USRINCDIR)/gmp
CFLAGS += -I$(USRINCDIR)/idn

# Force libtool to pass this flag through using -Wc.
# https://www.gnu.org/software/libtool/manual/html_node/Stripped-link-flags.html
CXXFLAGS.studio += -Wc,$(studio_NORUNPATH)

MCS = mcs
STRIP = strip

# Set the wanboot CFLAGS as needed for the wanboot compilation

CFLAGS.wanboot += -D_BOOT
CFLAGS.wanboot += -g
CFLAGS.wanboot += -falign-jumps=1
CFLAGS.wanboot += -falign-loops=1
CFLAGS.wanboot += -falign-functions
CFLAGS.wanboot += -mno-mmx
CFLAGS.wanboot += -mno-sse
CFLAGS.wanboot += -mno-sse2
CFLAGS.wanboot += -mno-sse3
CFLAGS.wanboot += -mno-ssse3
CFLAGS.wanboot += -mno-sse4.1
CFLAGS.wanboot += -mno-sse4.2
CFLAGS.wanboot += -mno-sse4
CFLAGS.wanboot += -mno-avx
CFLAGS.wanboot += -mno-avx2
CFLAGS.wanboot += -mno-aes
CFLAGS.wanboot += -mno-pclmul
CFLAGS.wanboot += -mno-fsgsbase
CFLAGS.wanboot += -mno-rdrnd
CFLAGS.wanboot += -mno-f16c
CFLAGS.wanboot += -mno-fma
CFLAGS.wanboot += -mno-sse4a
CFLAGS.wanboot += -mno-fma4
CFLAGS.wanboot += -mno-xop
CFLAGS.wanboot += -mno-lwp
CFLAGS.wanboot += -mno-3dnow
CFLAGS.wanboot += -fno-dwarf2-cfi-asm
CFLAGS.wanboot += -fno-asynchronous-unwind-tables
CFLAGS.wanboot += -fno-common
CFLAGS.wanboot += -mcmodel=large
CFLAGS.wanboot += -mno-red-zone
CFLAGS.wanboot += -fno-stack-protector
CFLAGS.wanboot += -mno-stack-arg-probe

# Set the wanboot configure options as needed for wanboot

CONFIGURE_OPTIONS.wanboot += --enable-largefile
CONFIGURE_OPTIONS.wanboot += --disable-doc
CONFIGURE_OPTIONS.wanboot += --disable-tools
CONFIGURE_OPTIONS.wanboot += --disable-cxx
CONFIGURE_OPTIONS.wanboot += --disable-hardware-acceleration
CONFIGURE_OPTIONS.wanboot += --disable-padlock
CONFIGURE_OPTIONS.wanboot += --with-nettle-mini
CONFIGURE_OPTIONS.wanboot += --with-included-libtasn1
CONFIGURE_OPTIONS.wanboot += --disable-dtls-srtp-support
CONFIGURE_OPTIONS.wanboot += --disable-alpn-support
CONFIGURE_OPTIONS.wanboot += --disable-heartbeat_support
CONFIGURE_OPTIONS.wanboot += --disable-srp-authentication
CONFIGURE_OPTIONS.wanboot += --disable-psk-authentication
CONFIGURE_OPTIONS.wanboot += --enable-anon-authentication
CONFIGURE_OPTIONS.wanboot += --enable-dhe
CONFIGURE_OPTIONS.wanboot += --disable-openpgp-authentication
CONFIGURE_OPTIONS.wanboot += --disable-cryptodev
CONFIGURE_OPTIONS.wanboot += --disable-ocsp
CONFIGURE_OPTIONS.wanboot += --disable-session-tickets
CONFIGURE_OPTIONS.wanboot += --disable-openssl-compatibility
CONFIGURE_OPTIONS.wanboot += --disable-tests
CONFIGURE_OPTIONS.wanboot += --without-html-dir
CONFIGURE_OPTIONS.wanboot += --disable-gtk-doc
CONFIGURE_OPTIONS.wanboot += --disable-gtk-doc-html
CONFIGURE_OPTIONS.wanboot += --disable-gtk-doc-pdf
CONFIGURE_OPTIONS.wanboot += --disable-nls
CONFIGURE_OPTIONS.wanboot += --disable-rpath
CONFIGURE_OPTIONS.wanboot += --without-libiconv-prefix
CONFIGURE_OPTIONS.wanboot += --without-libintl-prefix
CONFIGURE_OPTIONS.wanboot += --without-librt-prefix
CONFIGURE_OPTIONS.wanboot += --without-libpthread-prefix
CONFIGURE_OPTIONS.wanboot += --without-libnsl-prefix
CONFIGURE_OPTIONS.wanboot += --disable-ld-version-script
CONFIGURE_OPTIONS.wanboot += --disable-valgrind-tests
CONFIGURE_OPTIONS.wanboot += --enable-static
CONFIGURE_OPTIONS.wanboot += --disable-shared
CONFIGURE_OPTIONS.wanboot += --without-pic
CONFIGURE_OPTIONS.wanboot += --disable-self-checks
CONFIGURE_OPTIONS.wanboot += --disable-fips140-mode
CONFIGURE_OPTIONS.wanboot += --without-idn
CONFIGURE_OPTIONS.wanboot += --disable-non-suiteb-curves
CONFIGURE_OPTIONS.wanboot += --disable-libdane
CONFIGURE_OPTIONS.wanboot += --without-unbound-root-key-file
CONFIGURE_OPTIONS.wanboot += --without-system-priority-file
CONFIGURE_OPTIONS.wanboot += --without-tpm
CONFIGURE_OPTIONS.wanboot += --disable-local-libopts
CONFIGURE_OPTIONS.wanboot += --disable-libopts-install
CONFIGURE_OPTIONS.wanboot += --without-regex_header
CONFIGURE_OPTIONS.wanboot += --without-libregex
CONFIGURE_OPTIONS.wanboot += --without-libregex_cflags
CONFIGURE_OPTIONS.wanboot += --without-libregex_libs
CONFIGURE_OPTIONS.wanboot += --disable-optional-args
CONFIGURE_OPTIONS.wanboot += --without-zlib
CONFIGURE_OPTIONS.wanboot += --without-default-trust-store-dir
CONFIGURE_OPTIONS.wanboot += --without-default-trust-store-file
CONFIGURE_OPTIONS.wanboot += --without-default-crl-file
CONFIGURE_OPTIONS.wanboot += --without-default-blacklist-file
CONFIGURE_OPTIONS.wanboot += --disable-guile
CONFIGURE_OPTIONS.wanboot += --without-guile-site-dir
CONFIGURE_OPTIONS.wanboot += --disable-crywrap

# For wanboot tell configure that we don't have lots of the
# standard unix environment.  This will cache these values, and set
# them to no.

CONFIGURE_OPTIONS.wanboot += ac_cv_func___fsetlocking=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func___register_atfork=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func___secure_getenv=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func__fseeki64=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func__ftelli64=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func__ftime=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_alarm=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_argpusage=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_canonicalize_file_name=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_chmod=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_clock_gettime=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_clock_settime=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_daemon=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_dup2=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_epoll_create=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_fchmod=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_flockfile=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_fork=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_fstat=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_ftello=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_funlockfile=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_getdelim=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_gethostbyname=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_getline=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_getpagesize=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_getpass=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_getpid=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_getpwuid_r=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_getrusage=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_getservbyname=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_iconv=no
CONFIGURE_OPTIONS.wanboot += am_cv_func_iconv=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_inet_ntop=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_inet_pton=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_issetugid=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_kqueue=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_localtime=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_localtime_r=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_mbrtowc=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_memmem=no
CONFIGURE_OPTIONS.wanboot += gl_cv_func_memmem_works_always=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_mmap=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_mprotect=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_munmap=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_nanosleep=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_pthread_atfork=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_pthread_mutex_lock=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_putenv=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_regcomp=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_scandir=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_scm_gc_malloc_pointerless=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_secure_getenv=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_select=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_setdtablesize=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_setenv=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_shutdown=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_socket=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_strerror_r=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_strpbrk=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_strsignal=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_strtok_r=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_strverscmp=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_tcgetattr=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_tcsetattr=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_tsearch=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_uname=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_unsetenv=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_vasprintf=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_vfork=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_wcslen=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_wcsnlen=no
CONFIGURE_OPTIONS.wanboot += ac_cv_func_wctomb=no
CONFIGURE_OPTIONS.wanboot += ac_cv_libiconv=no
CONFIGURE_OPTIONS.wanboot += ac_cv_libnsl=no
CONFIGURE_OPTIONS.wanboot += ac_cv_libpthread=no
CONFIGURE_OPTIONS.wanboot += ac_cv_librt=no

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --mandir=$(USRSHAREDIR)/$(COMPONENT_NAME)-3/man
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.32 += --libdir=$(USRLIBDIR)/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.64 += --libdir=$(USRLIBDIR64)/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.32 += --libexecdir=$(USRLIBDIR)/pkgconfig/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.64 += --libexecdir=$(USRLIBDIR64)/pkgconfig/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS += --localedir=$(USRSHARELOCALEDIR)/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --disable-guile
CONFIGURE_OPTIONS += --with-included-libtasn1
CONFIGURE_OPTIONS += --without-p11-kit
CONFIGURE_OPTIONS += --disable-ecdhe
CONFIGURE_OPTIONS += --disable-openssl-compatibility
CONFIGURE_OPTIONS += --disable-tests

include ../../make-rules/shared-targets.mk

$(BUILD_DIR)/wanboot-amd64/.configured: BITS=64
$(BUILD_DIR)/wanboot-amd64/.configured: COMPILER=gcc
$(BUILD_DIR)/wanboot-amd64/.configured: CFLAGS += $(CFLAGS.wanboot)
$(BUILD_DIR)/wanboot-amd64/.configured: \
	CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.wanboot)

$(BUILD_DIR)/wanboot-amd64/.installed: \
	COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRLIBDIR)/grub/wanboot;
$(BUILD_DIR)/wanboot-amd64/.installed: \
	COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRLIBDIR64)/$(COMPONENT_NAME)-3/libgnutls.a \
	$(PROTOUSRLIBDIR)/grub/wanboot/libgnutls.a;
$(BUILD_DIR)/wanboot-amd64/.installed: \
	COMPONENT_POST_INSTALL_ACTION += \
	$(STRIP) -x  $(PROTOUSRLIBDIR)/grub/wanboot/libgnutls.a;
$(BUILD_DIR)/wanboot-amd64/.installed: \
	COMPONENT_POST_INSTALL_ACTION += \
	$(MCS) -d $(PROTOUSRLIBDIR)/grub/wanboot/libgnutls.a;
$(BUILD_DIR)/wanboot-amd64/.installed: \
	COMPONENT_POST_INSTALL_ACTION += \
	$(AR) ts $(PROTOUSRLIBDIR)/grub/wanboot/libgnutls.a;

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/ERROR/p" '

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/security/nettle
REQUIRED_PACKAGES += library/security/trousers
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/c++-runtime
