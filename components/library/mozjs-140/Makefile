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
#

# USE_PARALLEL_BUILD = yes
include ../../../make-rules/shared-macros.mk
ENV = /usr/bin/env

# ESR should be set to esr for esr build, or an empty string for other builds
ESR = esr

# CANDIDATE_BUILD is the build number found in the candidates directory.
# CANDIDATE_BETA is the beta version found in the candidates directory.
# CANDIDATE_NIGHTLY is the nightly release hosted on github
# USE_HG_REPO is to use mozilla's hg source repo nstead of github
# Do not define any for final release build.
# CANDIDATE_BUILD=1
# CANDIDATE_BETA=9
# CANDIDATE_NIGHTLY=1
# USE_HG_REPO=1

COMPONENT_NAME =        mozjs
COMPONENT_VERSION =     140.17.0
COMPONENT_SUMMARY=      JavaScript interpreter and libraries
COMPONENT_PROJECT_URL = https://spidermonkey.dev/
COMPONENT_SRC_NAME =    firefox-$(COMPONENT_VERSION)
COMPONENT_LICENSE =     MPL 2.0
COMPONENT_LICENSE_FILE =mozjs.license
ifdef CANDIDATE_BETA
COMPONENT_ARCHIVE =     firefox-$(COMPONENT_VERSION)b$(CANDIDATE_BETA)$(ESR).source.tar.xz
else
COMPONENT_ARCHIVE =     $(COMPONENT_SRC_NAME)$(ESR).source.tar.xz
# CANDIDATE_BETA
endif

ifdef CANDIDATE_NIGHTLY
COMPONENT_GIT_HASH=     827e12a962ef47511089af4498f65ebf42fa57ca31db790bfd7e9a820d16b960
COMPONENT_SRC=          gecko-dev-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE=      $(COMPONENT_GIT_HASH).tar.gz
COMPONENT_ARCHIVE_URL=  https://github.com/mozilla/gecko-dev/archive/$(COMPONENT_ARCHIVE)
  ifdef USE_HG_REPO
  COMPONENT_HG_HASH=    ff0882e981495f07c521e0b00e1e83b050dfcdc2
  COMPONENT_SRC=        mozilla-central-$(COMPONENT_HG_HASH)
  COMPONENT_ARCHIVE=    $(COMPONENT_HG_HASH).zip
  COMPONENT_ARCHIVE_URL= https://hg.mozilla.org/mozilla-central/archive/$(COMPONENT_ARCHIVE)
  endif
else
 ifndef CANDIDATE_BUILD
MOZILLA_FTP =           https://ftp.mozilla.org/pub/firefox/releases/$(COMPONENT_VERSION)$(ESR)
  else
    ifndef CANDIDATE_BETA
MOZILLA_FTP =           https://ftp.mozilla.org/pub/firefox/candidates/$(COMPONENT_VERSION)$(ESR)-candidates/build$(CANDIDATE_BUILD)
    else
MOZILLA_FTP =           https://ftp.mozilla.org/pub/firefox/candidates/$(COMPONENT_VERSION)b$(CANDIDATE_BETA)$(ESR)-candidates/build$(CANDIDATE_BUILD)
    endif
  endif
COMPONENT_SRC =         $(COMPONENT_SRC_NAME)
COMPONENT_ARCHIVE_URL = $(MOZILLA_FTP)/source/$(COMPONENT_ARCHIVE)
endif

COMPONENT_ARCHIVE_HASH= sha256:4d6ed3b18b2069c55bab12d8ba95da6013ac0b036d8a031df8b9f39a25d05c33
COMPONENT_PROJECT_URL = https://www.mozilla.com/en-US/firefox/
COMPONENT_FMRI=         library/desktop/mozjs-140
COMPONENT_CLASSIFICATION = System/Libraries

RUST_VERSION = 1.86.0

# TODO: use remote hashfile to verify
ALLOW_UNVERIFIED_DOWNLOADS=yes
export ALLOW_UNVERIFIED_DOWNLOADS

ifdef CANDIDATE_NIGHTLY
FIREFOX_UPDATE_CHANNEL=nightly
else
  ifdef CANDIDATE_BETA
FIREFOX_UPDATE_CHANNEL=beta
else
    ifdef CANDIDATE_BUILD
FIREFOX_UPDATE_CHANNEL=default
    else
FIREFOX_UPDATE_CHANNEL=default
    endif
  endif
endif

# handle esr case to set FIREFOX_UPDATE_CHANNEL
ifdef ESR
  ifeq ($(ESR), esr)
    FIREFOX_UPDATE_CHANNEL=esr
  endif
endif

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

MOZCONFIG_DEBUG =       $(MOZCONFIG)
MOZCONFIG_NON_DEBUG =   /dev/null
else
MOZCONFIG_DEBUG =       /dev/null
MOZCONFIG_NON_DEBUG =   $(MOZCONFIG)
endif

# set custom mozbuild path
CONFIGURE_ENV += MOZBUILD_STATE_PATH=$(BUILD_DIR)/mozbuild
COMPONENT_BUILD_ENV += MOZBUILD_STATE_PATH=$(BUILD_DIR)/mozbuild

CONFIGURE_OPTIONS=

# clang or gcc
CC_TYPE = gcc
COMPILER.gcc= gcc
COMPILER.clang= clang
COMPILER = $(COMPILER.$(CC_TYPE))

