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
# Copyright 2024 Marcel Telka
#

BUILD_BITS = 64_and_32
USE_PARALLEL_BUILD = yes
DROP_STATIC_LIBRARIES = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			openssl
COMPONENT_VERSION=		3.4.1
COMPONENT_SUMMARY=		OpenSSL software library is a robust, commercial-grade, full-featured toolkit for general-purpose cryptography and secure communication
COMPONENT_PROJECT_URL=		https://openssl-library.org/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=		https://github.com/openssl/openssl/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:002a2d6b30b58bf4bea46c43bdd96365aaf8daa6c428782aa4feee06da197df3
COMPONENT_FMRI=			library/security/openssl-$(OPENSSL_VERSION)
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_LICENSE=		Apache-2.0
COMPONENT_LICENSE_FILE=		LICENSE.txt

COMPONENT_FMRI.$(COMPONENT_NAME)-32=	$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.$(COMPONENT_NAME)-32=	$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/common.mk

# API/ABI incompatible changes are introduced with MAJOR version number change.
# See also https://openssl-library.org/policies/releasestrat/index.html
OPENSSL_VERSION = $(firstword $(subst ., ,$(COMPONENT_VERSION)))

# Make sure our preferred Perl and pod2man is used
PATH.prepend += $(PERL5BINDIR)

# OpenSSL uses Configure incompatible with autoconf
CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure
CONFIGURE_OPTIONS =
CONFIG_SHELL =

# Installation directories
CONFIGURE_OPTIONS += --openssldir=$(OPENSSL_ETCDIR)
CONFIGURE_OPTIONS += --prefix=$(OPENSSL_PREFIX)

# Define compiler and linker option sets.
# See Configurations/10-main.conf for more information.
CONFIGURE_OPTIONS32_i386 =	solaris-x86-gcc
CONFIGURE_OPTIONS32_sparc =	solaris-sparcv9-gcc
CONFIGURE_OPTIONS64_i386 =	solaris64-x86_64-gcc
CONFIGURE_OPTIONS64_sparc =	solaris64-sparcv9-gcc
CONFIGURE_OPTIONS +=		$(CONFIGURE_OPTIONS$(BITS)_$(MACH))

# Use non-default man pages suffix
COMPONENT_INSTALL_ARGS += MANSUFFIX=openssl

# We do not need to install overlapping docs, /etc, and other common files for
# 32-bit build.  We will use such files as produced by the 64-bit build.  See
# the toplevel Makefile in the build dir for more information.
#
# List of skipped targets:
# install_ssldirs	- $(OPENSSL_ETCDIR)
# install_docs		- man pages and html docs
# install_runtime	- runtime (in bin)
$(BUILD_DIR_32)/.installed: COMPONENT_INSTALL_TARGETS = install_dev install_engines install_modules

# Save includes installed during the 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += \
	$(MV) $(PROTO_DIR)/$(OPENSSL_INCDIR) $(PROTO_DIR)/$(OPENSSL_INCDIR)-32 ;

# Merge includes for 32-bit and 64-bit.  When a file differs create a wrapper.
COMPONENT_POST_INSTALL_ACTION.64 += \
	( cd $(PROTO_DIR)/$(OPENSSL_INCDIR)/.. ; \
	nd=$(notdir $(OPENSSL_INCDIR)) ; \
	for f in $$($(ENV) $(GDIFF) -qr $$nd-32 $$nd \
	    | $(GSED) -n -e 's|^Files .* '"$$nd"'/\([^ ]\{1,\}\) differ$$|\1|p') ; do \
		f32=$$f-32 ; f64=$$f-64 ; \
		[ "$${f\#\#*.}" != "$$f" ] \
			&& f32=$${f%.*}-32.$${f\#\#*.} && f64=$${f%.*}-64.$${f\#\#*.} ; \
		[ -e "$$nd/$$f32" ] && exit 1 ; \
		[ -e "$$nd/$$f64" ] && exit 1 ; \
		$(MV) $$nd/$$f $$nd/$$f64 ; \
		$(MV) $$nd-32/$$f $$nd/$$f32 ; \
		printf '\#if defined (__amd64)\n\#include <%s>\n\#else\n\#include <%s>\n\#endif\n' \
		    "$$f64" "$$f32" > $$nd/$$f ; \
	done ) ; \
	$(RM) -r $(PROTO_DIR)/$(OPENSSL_INCDIR)-32 ;

# Provide usable openssl.cnf
COMPONENT_POST_INSTALL_ACTION.64 += $(GSED) -i \
	-e 's|\(^dir.*=.*\)\./demoCA\(.*Where everything is kept.*\)$$|\1$(OPENSSL_ETCDIR)\2|' \
	-e 's/^crlnumber/\#&/' \
	-e 's/^countryName_default/\#&/' \
	-e 's/^stateOrProvinceName_default/\#&/' \
	-e 's/^0\.organizationName_default/\#&/' \
	$(PROTO_DIR)/$(OPENSSL_ETCDIR)/openssl.cnf ;

# Move programs to the bin directory so they are directly available
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(MV) $(PROTO_DIR)/$(OPENSSL_ETCDIR)/misc/* $(PROTO_DIR)/$(OPENSSL_BINDIR) ;

# Create various symlinks at standard locations
COMPONENT_POST_INSTALL_ACTION += $(call create-symlinks,$(OPENSSL_LIBDIR)/*.so*,$(USRLIBDIR.$(BITS))) ;
COMPONENT_POST_INSTALL_ACTION += $(call create-symlinks,$(OPENSSL_PKG_CONFIG_PATH)/*,$(PKG_CONFIG_PATH.$(BITS))) ;
COMPONENT_POST_INSTALL_ACTION += $(call create-symlinks,$(OPENSSL_LIBDIR)/cmake/*,$(USRLIBDIR.$(BITS))/cmake) ;
COMPONENT_POST_INSTALL_ACTION.64 += $(call create-symlinks,$(OPENSSL_BINDIR)/*,$(USRBINDIR)) ;
COMPONENT_POST_INSTALL_ACTION.64 += $(call create-symlinks,$(OPENSSL_INCDIR)/*,$(USRINCDIR)) ;
COMPONENT_POST_INSTALL_ACTION.64 += $(SYMLINK) $(OPENSSL_VERSION) $(PROTOETCDIR)/openssl/default ;

# Compatibility symlink for 64 bit libraries
COMPONENT_POST_INSTALL_ACTION.64 += $(SYMLINK) $(MACH64) $(PROTO_DIR)/$(OPENSSL_LIBDIR)/../64 ;

# Convert the (empty) certs directory to a symlink
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(MV) $(PROTO_DIR)/$(OPENSSL_ETCDIR)/certs $(PROTO_DIR)/$(OPENSSL_ETCDIR)/.. ; \
	$(SYMLINK) ../certs $(PROTO_DIR)/$(OPENSSL_ETCDIR)/certs ;

# Fix shebang for Perl scripts
COMPONENT_POST_INSTALL_ACTION.64 += \
	for f in $(PROTO_DIR)/$(OPENSSL_BINDIR)/* ; do \
		[ -L $$f ] && continue ; \
		[ -f $$f ] || continue ; \
		$(GSED) -i -e '1s|^\(\#!/usr/bin/\)env \(perl\)$$|\1\2|' $$f ; \
	done ;

# See test/README.md
COMPONENT_TEST_TARGETS = test

# Test transforms
COMPONENT_TEST_TRANSFORMS += '-e "0,/run_tests\.pl/d"'		# delete any lines up through run_tests.pl
COMPONENT_TEST_TRANSFORMS += '-e "s/,  *[0-9]* wallclock.*//"'	# delete timings
COMPONENT_TEST_TRANSFORMS += '-e "/^make\[/d"'			# delete make logs

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
