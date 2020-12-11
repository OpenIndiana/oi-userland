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
# Copyright (c) 2015, 2019, Oracle and/or its affiliates. All rights reserved.
# Copyright 2015 OpenSXCE.org Martin Bochnig <opensxce@mail.ru>
# Copyright 2013-2017 Alexander Pyhalov
# Copyright 2019 Geoffrey Weiss
# Copyright 2019 Michal Nowak
#

BUILD_BITS = 64

include ../../../make-rules/shared-macros.mk

ESR = esr

COMPONENT_NAME =	firefox
COMPONENT_VERSION =	78.8.0
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      Mozilla Firefox Web browser
COMPONENT_PROJECT_URL =	http://www.mozilla.com/firefox
COMPONENT_SRC_NAME =	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SRC = 	$(COMPONENT_SRC_NAME)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC_NAME)$(ESR).source.tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:1cf2dfdee2e31fd0a5ecced6275a33fa11bee1d2a7c65e23350b26992584a110
ifndef CANDIDATE_BUILD
MOZILLA_FTP =		http://ftp.mozilla.org/pub/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)$(ESR)
else
MOZILLA_FTP =		http://ftp.mozilla.org/pub/$(COMPONENT_NAME)/candidates/$(COMPONENT_VERSION)$(ESR)-candidates/build$(CANDIDATE_BUILD)
endif
COMPONENT_ARCHIVE_URL =	$(MOZILLA_FTP)/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.mozilla.com/en-US/firefox/
COMPONENT_FMRI=		web/browser/firefox

LANG_LIST=	ar bg ca cs da de el es-AR es-CL es-ES et fi fr he hi-IN hr hu id is it ja kk ko lt lv mk nb-NO nl nn-NO pl pt-BR pt-PT ro ru sk sl sq sr sv-SE th tr uk vi zh-CN zh-TW
ifdef CANDIDATE_BUILD
LANG_FILES_LOCATION= \
	http://ftp.mozilla.org/pub/mozilla.org/firefox/candidates/$(COMPONENT_VERSION)-candidates/build$(CANDIDATE_BUILD)/linux-x86_64/xpi/
else
LANG_FILES_LOCATION= \
	http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/$(COMPONENT_VERSION)$(ESR)/linux-x86_64/xpi/
endif

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/common.mk

#PATH=$(USRBINDIR.64):$(PATH.illumos)
# /usr/gnu/bin needed to pick up the GNU version of tail and readelf.
# /usr/sbin needed for dtrace.
PATH = /usr/gnu/bin:/usr/bin:/usr/sbin

GCC_VERSION= 7

MOZCONFIG = $(SOURCE_DIR)/mozconfig
GNU_ARCH=		x86_64-sun-solaris

ifdef DEBUG
# disable code optimization
CFLAGS =
CXXFLAGS =

MOZCONFIG_DEBUG =	$(MOZCONFIG)
MOZCONFIG_NON_DEBUG =	/dev/null
else
MOZCONFIG_DEBUG =	/dev/null
MOZCONFIG_NON_DEBUG =	$(MOZCONFIG)
endif

CONFIGURE_ENV=
CONFIGURE_OPTIONS=

# clang or gcc
CC_TYPE = gcc
COMPILER.gcc= gcc
COMPILER.clang= clang
COMPILER = $(COMPILER.$(CC_TYPE))

CXXFLAGS += -Wno-invalid-offsetof -fpermissive
# not set in build 'js/xpconnect'
CPPFLAGS += -I/usr/include/libevent2
# type problem compiling ffvpx with clang 
CFLAGS += -D__int8_t_defined

FIREFOX_LIBDIR = /usr/lib/$(MACH64)

#	echo "ac_add_options --disable-jemalloc" >> $(MOZCONFIG) ; \
#	echo "ac_add_options PKG_CONFIG=/usr/bin/amd64/pkg-config" >> $(MOZCONFIG) ; 
COMPONENT_PRE_CONFIGURE_ACTION += \
        rm -f  $(MOZCONFIG); \
	echo "ac_add_options MOZILLA_OFFICIAL=1" >> $(MOZCONFIG) ; \
	echo "ac_add_options PKG_CONFIG=/usr/bin/amd64/pkg-config" >> $(MOZCONFIG) ; \
	echo "ac_add_options CC_TYPE=$(CC_TYPE)" >> $(MOZCONFIG) ; \
	echo "ac_add_options CC=$(CC)" >> $(MOZCONFIG) ; \
	echo "ac_add_options CXX=$(CXX)" >> $(MOZCONFIG) ; \
	echo "ac_add_options --prefix=/usr" >> $(MOZCONFIG) ; \
	echo "ac_add_options --libdir=$(FIREFOX_LIBDIR)" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-av1" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-crashreporter" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-debug-symbols" >> $(MOZCONFIG_NON_DEBUG) ; \
	echo "ac_add_options --disable-install-strip" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --disable-optimize" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --disable-tests" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-updater" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-debug" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --enable-js-shell" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-official-branding" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-optimize" >> $(MOZCONFIG_NON_DEBUG) ; \
	echo "ac_add_options --enable-pulseaudio" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-pixman" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-update-channel=esr" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-intl-api" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-libevent" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-zlib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --host=$(GNU_ARCH)" >> $(MOZCONFIG) ; \
	echo "ac_add_options --target=$(GNU_ARCH)" >> $(MOZCONFIG) ; \

