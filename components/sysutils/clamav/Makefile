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
COMPONENT_VERSION=	0.99.2
ifeq ($(words $(subst ., ,$(COMPONENT_VERSION))),2)
 IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).0
else
 IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION)
endif
COMPONENT_REVISION=	1
### Library files are tagged with unique per-version numbers
COMPONENT_VERSION_LIB_MAJOR=	7
COMPONENT_VERSION_LIB_FULL=	$(COMPONENT_VERSION_LIB_MAJOR).1.1
COMPONENT_SUMMARY=	ClamAV $(IPS_COMPONENT_VERSION) opensource antivirus toolkit
COMPONENT_FMRI= 	antivirus/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:167bd6a13e05ece326b968fdb539b05c2ffcfef6018a274a10aeda85c2c0027a
COMPONENT_PROJECT_URL=	http://www.clamav.org/
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

# Make sure that *-config scripts are taken from proper MACH$(BITS) dir
PATH.64=$(GNUBIN)/$(MACH64):$(USRBINDIR64):$(GNUBIN):$(USRBINDIR)
PATH.32=$(GNUBIN):$(USRBINDIR)
PATH=$(PATH.$(BITS))

USRLIBDIR.32=$(USRLIBDIR)
USRLIBDIR.64=$(USRLIBDIR64)

GNULIBDIR.32=$(GNULIB)
GNULIBDIR.64=$(GNULIB64)

LDFLAGS.$(BITS) += -L$(GNULIBDIR.$(BITS)) -R$(GNULIBDIR.$(BITS))

# Redefine the LDFLAGS completely, try to avoid "/usr/lib" in 64-bit bins/libs
LDFLAGS = $(LDFLAGS.$(BITS)) -m$(BITS)

COMPONENT_PREP_ACTION = \
    (cd $(@D) &&\
        aclocal -I . &&\
        autoheader &&\
        automake -a -f -c --gnu &&\
        autoconf &&\
        $(RM) config.h )

# Missing files in build dir for configure without this
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SYSCONFDIR =	$(ETCDIR)/clamav

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared
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

### The clamav-milter requires that libmilter exists (in OI Hipster's
### sendmail-8.14.4 - or rather illumos-gate's, that is only present
### for 32-bits at this time, it seems...)
CONFIGURE_OPTIONS.32 +=	--enable-milter

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


build:		$(BUILD_32_and_64)

# Ensure 32-bit configs are installed last
$(INSTALL_32): $(INSTALL_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/network/smtp/sendmail
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
