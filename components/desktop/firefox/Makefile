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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

# parfait is a bit unhappy (22527218)
export PARFAIT_BUILD=no

COMPILER =	gcc

include ../../../make-rules/shared-macros.mk

# gcc 5.3 can't compile this version of firefox yet, so keep using 4.8 for now.
GCC_ROOT = /usr/gcc/4.8

COMPONENT_NAME =		firefox
COMPONENT_VERSION =		38.5.0esr
COMPONENT_PROJECT_URL =		http://www.mozilla.com/firefox
COMPONENT_SRC =			mozilla-esr38
COMPONENT_SRC_NAME =		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC_NAME).source.tar.bz2
COMPONENT_ARCHIVE_HASH = \
	sha256:2a1f90cfe390ab20be88fed38cb9f61a18281cfbee47505c67e0254d339cdb20
MOZILLA_FTP = 		        http://ftp.mozilla.org/pub/mozilla.org/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_URL =		$(MOZILLA_FTP)/source/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB =		firefox/browser

TPNO=				26828	

IPS_COMPONENT_VERSION =		38.5.0

# There are a set of .xpi files (as given in the LANG_LIST definition below)
# that we need. These are available under:
# http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/31.8.0esr/linux-i686/xpi/
# We could download and unpack them individually, but instead I've created
# a compressed tarball of them, and made that available locally for download.
# Downloading them individually can be a problem because firefox/thunderbird 
# collide due to different files with identical .xpi names.
COMPONENT_ARCHIVE_1 =           $(COMPONENT_SRC_NAME)-xpi.tar.gz
COMPONENT_ARCHIVE_HASH_1 = \
	sha256:1fe09d5540167cbda3029f4e02640498fbb98ad7b47cdb6b8872e6dcf522a3e1
COMPONENT_ARCHIVE_URL_1 =       $(INTERNAL_ARCHIVE_MIRROR)/source-archives/$(COMPONENT_ARCHIVE_1)

LANG_LIST = ar be bg ca cs da de el es-AR es-CL es-ES et fi \
	fr he hi-IN hr hu id is it ja kk ko lt lv mk nb-NO nl nn-NO \
	pl pt-BR pt-PT ro ru sk sl sq sr sv-SE th tr uk vi zh-CN zh-TW

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk

# Alignment issues on sparc: do not publish until resolved.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32=
INSTALL_32=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/ips.mk

# /usr/gnu/bin needed to pick up the GNU version of tail and readelf.
# /usr/sbin needed for dtrace.
PATH =			$(dirname $(CC)):/usr/gnu/bin:/usr/bin:/usr/sbin

CLEAN_PATHS +=		$(COMPONENT_SRC)

MOZCONFIG = 		$(BUILD_DIR_32)/mozconfig

COMPONENT_PRE_CONFIGURE_ACTION += \
	echo "mk_add_options BUILD_OFFICIAL=1" > $(MOZCONFIG) ; \
	echo "mk_add_options MOZILLA_OFFICIAL=1" >> $(MOZCONFIG) ; \
	echo "ac_add_options --prefix=/usr" >> $(MOZCONFIG) ; \
	echo "ac_add_options --libdir=/usr/lib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --mandir=/usr/share/man" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-official-branding" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-updater" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-debug-symbols=no" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-update-packaging" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-update-channel=esr" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-tests" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-libevent" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-zlib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-bz2" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-ffi" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-sqlite" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-jemalloc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-xinerama" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-crashreporter" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-pulseaudio" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-gstreamer" >> $(MOZCONFIG) ; \
	echo "ac_add_options --without-intl-api" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-libffi" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-ipc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-pixman" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-startup-notification" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-dtrace" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-replace-malloc" >> $(MOZCONFIG) ;

CXXFLAGS +=     -Wno-invalid-offsetof -fpermissive
CC +=           $(CC_BITS)
CXX +=          $(CC_BITS)

CONFIGURE_ENV +=	PKG_CONFIG_PATH=$(CONFIGURE_LIBDIR.$(BITS))/pkgconfig
CONFIGURE_ENV +=	OS_DEFINES="-D__USE_LEGACY_PROTOTYPES__"
CONFIGURE_ENV +=        CXXFLAGS='-xlibmil -xlibmopt -lCrun -lCstd -features=tmplrefstatic,no%except -D_XOPEN_SOURCE=500 -D__EXTENSIONS__ -template=no%extdef'
# -L.../dist/lib needs to be set otherwise it will report missing libnss3.so, 
# libssl3.so, etc, while linking.
CONFIGURE_ENV +=        LDFLAGS="$(LD_Z_IGNORE) -z interpose -B nodirect -L$(BUILD_DIR_32)/dist/lib"


CONFIGURE_ENV +=	MOZCONFIG=$(MOZCONFIG)
CONFIGURE_ENV +=	"CC=$(CC)"
CONFIGURE_ENV +=	"CXX=$(CXX)"
CONFIGURE_ENV +=	"CFLAGS=$(CFLAGS)"
CONFIGURE_ENV +=	"CXXFLAGS=$(CXXFLAGS)"

# If the configure options are not explicitly set, then configure fails with:
# configure: warning: CC=/usr/gcc/4.8/bin/gcc: invalid host type
# invalid host type
# configure: warning: CXX=/usr/gcc/4.8/bin/g++: invalid host type
# invalid host type
# configure: error: can only configure for one host and one target at a time
CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/browser/installer ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))

COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(BUILD_DIR_32)/dist/firefox/precomplete \
		$(PROTOUSRLIBDIR)/firefox-$(IPS_COMPONENT_VERSION)/precomplete ;

COMPONENT_POST_INSTALL_ACTION += \
        $(RM) -rf xpi ; \
        /usr/bin/tar xvf $(COMPONENT_ARCHIVE_1) > /dev/null 2>&1 ; \
        list1='$(LANG_LIST)' ; for f in $$list1 ; do \
            $(CP) xpi/$$f.xpi \
                $(PROTOUSRLIBDIR)/firefox-$(IPS_COMPONENT_VERSION)/browser/extensions/langpack-$$f@firefox.mozilla.org.xpi ; \
        done ;

SIGNED_LIST.i386 = libsoftokn3.so libnssdbm3.so libfreebl3.so
SIGNED_LIST.sparc = libsoftokn3.so libnssdbm3.so libfreebl_32int_3.so libfreebl_32int64_3.so
SIGNED_LIST = $(SIGNED_LIST.$(MACH))

COMPONENT_POST_INSTALL_ACTION += \
	slist='$(SIGNED_LIST)' ; for f in $$slist ; do \
	    mcs -d $(PROTOUSRLIBDIR)/firefox-$(IPS_COMPONENT_VERSION)/$$f ; \
	    LD_LIBRARY_PATH=$(PROTOUSRLIBDIR)/firefox-$(IPS_COMPONENT_VERSION) $(BUILD_DIR_32)/dist/bin/shlibsign -v -i $(PROTOUSRLIBDIR)/firefox-$(IPS_COMPONENT_VERSION)/$$f ; \
        done ;

COMPONENT_TEST_DIR =    $(@D)/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS += \
        '-e "/\(^TEST-PASS\).*/d" '

configure:	$(CONFIGURE_32)

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TEST_32)

system-test:	$(NO_TESTS)

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
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/toolkit/libxt
