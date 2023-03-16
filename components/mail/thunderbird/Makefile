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
# Copyright 2017 Alexander Pyhalov
# Copyright 2018 Michal Nowak
# Copyright (c) 2015, 2021, Oracle and/or its affiliates.
# Copyright 2021, Carsten Grzemba
#

include ../../../make-rules/shared-macros.mk

# unfortunatly I see -m32 in CFLAGS despite that BUILD_BITS = 64 is set
BITS = 64

COMPONENT_NAME =	thunderbird
COMPONENT_VERSION =	102.9.0
COMPONENT_SUMMARY = Mozilla Thunderbird Email Application
COMPONENT_PROJECT_URL =	https://www.thunderbird.net/
COMPONENT_SRC = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE = 	$(COMPONENT_SRC).source.tar.xz
COMPONENT_ARCHIVE_HASH= \
	 sha256:ecb34de765d548ed26ea24d4d617567a7896230d7c8379c1ef76be8ca05d6fef
ifndef CANDIDATE_BUILD
MOZILLA_FTP = 		https://ftp.mozilla.org/pub/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)
else
MOZILLA_FTP = 		https://ftp.mozilla.org/pub/$(COMPONENT_NAME)/candidates/$(COMPONENT_VERSION)-candidates/build$(CANDIDATE_BUILD)
endif
COMPONENT_ARCHIVE_URL =	$(MOZILLA_FTP)/source/$(COMPONENT_ARCHIVE)

RUST_VERSION = 1.67.1

# TODO: use remote hashfile to verify
ALLOW_UNVERIFIED_DOWNLOADS=yes
export ALLOW_UNVERIFIED_DOWNLOADS

# There are a set of .xpi files (as given in the LANG_LIST definition
# below) that we need. We could download and unpack them individually, but
# they doesn't contain version in its file name and there is lot of them.
# Therefore we will download them and archive them in Userland cache using
# one file with version number.

LANG_LIST = af ar ast be bg br ca cak cs cy \
       da de dsb el en-CA en-GB en-US es-AR es-ES es-MX et \
       eu fi fr fy-NL ga-IE gd gl he hr hsb hu \
       hy-AM id is it ja ka kab kk ko lt lv ms \
       nb-NO nl nn-NO pa-IN pl pt-BR pt-PT rm ro ru sk sl \
       sq sr sv-SE th tr uk uz vi zh-CN zh-TW

LANG_FILES_LOCATION= \
        https://ftp.mozilla.org/pub/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)/linux-x86_64/xpi
#        https://ftp.mozilla.org/pub/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)$(ESR)/linux-x86_64/xpi
CLEAN_PATHS += $(COMPONENT_DIR)/xpi

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/common.mk

RUSTUP_HOME = $(BUILD_DIR)/.rust_up
CARGO_HOME  = $(BUILD_DIR)/.cargo

PATH = $(CARGO_HOME)/bin:$(PATH.gnu)

MOZCONFIG = $(SOURCE_DIR)/mozconfig
GNU_ARCH=               x86_64-unknown-illumos

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

THUNDERBIRD_LIBDIR = /usr/lib/$(MACH64)

COMPONENT_PRE_CONFIGURE_ACTION += \
	rm -f  $(MOZCONFIG); \
	echo "ac_add_options MOZILLA_OFFICIAL=1" >> $(MOZCONFIG) ; \
	echo "ac_add_options --prefix=/usr" >> $(MOZCONFIG) ; \
	echo "ac_add_options --libdir=$(THUNDERBIRD_LIBDIR)" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-av1" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-crashreporter" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-debug-symbols" >> $(MOZCONFIG_NON_DEBUG) ; \
	echo "ac_add_options --disable-install-strip" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --disable-optimize" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --disable-tests" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-updater" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-application=comm/mail" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-debug" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --enable-js-shell" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-official-branding" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-optimize" >> $(MOZCONFIG_NON_DEBUG) ; \
	echo "ac_add_options --enable-system-pixman" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-intl-api" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-libevent" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-zlib" >> $(MOZCONFIG) ; \
        echo "ac_add_options --host=$(GNU_ARCH)" >> $(MOZCONFIG) ; \
        echo "ac_add_options --target=$(GNU_ARCH)" >> $(MOZCONFIG) ; \
        echo "ac_add_options --without-wasm-sandboxed-libraries" >> $(MOZCONFIG) ; \

# xpcom uses DEF XP_SOLARIS
CXXFLAGS += -DXP_SOLARIS -Wno-invalid-offsetof -fpermissive 

# 28395728
LD_MAP_NOEXBSS.sparc=

# libmozgtk needs to link to gtk3 and others
LD_Z_IGNORE=

# missing symbols from gtk3 during Firefox start
LD_B_DIRECT=

# SPARC build seems to require more open files for "Reticulating splines" phase
ENV := ulimit -n 16384; $(ENV)

