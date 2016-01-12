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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

# parfait is a bit unhappy (22527218)
export PARFAIT_BUILD=no

COMPILER =	gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		thunderbird
COMPONENT_VERSION=	31.6.0
COMPONENT_PROJECT_URL=	http://www.mozilla.com/thunderbird
COMPONENT_SRC=		comm-esr31
COMPONENT_SRC_NAME =	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC_NAME).source.tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:ccbf8cbb740bc1b30ecf4fe39aab226607f9a41e23a07e994c508a90e8b70508
MOZILLA_FTP = 		http://ftp.mozilla.org/pub/mozilla.org/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_URL=	$(MOZILLA_FTP)/source/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	thunderbird/mailer

TPNO=			22326

# There are a set of .xpi files (as given in the LANG_LIST definition below)
# that we need. These are available under:
# http://ftp.mozilla.org/pub/mozilla.org/thunderbird/releases/31.6.0/linux-i686/xpi/
# We could download and unpack them individually, but instead I've created
# a compressed tarball of them, and made that available locally for download.
# Downloading them individually can be a problem because firefox/thunderbird 
# collide due to different files with identical .xpi names. 
COMPONENT_ARCHIVE_1 =   thunderbird-31.6.0-xpi.tar.gz
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:80e9cc4b152d75f5c3887c01ad1767680aff5ca7c3aee87254bdc1574590b95e
COMPONENT_ARCHIVE_URL_1 =       $(INTERNAL_ARCHIVE_MIRROR)/source-archives/$(COMPONENT_ARCHIVE_1)

LANG_LIST = ar bg ca cs da de el es-AR es-ES et eu fi \
	fr gl he hu id is it ja ko lt nb-NO nl nn-NO pa-IN pl \
	pt-BR pt-PT ro ru sk sl sq sv-SE tr uk zh-CN zh-TW

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# /usr/sbin needed for dtrace.
PATH =         /usr/gnu/bin:/usr/bin:/usr/sbin

COMPONENT_PRE_CONFIGURE_ACTION += \
	echo "mk_add_options BUILD_OFFICIAL=1" > .mozconfig ; \
	echo "mk_add_options MOZILLA_OFFICIAL=1" >> .mozconfig ; \
	echo "ac_add_options --prefix=/usr" >> .mozconfig ; \
	echo "ac_add_options --libdir=/usr/lib" >> .mozconfig ; \
	echo "ac_add_options --mandir=/usr/share/man" >> .mozconfig ; \
	echo "ac_add_options --disable-debug" >> .mozconfig ; \
	echo "ac_add_options --enable-optimize" >> .mozconfig ; \
	echo "ac_add_options --disable-tests" >> .mozconfig ; \
	echo "ac_add_options --with-system-libevent" >> .mozconfig ; \
	echo "ac_add_options --with-system-zlib" >> .mozconfig ; \
	echo "ac_add_options --with-system-bz2" >> .mozconfig ; \
	echo "ac_add_options --enable-system-ffi" >> .mozconfig ; \
	echo "ac_add_options --enable-system-sqlite" >> .mozconfig ; \
	echo "ac_add_options --enable-libxul" >> .mozconfig ; \
	echo "ac_add_options --enable-jemalloc" >> .mozconfig ; \
	echo "ac_add_options --enable-official-branding" >> .mozconfig ; \
	echo "ac_add_options --disable-updater" >> .mozconfig ; \
	echo "ac_add_options --enable-update-packaging" >> .mozconfig ; \
	echo "ac_add_options --enable-ipc" >> .mozconfig ; \
	echo "ac_add_options --with-system-zlib" >> .mozconfig ; \
	echo "ac_add_options --with-system-bz2" >> .mozconfig ; \
	echo "ac_add_options --enable-gstreamer" >> .mozconfig ; \
	echo "ac_add_options --enable-system-pixman" >> .mozconfig ; \
	echo "ac_add_options --without-intl-api" >> .mozconfig ; \
	echo "ac_add_options --disable-crashreporter" >> .mozconfig ; \
	echo "ac_add_options --enable-debug-symbols=no" >> .mozconfig ; \
	echo "ac_add_options --enable-calendar" >> .mozconfig ; \
	echo "ac_add_options --enable-startup-notification" >> .mozconfig ;

