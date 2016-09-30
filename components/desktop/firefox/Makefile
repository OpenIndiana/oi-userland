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

BUILD_BITS= 32
COMPILER= gcc
include ../../../make-rules/shared-macros.mk

# gcc 5.3 can't compile this version of firefox yet, so keep using 4.9 for now.
GCC_ROOT = /usr/gcc/4.9

COMPONENT_NAME =		firefox
COMPONENT_VERSION =		45.4.0esr
COMPONENT_PROJECT_URL =		http://www.mozilla.com/firefox
COMPONENT_SRC_NAME =		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SRC = 		$(COMPONENT_SRC_NAME)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC_NAME).source.tar.xz
COMPONENT_ARCHIVE_HASH = \
    sha256:cfd90096b9e1019b9de4fe061ece8c65f668b8a24bcbb657ce6b3c940ef83ad0
MOZILLA_FTP = 		        http://ftp.mozilla.org/pub/mozilla.org/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_URL =		$(MOZILLA_FTP)/source/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB =		firefox/browser

TPNO=				31455

IPS_COMPONENT_VERSION =		45.4.0

# There are a set of .xpi files (as given in the LANG_LIST definition below)
# that we need. These are available under:
# http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/31.8.0esr/linux-i686/xpi/
# We could download and unpack them individually, but instead I've created
# a compressed tarball of them, and made that available locally for download.
# Downloading them individually can be a problem because firefox/thunderbird 
# collide due to different files with identical .xpi names.
COMPONENT_ARCHIVE_1 =           $(COMPONENT_SRC_NAME)-xpi.tar.gz
COMPONENT_ARCHIVE_HASH_1 = \
	sha256:7a1cfadd2bdc81c7e4ecfdf138ec565a8baf7fbb087491db201e0c4fe8994299
COMPONENT_ARCHIVE_URL_1 =       $(INTERNAL_ARCHIVE_MIRROR)/$(COMPONENT_ARCHIVE_1)

LANG_LIST = ar be bg ca cs da de el es-AR es-CL es-ES et fi \
	fr he hi-IN hr hu id is it ja kk ko lt lv mk nb-NO nl nn-NO \
	pl pt-BR pt-PT ro ru sk sl sq sr sv-SE th tr uk vi zh-CN zh-TW

# Alignment issues on sparc: do not publish until resolved.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# /usr/gnu/bin needed to pick up the GNU version of tail and readelf.
# /usr/sbin needed for dtrace.
PATH =			$(dirname $(CC)):/usr/gnu/bin:/usr/bin:/usr/sbin

CLEAN_PATHS +=		$(COMPONENT_SRC)
CLEAN_PATHS +=		$(COMPONENT_DIR)/xpi

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
	echo "ac_add_options --with-system-zlib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-bz2" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-libevent" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-ffi" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-jemalloc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-xinerama" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-crashreporter" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-pulseaudio" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-gstreamer" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-intl-api" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-libffi" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-sqlite" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-ipc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-pixman" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-startup-notification" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-dtrace" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-replace-malloc" >> $(MOZCONFIG) ;

CXXFLAGS +=     -Wno-invalid-offsetof -fpermissive
CC +=           $(CC_BITS)
CXX +=          $(CC_BITS)

# Currently, GCC 4.9 incorrectly forces all 32-bit compilation to use lf64(7) 
# interfaces.  
CFLAGS += -U_FILE_OFFSET_BITS
CXXFLAGS += -U_FILE_OFFSET_BITS

CONFIGURE_ENV +=	PKG_CONFIG_PATH=$(CONFIGURE_LIBDIR.$(BITS))/pkgconfig
CONFIGURE_ENV +=	OS_DEFINES="-D__USE_LEGACY_PROTOTYPES__"
# -L.../dist/lib needs to be set otherwise it will report missing libnss3.so, 
# libssl3.so, etc, while linking.
CONFIGURE_ENV +=        LDFLAGS="-z ignore -z interpose -B nodirect -L$(BUILD_DIR_32)/dist/lib -L$(BUILD_DIR_32)/dist/bin"


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

FF_XPI = $(MOZILLA_FTP)/linux-i686/xpi

# Run gmake download-xpis to download a tarball for xpi locally. 
# The resulting archive should be uploaded to userland internal archive.
download-xpis:
	@echo "download-xpis"
	$(RM) -r $(COMPONENT_DIR)/$(COMPONENT_ARCHIVE_1)
	$(MKDIR) $(COMPONENT_DIR)/xpi
	@echo "downloading firefox xpis"
	list1='$(LANG_LIST)' ; for f in $$list1 ; do \
	    echo $$f; \
	    /usr/bin/curl -s -o $(COMPONENT_DIR)/xpi/$$f.xpi \
	        $(FF_XPI)/$$f.xpi; \
	done
	(cd $(COMPONENT_DIR); \
	    $(TAR) czvf $(COMPONENT_DIR)/$(COMPONENT_ARCHIVE_1) xpi )
	/usr/bin/sha256sum $(COMPONENT_ARCHIVE_1)

SIGNED_LIST.i386 = libsoftokn3.so libnssdbm3.so libfreebl3.so
SIGNED_LIST.sparc = libsoftokn3.so libnssdbm3.so libfreebl_32int_3.so libfreebl_32int64_3.so
SIGNED_LIST = $(SIGNED_LIST.$(MACH))

COMPONENT_POST_INSTALL_ACTION += \
	slist='$(SIGNED_LIST)' ; for f in $$slist ; do \
	    mcs -d $(PROTOUSRLIBDIR)/firefox-$(IPS_COMPONENT_VERSION)/$$f ; \
	    LD_LIBRARY_PATH=$(PROTOUSRLIBDIR)/firefox-$(IPS_COMPONENT_VERSION) $(BUILD_DIR_32)/dist/bin/shlibsign -v -i $(PROTOUSRLIBDIR)/firefox-$(IPS_COMPONENT_VERSION)/$$f ; \
        done ;

COMPONENT_TEST_MASTER = \
        $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master
COMPONENT_TEST_DIR =    $(@D)/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS = \
	'-e "/^TIMEOUTS:/,/Failed:/p" ' \
	'-e "/.*/d" '

REQUIRED_PACKAGES += codec/libogg
REQUIRED_PACKAGES += codec/libvorbis
REQUIRED_PACKAGES += codec/ogg-vorbis
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/gcc-49
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