LANG_FILES=$(addsuffix .xpi,$(LANG_LIST))

CLEAN_PATHS += $(LANG_FILES)

$(LANG_FILES): 
	$(FETCH) --file $@  --url $(LANG_FILES_LOCATION)/$@

download prep:: $(LANG_FILES)

CONFIGURE_OPTIONS = CC=$(CC) CXX=$(CXX)

ENV +=  CFLAGS="$(CFLAGS)"
ENV +=  CXXFLAGS="$(CXXFLAGS)"
ENV += PKG_CONFIG=/usr/bin/amd64/pkg-config
ENV += RUSTUP_HOME=$(RUSTUP_HOME)
ENV += CARGO_HOME=$(CARGO_HOME)

COMPONENT_BUILD_ARGS += $(JOBS:%=-j%)

CONFIGURE_ENV = $(ENV)
COMPONENT_BUILD_ENV =   $(ENV)

# because we touched old-configure.in and js/src/old-configure.in
COMPONENT_PRE_CONFIGURE_ACTION += ( \
	cd $(COMPONENT_NAME)-$(COMPONENT_VERSION); \
        cp configure.in configure; \
        cd js/src; \
        cp configure.in configure; \
        export RUSTUP_HOME=$(RUSTUP_HOME); \
        export CARGO_HOME=$(CARGO_HOME); \
        export RUSTUP_INIT_SKIP_PATH_CHECK=yes; \
        curl https://sh.rustup.rs -sSf | bash -s -- -y --no-modify-path; \
        source $(CARGO_HOME)/env; \
        rustup install $(RUST_VERSION); \
        rustup default $(RUST_VERSION)-x86_64-unknown-illumos; \
        rustup show; \
        cargo install --root=$(CARGO_HOME) --vers 0.24.2 cbindgen; \
	);

# COMPONENT_POST_BUILD_ACTION = \
# 	(cd $(@D)/mail/installer ; $(ENV) $(COMPONENT_BUILD_ENV) \
# 		$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))

COMPONENT_POST_INSTALL_ACTION  += \
    for file in `find $(PROTO_DIR)$(THUNDERBIRD_LIBDIR)/thunderbird -name "*.so"`; \
          do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$(THUNDERBIRD_LIBDIR)/thunderbird:$$ORIGIN"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR):$(THUNDERBIRD_LIBDIR)/thunderbird:$$ORIGIN"' $$file ; \
    done ; \
    /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR):$(THUNDERBIRD_LIBDIR)/thunderbird:$$ORIGIN"' $(PROTO_DIR)$(THUNDERBIRD_LIBDIR)/thunderbird/plugin-container ; \
    
COMPONENT_POST_INSTALL_ACTION += \
        $(MKDIR) $(PROTO_DIR)$(THUNDERBIRD_LIBDIR)/thunderbird/distribution/extensions/; \
        list1='$(LANG_LIST)' ; for f in $$list1 ; do \
            $(CP) $$f.xpi \
                $(PROTO_DIR)$(THUNDERBIRD_LIBDIR)/thunderbird/distribution/extensions/langpack-$$f@thunderbird.mozilla.org.xpi ; \
        done ;

license: install
	@echo "regenerating license text"
	unzip -c $(PROTO_DIR)$(THUNDERBIRD_LIBDIR)/$(COMPONENT_NAME)/omni.ja chrome/messenger/content/messenger/license.html \
	    | lynx  -stdin --dump -nolist > $(COMPONENT_NAME).license

SIGNED_LIST.amd64 = libsoftokn3.so libnssdbm3.so libfreebl3.so
SIGNED_LIST.sparc = libsoftokn3.so libnssdbm3.so libfreebl_64fpu_3.so libfreebl_64int_3.so
SIGNED_LIST = $(SIGNED_LIST.$(MACH))

COMPONENT_POST_INSTALL_ACTION += \
	slist='$(SIGNED_LIST)' ; for f in $$slist ; do \
	    mcs -d $(PROT_DIR)$(THUNDERBIRD_LIBDIR)/$(COMPONENT_NAME)/$$f ; \
	    LD_LIBRARY_PATH=$(PROTO_DIR)$(THUNDERBIRD_LIBDIR)/$(COMPONENT_NAME) $(BUILD_DIR_64)/dist/bin/shlibsign -v -i $(PROTO_DIR)$(THUNDERBIRD_LIBDIR)/$(COMPONENT_NAME)/$$f ; \
        done ;

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

COMPONENT_TEST_DIR =    $(@D)/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS = \
	'-e "/^PASSED ALL/,/Failed:/p" ' \
	'-e "/^FAILURES:/,/Failed:/p" ' \
	'-e "/.*/d" '

# Build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/build/autoconf-213
REQUIRED_PACKAGES += developer/clang-15
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/http-parser
REQUIRED_PACKAGES += library/python/psutil
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += system/library/gcc-10-compat-links

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrandr
