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
# Copyright 2021 Carsten Grzemba
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	librewolf
COMPONENT_VERSION =	114.0.2
COMPONENT_BUILD =	1
COMPONENT_SUMMARY=      LibreWolf Web browser
COMPONENT_PROJECT_URL =	https://librewolf.net
COMPONENT_SRC_NAME =	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_BUILD)
COMPONENT_SRC = 	$(COMPONENT_SRC_NAME)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC_NAME).source.tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2138e4cb43a480e04c96daea579c6e4179ab3caea8d99539278cf5631819bf27
COMPONENT_ARCHIVE_URL =	https://gitlab.com/api/v4/projects/32320088/packages/generic/librewolf-source/$(COMPONENT_VERSION)-$(COMPONENT_BUILD)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		web/browser/librewolf
COMPONENT_CLASSIFICATION =	Applications/Internet

RUST_VERSION = 1.69.0

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/common.mk

RUSTUP_HOME = $(BUILD_DIR)/.rust_up
CARGO_HOME  = $(BUILD_DIR)/.cargo

PATH = $(CARGO_HOME)/bin:$(PATH.gnu)

MOZCONFIG = $(SOURCE_DIR)/mozconfig
GNU_ARCH= x86_64-unknown-illumos

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
# xpcom uses DEF XP_SOLARIS
CXXFLAGS += -DXP_SOLARIS
# type problem compiling ffvpx with clang 
CFLAGS += -D__int8_t_defined

FIREFOX_LIBDIR =	$(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_PRE_CONFIGURE_ACTION += \
	echo "ac_add_options PKG_CONFIG=/usr/bin/amd64/pkg-config" >> $(MOZCONFIG) ; \
	echo "ac_add_options CC_TYPE=$(CC_TYPE)" >> $(MOZCONFIG) ; \
	echo "ac_add_options CC=$(CC)" >> $(MOZCONFIG) ; \
	echo "ac_add_options CXX=$(CXX)" >> $(MOZCONFIG) ; \
	echo "ac_add_options --prefix=/usr" >> $(MOZCONFIG) ; \
	echo "ac_add_options --libdir=$(FIREFOX_LIBDIR)" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-debug-symbols" >> $(MOZCONFIG_NON_DEBUG) ; \
	echo "ac_add_options --disable-install-strip" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --enable-jemalloc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-js-shell" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-pulseaudio" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-replace-malloc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-pixman" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-zlib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --host=$(GNU_ARCH)" >> $(MOZCONFIG) ; \
	echo "ac_add_options --target=$(GNU_ARCH)" >> $(MOZCONFIG) ; \
	echo "ac_add_options --without-wasm-sandboxed-libraries" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-alsa" >> $(MOZCONFIG) ; \
# 	echo "ac_add_options --enable-bootstrap" >> $(MOZCONFIG) ; \
#	echo "ac_add_options --with-wasi-sysroot=" >> $(MOZCONFIG) ; \

LD_SECEXT_OPTIONS += $(SSBD_ENABLE)

# 28395728
LD_MAP_NOEXBSS.sparc=

# libmozgtk needs to link to gtk3 and others
LD_Z_IGNORE=

# missing symbols from gtk3 during Firefox start
LD_B_DIRECT=

# hope to get args data in stacks of core dumps
LD_OPTIONS += -msave-args

# use a local installed rust since the system version may not be compatible
COMPONENT_PRE_CONFIGURE_ACTION += ( \
	export RUSTUP_HOME=$(RUSTUP_HOME); \
	export CARGO_HOME=$(CARGO_HOME); \
	export RUSTUP_INIT_SKIP_PATH_CHECK=yes; \
	curl https://sh.rustup.rs -sSf | bash -s -- -y --no-modify-path; \
	source $(CARGO_HOME)/env; \
	rustup install $(RUST_VERSION); \
	rustup default $(RUST_VERSION)-x86_64-unknown-illumos; \
	rustup show; \
	cargo install --root=$(CARGO_HOME) --vers 0.24.3 cbindgen; \
	);

ENV +=	CFLAGS="$(CFLAGS)"
ENV +=	CXXFLAGS="$(CXXFLAGS)"
ENV += PKG_CONFIG=/usr/bin/amd64/pkg-config
ENV += RUSTUP_HOME=$(RUSTUP_HOME)
ENV += CARGO_HOME=$(CARGO_HOME)

COMPONENT_BUILD_ARGS += $(JOBS:%=-j%)

CONFIGURE_ENV =	$(ENV)
COMPONENT_BUILD_ENV =	$(ENV)
COMPONENT_INSTALL_ENV += HOME=/tmp

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/browser/installer ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))

COMPONENT_POST_INSTALL_ACTION  = \
    for file in `find $(PROTO_DIR)$(FIREFOX_LIBDIR)/firefox/ -name "*.so"`; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$(FIREFOX_LIBDIR)/firefox:/usr/lib/mps/amd64"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR):$(FIREFOX_LIBDIR)/firefox:/usr/lib/mps/amd64"' $$file ; \
    done ; \
    unzip -c $(PROTOUSRLIBDIR64)/$(COMPONENT_NAME)/omni.ja chrome/toolkit/content/global/license.html \
    | LC_ALL=en_US.UTF-8 lynx --display_charset=utf-8 -stdin --dump -nolist > $(COMPONENT_NAME).license ;

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

COMPONENT_TEST_DIR =    $(@D)/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS = \
	'-e "/^PASSED ALL/,/Failed:/p" ' \
	'-e "/^FAILURES:/,/Failed:/p" ' \
	'-e "/.*/d" '

# the license file is dynamically build, thus we need to remove it:
clean::
	$(RM) $(COMPONENT_LICENSE_FILE)

# Build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
PYTHON_REQUIRED_PACKAGES += library/python/psutil
REQUIRED_PACKAGES += developer/build/autoconf-213
REQUIRED_PACKAGES += developer/clang-15
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += developer/lang/rustc
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/http-parser
REQUIRED_PACKAGES += web/browser/lynx

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
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/gcc-10-compat-links
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrandr
