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

COMPONENT_NAME=		thunderbird
COMPONENT_VERSION=	38.5.0
COMPONENT_PROJECT_URL=	http://www.mozilla.com/thunderbird
COMPONENT_SRC=		comm-esr38
COMPONENT_SRC_NAME =	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC_NAME).source.tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:7da187d4d5df17b1457bd93b584f78f5e41d2094f87c14e74ee9d8064de25d0d
MOZILLA_FTP = 		http://ftp.mozilla.org/pub/mozilla.org/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_URL=	$(MOZILLA_FTP)/source/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	tbird/mailer

TPNO=			26829

LIGHTNING_VERSION=	lightning-4.0.5

# There are a set of .xpi files (as given in the LANG_LIST definition below)
# that we need. These are available under:
# http://ftp.mozilla.org/pub/mozilla.org/thunderbird/releases/31.6.0/linux-i686/xpi/
# https://ftp.mozilla.org/pub/calendar/lightning/candidates/4.0.5-candidates/build1/linux-i686/
# We could download and unpack them individually, but instead I've created
# a compressed tarball of them, and made that available locally for download.
# Downloading them individually can be a problem because firefox/thunderbird 
# collide due to different files with identical .xpi names. 
COMPONENT_ARCHIVE_1 =   	$(COMPONENT_SRC_NAME)-xpi.tar.gz
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:eeb85b3e5ef7a97abff831f3aa895c2034cb8f039bb3383dba3a5f495e1fe93f
COMPONENT_ARCHIVE_URL_1 =       $(INTERNAL_ARCHIVE_MIRROR)/source-archives/$(COMPONENT_ARCHIVE_1)

COMPONENT_ARCHIVE_2 =		$(LIGHTNING_VERSION)-xpi.tar.gz
COMPONENT_ARCHIVE_HASH_2 = \
    sha256:96f263984b1e939215a614dea21fda479eb4babf1574141728b9dbf273067893
COMPONENT_ARCHIVE_URL_2 = 	$(INTERNAL_ARCHIVE_MIRROR)/source-archives/$(COMPONENT_ARCHIVE_2)

LANG_LIST = ar bg ca cs da de el es-AR es-ES et eu fi \
	fr gl he hu id is it ja ko lt nb-NO nl nn-NO pa-IN pl \
	pt-BR pt-PT ro ru sk sl sq sv-SE tr uk zh-CN zh-TW

# Firefox and Thunderbird share the same firefox*.patch patches. Copy these 
# patches from the Firefox patches directory, except for patches 42 and 46, 
# which don't get applied in Thunderbird.
COMPONENT_POST_UNPACK_ACTION += \
	rm -f patches/firefox*.patch ; \
	cp ../firefox/patches/*.patch patches/ ; \
	rm -f patches/firefox*42*.patch patches/firefox*46*.patch;
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk

# Depends on libsmbclient but samba is on the do-not-publish list, so this
# must be too.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32=
INSTALL_32=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/ips.mk

# /usr/sbin needed for dtrace.
PATH =         /usr/gnu/bin:/usr/bin:/usr/sbin

MOZCONFIG =	$(BUILD_DIR_32)/mozconfig

COMPONENT_PRE_CONFIGURE_ACTION += \
	echo "mk_add_options BUILD_OFFICIAL=1" > $(MOZCONFIG) ; \
	echo "mk_add_options MOZILLA_OFFICIAL=1" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-application=mail" >> $(MOZCONFIG) ; \
	echo "ac_add_options --prefix=/usr" >> $(MOZCONFIG) ; \
	echo "ac_add_options --libdir=/usr/lib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --mandir=/usr/share/man" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-debug" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-optimize" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-tests" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-libevent" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-zlib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-bz2" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-ffi" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-sqlite" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-libxul" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-jemalloc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-official-branding" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-updater" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-update-packaging" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-ipc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-zlib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-bz2" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-gstreamer" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-pixman" >> $(MOZCONFIG) ; \
	echo "ac_add_options --without-intl-api" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-crashreporter" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-debug-symbols=no" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-calendar" >> $(MOZCONFIG) ; \
        echo 'ac_add_options --with-rpath="\\\\\\$$\\$$ORIGIN"' >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-startup-notification" >> $(MOZCONFIG) ;

CXXFLAGS += 		-Wno-invalid-offsetof -fpermissive
CC +=		$(CC_BITS)
CXX +=		$(CC_BITS)

CONFIGURE_ENV +=	PKG_CONFIG_PATH=$(CONFIGURE_LIBDIR.$(BITS))/pkgconfig
CONFIGURE_ENV +=	OS_DEFINES="-D__USE_LEGACY_PROTOTYPES__"
# -L.../dist/bin needs to be set otherwise it will report missing libnss3.so, 
# libssl3.so, etc, while linking.
CONFIGURE_ENV +=	LDFLAGS="-z ignore -z interpose -B nodirect -L$(BUILD_DIR_32)/dist/lib"

CONFIGURE_ENV +=	MOZCONFIG=$(MOZCONFIG)
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

COMPONENT_POST_CONFIGURE_ACTION += \
        $(CP) $(MOZCONFIG) $(COMPONENT_SRC)/mozconfig

COMPONENT_POST_BUILD_ACTION = \
        (cd $(@D)/mail/installer ; $(ENV) $(COMPONENT_BUILD_ENV) \
                $(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))

# Path to lightning extension directory
LIGHTNING_EXT_DIR = \
	$(PROTOUSRLIBDIR)/thunderbird-$(COMPONENT_VERSION)/extensions/{e2fda1a4-762b-4020-b5ad-a41df1933103}

COMPONENT_POST_INSTALL_ACTION += \
	$(CP) -r $(BUILD_DIR_32)/dist/bin/distribution/extensions/{e2fda1a4-762b-4020-b5ad-a41df1933103} \
		$(LIGHTNING_EXT_DIR) ;

COMPONENT_POST_INSTALL_ACTION += \
        $(RM) -rf xpi ; \
        /usr/bin/tar xvf $(COMPONENT_ARCHIVE_1) > /dev/null 2>&1 ; \
	/usr/bin/tar xvf $(COMPONENT_ARCHIVE_2) > /dev/null 2>&1 ; \
        list1='$(LANG_LIST)' ; for f in $$list1 ; do \
            $(CP) xpi/$$f.xpi \
                $(PROTOUSRLIBDIR)/thunderbird-$(COMPONENT_VERSION)/extensions/langpack-$$f@thunderbird.mozilla.org.xpi ; \
	    unzip xpi-lightning/$(LIGHTNING_VERSION).$$f.linux-i686.xpi \
		chrome/calendar-$$f/\* chrome/lightning-$$f/\* -d \
		    $(LIGHTNING_EXT_DIR)/ ; \
	    echo 'locale calendar '$$f' chrome/calendar-'$$f'/locale/'$$f'/calendar/' >> $(LIGHTNING_EXT_DIR)/chrome.manifest ; \
	    echo 'locale lightning '$$f' chrome/lightning-'$$f'/locale/'$$f'/lightning/' >> $(LIGHTNING_EXT_DIR)/chrome.manifest ; \
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

COMPONENT_TEST_DIR =    $(@D)/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS += \
        '-e "/\(^TEST-PASS\).*/d" '

$(SOURCE_DIR)/.patched-firefox38-%: GPATCH_FLAGS += -d $(@D)/mozilla

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
