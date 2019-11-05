#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016, Jim Klimov. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		clamav
### For X.Y.0 versions the TGZ and DIR do not include trailing .0 piece
### But our IPS version should better have same number of components.
### So the COMPONENT_VERSION may be 0.99 or 0.99.1 (as in original),
### but the IPS_COMPONENT_VERSION is forced to 3-part 0.99.0 or 0.99.1.
COMPONENT_VERSION=	0.99.3
ifeq ($(words $(subst ., ,$(COMPONENT_VERSION))),2)
 IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).0
else
 IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION)
endif
### Library files are tagged with unique per-version numbers
COMPONENT_VERSION_LIB_MAJOR=	7
COMPONENT_VERSION_LIB_FULL=	$(COMPONENT_VERSION_LIB_MAJOR).1.1
COMPONENT_SUMMARY=	ClamAV $(IPS_COMPONENT_VERSION) opensource antivirus toolkit
COMPONENT_FMRI= 	antivirus/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:00fa5292a6e00a3a4035b826267748965d5d2c4943d8ff417d740238263e8e84
COMPONENT_PROJECT_URL=	http://www.clamav.net/
COMPONENT_ARCHIVE_URL=	\
	http://www.clamav.net/downloads/production/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2
# We need to use non-default User-Agent for the fetch, otherwise we are denied
# to download the source file.
COMPONENT_FETCH_USER_AGENT=	fetch

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_OPTIONS +=	-D COMPONENT_VERSION_LIB_MAJOR="$(COMPONENT_VERSION_LIB_MAJOR)"
PKG_OPTIONS +=	-D COMPONENT_VERSION_LIB_FULL="$(COMPONENT_VERSION_LIB_FULL)"

# Note: This is done just in case, because according to
# https://github.com/vrtadmin/clamav-devel/issues/45 currently
#   ClamAV doesn't support scanning files larger than 2.7GB due
#   to constraints in the scanning engine.
# Still, this can help with not dying on e.g. huge log files :-)
CFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_LARGEFILES)

CFLAGS   += -std=gnu89  $(CPP_XPG5MODE)

# Make sure that *-config scripts are taken from proper MACH$(BITS) dir
PATH.64=$(GNUBIN)/$(MACH64):$(USRBINDIR64):$(GNUBIN):$(USRBINDIR)
PATH.32=$(GNUBIN):$(USRBINDIR)
PATH=$(PATH.$(BITS))

COMPONENT_PREP_ACTION = \
    (cd $(@D) &&\
        aclocal -I . &&\
        autoheader &&\
        automake -a -f -c --gnu &&\
        autoconf &&\
        $(RM) config.h )

# Missing files in build dir for configure without this
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin
CONFIGURE_SBINDIR.64 =	$(CONFIGURE_PREFIX)/sbin

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-rpath
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)/clamav
CONFIGURE_OPTIONS +=	--with-dbdir=$(VARDIR)/clamav/db
CONFIGURE_OPTIONS +=	--with-user=clamav
CONFIGURE_OPTIONS +=	--with-group=clamav
CONFIGURE_OPTIONS +=	--without-gnu-ld
CONFIGURE_OPTIONS +=	--enable-bigstack
CONFIGURE_OPTIONS +=	--enable-readdir_r

# By code in clamav m4 snippets, --with-*=/usr is the specific verbatim wording
# for certain dependencies that is processed correctly for multiarch cases too
# (does not enforce "$withval/lib" as the library file location)
CONFIGURE_OPTIONS +=	--with-openssl=/usr
CONFIGURE_OPTIONS +=	--with-zlib=/usr
CONFIGURE_OPTIONS +=	--with-libcurl=/usr
CONFIGURE_OPTIONS +=	--with-libjson=/usr

# This one is specially patched for proper build
CONFIGURE_OPTIONS +=	--with-xml

CONFIGURE_OPTIONS +=	--with-iconv
CONFIGURE_OPTIONS +=	--with-systemdsystemunitdir=no

# These are poorly found in 64-bit case (if "--with-*-prefix=/usr" is passed)
# But auto-linker with just "-lbz2" works fine
CONFIGURE_OPTIONS +=	--enable-bzip2
CONFIGURE_OPTIONS +=	--without-libbz2-prefix
CONFIGURE_OPTIONS +=	--without-libncurses-prefix

CONFIGURE_OPTIONS +=	--enable-clamdtop
CONFIGURE_OPTIONS +=	--enable-libfreshclam

CONFIGURE_OPTIONS +=	--with-pcre
# ClamAV includes bluntly <pcre.h> which library/pcre component has in a subdir
CFLAGS +=	-I/usr/include/pcre

CONFIGURE_OPTIONS +=	--enable-milter

# ClamAV has a JIT bytecode support based on CLang LLVM. We serve it.
# By default it builds its own from copy of the source (takes ages to
# build C++ code, and increases the libclamav.so from ~3Mb to ~22Mb).
# And this is what we have to put up with for the best-featured product.
# Alternately it can be skipped (--disable-llvm) or could use system LLVM
#   CONFIGURE_OPTIONS +=	--with-system-llvm --with-llvm-linking=dynamic
# (but we only package a 32-bit one, it seems)
# While heavy, it allows more flexible and fast virus checks, see their blog:
#   http://blog.talosintel.com/2010/09/introduction-to-clamavs-low-level.html
# Note that currently (see etc/clamd.conf.sample:~635) you can no longer load
# unsigned untrusted bytecode, unless clamav was built in debug mode.
# TODO: maybe provide a JIT and a non-JIT (smaller) libclamav, mediated?..
# NOTE: bytecode compiler is a separate project at e.g.
#   https://github.com/vrtadmin/clamav-bytecode-compiler/releases
CONFIGURE_OPTIONS +=	--enable-llvm

# Without this libclamunrar.so gets /usr/lib/$(MACH64) RPATH
CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libmilter
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/network/smtp/sendmail
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