LD_SECEXT_OPTIONS += $(SSBD_ENABLE)

# 28395728
LD_MAP_NOEXBSS.sparc=

# libmozgtk needs to link to gtk3 and others
LD_Z_IGNORE=

# missing symbols from gtk3 during Firefox start
LD_B_DIRECT=

LD_OPTIONS += -msave-args

# because we touched old-configure.in and js/src/old-configure.in
COMPONENT_PRE_CONFIGURE_ACTION += (cd $(COMPONENT_NAME)-$(COMPONENT_VERSION); autoreconf; touch configure; cd js/src; autoreconf; touch configure);


#FIREFOX_LIBDIR =	$(CONFIGURE_LIBDIR.$(BITS))

#ENV +=  PATH=$(PATH)
#ENV +=	CC=$(CC)
ENV +=	CFLAGS="$(CFLAGS)"
#ENV +=	CXX=$(CXX)
ENV +=	CXXFLAGS="$(CXXFLAGS)"
#ENV +=	LDFLAGS="$(LDFLAGS) -lm"
#ENV +=	MOZILLA_OFFICIAL=1
#ENV +=	MOZ_TELEMETRY_REPORTING=1
#ENV +=	MOZ_PACKAGE_JSSHELL=1
#ENV +=	MOZ_PKG_FORMAT=XZ
#ENV +=	PKG_SKIP_STRIP=1
#ENV +=	MOZILLA_PKG_NAME=firefox
#ENV +=	SHELL="/bin/bash"
#ENV +=  LDFLAGS="-L$(BUILD_DIR_64)/dist/lib -L$(BUILD_DIR_64)/dist/bin"
#ENV +=  PYTHON="$(PYTHON)"
ENV += PKG_CONFIG=/usr/bin/amd64/pkg-config

COMPONENT_BUILD_ARGS += $(JOBS:%=-j%)

CONFIGURE_ENV =	$(ENV)
COMPONENT_BUILD_ENV =	$(ENV)
COMPONENT_INSTALL_ENV += HOME=/tmp

LANG_FILES=$(addsuffix .xpi,$(LANG_LIST))

CLEAN_PATHS += $(LANG_FILES)

$(LANG_FILES): 
	$(FETCH) --file $@  --url $(LANG_FILES_LOCATION)/$@

download prep:: $(LANG_FILES)

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/browser/installer ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))

COMPONENT_POST_INSTALL_ACTION  = \
    for file in $(PROTO_DIR)$(FIREFOX_LIBDIR)/firefox/*.so \
          $(PROTO_DIR)$(FIREFOX_LIBDIR)/firefox/plugin-container; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$(FIREFOX_LIBDIR)/firefox:/usr/lib/mps/amd64:$$ORIGIN"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR):$(FIREFOX_LIBDIR)/firefox:/usr/lib/mps/amd64:$$ORIGIN"' $$file ; \
    done ;

donothave_SIGNED_LIST = libsoftokn3.so libnssdbm3.so libfreebl3.so


COMPONENT_POST_INSTALL_ACTION += \
        slist='$(SIGNED_LIST)' ; for f in $$slist ; do \
            mcs -d $(PROTO_DIR)$(FIREFOX_LIBDIR)/firefox/$$f ; \
            LD_LIBRARY_PATH=$(PROTO_DIR)$(FIREFOX_LIBDIR)/firefox $(BUILD_DIR_64)/dist/bin/shlibsign -v -i $(PROTO_DIR)$(FIREFOX_LIBDIR)/firefox/$$f ; \
        done ;

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

COMPONENT_TEST_DIR =    $(@D)/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS = \
	'-e "/^PASSED ALL/,/Failed:/p" ' \
	'-e "/^FAILURES:/,/Failed:/p" ' \
	'-e "/.*/d" '

# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf-213
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += developer/clang-90
REQUIRED_PACKAGES += developer/lang/rustc
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += library/python/psutil
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/nspr/header-nspr
REQUIRED_PACKAGES += system/library/mozilla-nss/header-nss
REQUIRED_PACKAGES += library/http-parser


# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/toolkit/libxt