CXXFLAGS += 		-Wno-invalid-offsetof

CONFIGURE_ENV +=	PKG_CONFIG_PATH=$(CONFIGURE_LIBDIR.$(BITS))/pkgconfig
CONFIGURE_ENV +=	OS_DEFINES="-D__USE_LEGACY_PROTOTYPES__"
CONFIGURE_ENV +=	LDFLAGS="-z ignore"

CONFIGURE_ENV +=	MOZCONFIG=$(shell pwd)/.mozconfig
CONFIGURE_ENV +=	"CC=$(CC)"
CONFIGURE_ENV +=	"CXX=$(CXX)"
CONFIGURE_ENV += 	"CFLAGS=$(CFLAGS)"
CONFIGURE_ENV +=	"CXXFLAGS=$(CXXFLAGS)"

# If the configure options are not explicitly set, then configure fails with:
# configure: warning: CC=/usr/gcc/4.8/bin/gcc: invalid host type
# invalid host type
# configure: warning: CXX=/usr/gcc/4.8/bin/gcc: invalid host type
# invalid host type
# configure: error: can only configure for one host and one target at a time
CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)

COMPONENT_POST_BUILD_ACTION = \
        (cd $(@D)/mail/installer ; $(ENV) $(COMPONENT_BUILD_ENV) \
                $(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))

COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(BUILD_DIR_32)/mozilla/dist/thunderbird/precomplete \
		$(PROTOUSRLIBDIR)/thunderbird-$(COMPONENT_VERSION)/precomplete ;

COMPONENT_POST_INSTALL_ACTION += \
	$(CP) -r $(BUILD_DIR_32)/mozilla/dist/bin/extensions/{e2fda1a4-762b-4020-b5ad-a41df1933103} \
		$(PROTOUSRLIBDIR)/thunderbird-$(COMPONENT_VERSION)/extensions/{e2fda1a4-762b-4020-b5ad-a41df1933103} ;

COMPONENT_POST_INSTALL_ACTION += \
        $(RM) -rf xpi ; \
        /usr/bin/tar xvf $(COMPONENT_ARCHIVE_1) > /dev/null 2>&1 ; \
        list1='$(LANG_LIST)' ; for f in $$list1 ; do \
            $(CP) xpi/$$f.xpi \
                $(PROTOUSRLIBDIR)/thunderbird-$(COMPONENT_VERSION)/extensions/langpack-$$f@thunderbird.mozilla.org.xpi ; \
        done ;

LIB_LIST.i386 =
LIB_LIST.sparc = $(PROTOUSRLIBDIR)/thunderbird-devel-$(COMPONENT_VERSION)/sdk/lib/cpu/sparcv8plus/libnspr_flt4.so
LIB_LIST = $(LIB_LIST.$(MACH))

COMPONENT_POST_INSTALL_ACTION += \
	slist='$(LIB_LIST)' ; for f in $$slist ; do \
	    $(MKDIR) $(PROTOUSRLIBDIR)/thunderbird-$(COMPONENT_VERSION)/cpu/sparcv8plus ; \
	    $(CP) $$f $(PROTOUSRLIBDIR)/thunderbird-$(COMPONENT_VERSION)/cpu/sparcv8plus/libnspr_flt4.so ; \
	done ;

ASLR_MODE =	$(ASLR_ENABLE)

COMPONENT_TEST_DIR =    $(@D)/mozilla/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS += \
        '-e "/\(^TEST-PASS\).*/d" '

configure:	$(CONFIGURE_32)

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TEST_32)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-libs
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/samba/libsmbclient
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/toolkit/libxt