CXXFLAGS += -Wno-invalid-offsetof -fpermissive
CXXFLAGS += -std=c++17
# type problem compiling ffvpx with clang 
CFLAGS += -D__int8_t_defined

FIREFOX_LIBDIR =        $(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_PRE_CONFIGURE_ACTION += \
        rm -f  $(MOZCONFIG); \
        echo "ac_add_options --enable-application=js" >> $(MOZCONFIG) ; \
        echo "ac_add_options PKG_CONFIG=/usr/bin/amd64/pkg-config" >> $(MOZCONFIG) ; \
        echo "ac_add_options CC_TYPE=$(CC_TYPE)" >> $(MOZCONFIG) ; \
        echo "ac_add_options CC=$(CC)" >> $(MOZCONFIG) ; \
        echo "ac_add_options CXX=$(CXX)" >> $(MOZCONFIG) ; \
        echo "ac_add_options --prefix=/usr" >> $(MOZCONFIG) ; \
        echo "ac_add_options --libdir=$(USRLIBDIR64)" >> $(MOZCONFIG) ; \
        echo "ac_add_options --enable-release" >> $(MOZCONFIG) ; \
        echo "ac_add_options --libdir=$(FIREFOX_LIBDIR)" >> $(MOZCONFIG) ; \
        echo "ac_add_options --enable-install-strip" >> $(MOZCONFIG_DEBUG) ; \
        echo "ac_add_options --disable-tests" >> $(MOZCONFIG) ; \
        echo "ac_add_options --disable-jemalloc" >> $(MOZCONFIG) ; \
        echo "ac_add_options --enable-ctypes" >> $(MOZCONFIG) ; \
        echo "ac_add_options --with-intl-api" >> $(MOZCONFIG) ; \
        echo "ac_add_options --host=$(GNU_ARCH)" >> $(MOZCONFIG) ; \
        echo "ac_add_options --target=$(GNU_ARCH)" >> $(MOZCONFIG) ; \
        echo "ac_add_options --enable-system-ffi" >> $(MOZCONFIG) ; \
        echo "ac_add_options --with-system-nspr" >> $(MOZCONFIG) ; \
        echo "ac_add_options --with-system-zlib" >> $(MOZCONFIG) ; \
        echo "ac_add_options --enable-readline" >> $(MOZCONFIG) ; \
        echo "ac_add_options --enable-strip" >> $(MOZCONFIG) ; \
        echo "ac_add_options --enable-install-strip" >> $(MOZCONFIG) ; \
        echo "ac_add_options --enable-shared-js" >> $(MOZCONFIG) ; \

#       echo "ac_add_options --with-system-icu" >> $(MOZCONFIG) ; \
LD_SECEXT_OPTIONS += $(SSBD_ENABLE)

# 28395728
LD_MAP_NOEXBSS.sparc=

# rust dynamic library work around
LD_Z_IGNORE=

# hope to get args data in stacks of core dumps
LD_OPTIONS += -msave-args

# use a local installed rust since the system version may not be compatible
COMPONENT_PRE_CONFIGURE_ACTION += ( \
        export RUSTUP_HOME=$(RUSTUP_HOME); \
        export CARGO_HOME=$(CARGO_HOME); \
        export RUSTUP_INIT_SKIP_PATH_CHECK=yes; \
        export LD_LIBRARY_PATH=$(GCC_LIBDIR); \
        curl https://sh.rustup.rs -sSf | bash -s -- -y --no-modify-path; \
        source $(CARGO_HOME)/env; \
        rustup install $(RUST_VERSION); \
        rustup default $(RUST_VERSION)-x86_64-unknown-illumos; \
        rustup show; \
        cargo install --root=$(CARGO_HOME) --vers 0.28.0 cbindgen; \
        );

ENV += CC="$(CC)"
ENV += CFLAGS="$(CFLAGS)"
ENV += CXXFLAGS="$(CXXFLAGS)"
ENV += PKG_CONFIG=/usr/bin/amd64/pkg-config
ENV += RUSTUP_HOME=$(RUSTUP_HOME)
ENV += CARGO_HOME=$(CARGO_HOME)

# This is needed to run bins/libs in .rustup
ENV += LD_LIBRARY_PATH=$(GCC_LIBDIR)

COMPONENT_BUILD_ARGS += $(JOBS:%=-j%)

CONFIGURE_ENV = $(ENV)
COMPONENT_BUILD_ENV =   $(ENV)
COMPONENT_INSTALL_ENV += HOME=/tmp

CONFIGURE_ENV += PYTHON3="$(PYTHON)"
CONFIGURE_ENV += LDSHARED="$(CC) -shared"
CONFIGURE_ENV += NSPR_CONFIG="/usr/bin/pkg-config nspr"


COMPONENT_POST_BUILD_ACTION = \
        (cd $(@D)/browser/installer ; $(ENV) $(COMPONENT_BUILD_ENV) \
                $(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

COMPONENT_TEST_DIR =    $(@D)/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS = \
        '-e "/^PASSED ALL/,/Failed:/p" ' \
        '-e "/^FAILURES:/,/Failed:/p" ' \
        '-e "/.*/d" '

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/psutil
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/build/autoconf-213
REQUIRED_PACKAGES += developer/lang/rustc
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/http-parser
REQUIRED_PACKAGES += runtime/nodejs-24
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += web/browser/lynx

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
