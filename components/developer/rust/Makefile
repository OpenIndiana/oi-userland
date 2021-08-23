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
# Copyright 2018, cgrzemba@opencsw.org
# Copyright 2018, Aurelien Larcher
# Copyright 2018, Michal Nowak
# Copyright 2021, Carsten Grzemba
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rustc
COMPONENT_VERSION=	1.44.1
COMPONENT_FMRI=		developer/lang/rustc
COMPONENT_SUMMARY=	Rust - Safe, concurrent, practical language
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_PROJECT_URL=	http://www.rust-lang.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:7e2e64cb298dd5d5aea52eafe943ba0458fa82f2987fdcda1ff6f537b6f88473
COMPONENT_ARCHIVE_URL=	https://static.rust-lang.org/dist/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT or Apache-2.0

RUST_STAGE0_VER=        1.44.1
RUST_ARCH:=             x86_64-sun-solaris

COMPONENT_NAME_1=	rust
COMPONENT_VERSION_1=	$(RUST_STAGE0_VER)
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)-$(RUST_ARCH)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1=	sha256:d203192453e132d41d32f32a70c2c6785515a7f43d2bd71a2b95ddfbd971f6f4
COMPONENT_ARCHIVE_URL_1=	https://us-east.manta.joyent.com/pkgsrc/public/pkg-bootstraps/$(COMPONENT_ARCHIVE_1)

SOURCE_DIR_1=		$(COMPONENT_DIR)/$(COMPONENT_SRC_1)
RUST_BOOTSTRAP_PATH=	$(SOURCE_DIR_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# GCC_VERSION =  7

PATH=$(GCC_BINDIR):$(PATH.gnu)

# Need some help to pick the correct ar binary
GNUAR=$(GNUBIN)/ar

# getpwuid_r failure
CXXFLAGS += -D_POSIX_PTHREAD_SEMANTICS
CFLAGS += -D_POSIX_PTHREAD_SEMANTICS

# Add arch triplet to pkg macros
PKG_MACROS+= RUST_ARCH="$(RUST_ARCH)"

#  workaround the symlink name lenght 100 problem, but hope it is not neccessary with
# but also with patch src_tools_rust-installer_src_generator.rs.patch 
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D); \
 	cd $(@D) ; \
 	$(COMPONENT_DIR)/files/sym2hard.py ; )

# Put the bits cargo downloads in a private directory.  This could be cached
# somewhere more permanent, but it's important to make sure that a person's
# $HOME/.cargo isn't used.
COMPONENT_BUILD_ENV +=	CARGO_HOME=$(BUILD_DIR)/.cargo
COMPONENT_INSTALL_ENV +=	CARGO_HOME=$(BUILD_DIR)/.cargo
COMPONENT_TEST_ENV += CARGO_HOME=$(BUILD_DIR)/.cargo

# Rust expects the library path to be /usr/lib and is broken otherwise 
RUSTC_LIBDIR= $(USRLIBDIR)
CLANG_ROOT= /usr/clang/9.0

CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(RUSTC_LIBDIR)
CONFIGURE_OPTIONS += --docdir=$(USRSHAREDOCDIR)/rust-$(COMPONENT_VERSION)
CONFIGURE_OPTIONS += --infodir=$(USRSHAREDIR)/info
CONFIGURE_OPTIONS += --datadir=$(USRSHAREDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --local-rust-root=$(RUST_BOOTSTRAP_PATH)
CONFIGURE_OPTIONS += --enable-extended       # Build and install cargo too.
CONFIGURE_OPTIONS += --default-linker=$(CC)
CONFIGURE_OPTIONS += --set rust.default-linker=$(CC)
CONFIGURE_OPTIONS += --set target.$(RUST_ARCH).cc=$(CC)
CONFIGURE_OPTIONS += --set target.$(RUST_ARCH).cxx=$(CXX)
CONFIGURE_OPTIONS += --set target.$(RUST_ARCH).ar=$(GNUAR)
CONFIGURE_OPTIONS += --set target.$(RUST_ARCH).linker=$(CC)
CONFIGURE_OPTIONS += --enable-rpath
CONFIGURE_OPTIONS += --disable-codegen-tests
CONFIGURE_OPTIONS += --disable-dist-src
CONFIGURE_OPTIONS += --disable-llvm-static-stdcpp
CONFIGURE_OPTIONS += --enable-ninja
CONFIGURE_OPTIONS += --enable-vendor
CONFIGURE_OPTIONS += --disable-docs
CONFIGURE_OPTIONS += --disable-compiler-docs
CONFIGURE_OPTIONS += --release-channel=stable
CONFIGURE_OPTIONS += --python=$(PYTHON)
CONFIGURE_OPTIONS += --enable-llvm-link-shared
CONFIGURE_OPTIONS += --llvm-root=$(CLANG_ROOT)

# Cleanup standard environment!
COMPONENT_BUILD_ENV =
COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CXX=$(CXX)
COMPONENT_BUILD_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ENV += AR=$(GNUAR)
COMPONENT_BUILD_ENV += RUSTC=$(RUST_BOOTSTRAP_PATH)/bin/rustc
# Enforce linker consistency
COMPONENT_BUILD_ENV += RUSTFLAGS="-C linker=$(CC)"
COMPONENT_BUILD_ENV += RUST_BACKTRACE=1

GMAKE = $(PYTHON)
COMPONENT_BUILD_GMAKE_ARGS = 
COMPONENT_BUILD_TARGETS = build
COMPONENT_BUILD_ARGS = ./x.py -v -v -v -v

COMPONENT_INSTALL_ARGS = ./x.py -v -v -v
# Cleanup standard environment
COMPONENT_INSTALL_ENV = 
COMPONENT_INSTALL_ENV += $(COMPONENT_BUILD_ENV)
# Set install path
COMPONENT_INSTALL_ENV += DESTDIR=$(PROTO_DIR)

COMPONENT_PRE_INSTALL_ACTION = mkdir -p $(PROTO_DIR)

RUSTC_BIN_POST = cargo
RUSTC_BIN_POST+= clippy-driver
RUSTC_BIN_POST+= rls
RUSTC_BIN_POST+= rustc
RUSTC_BIN_POST+= rustdoc

RUSTC_DRIVER_HASH=637b1017ef7a0c2f
# Create symlinks in place of copies to generate proper link actions
# Edit runpath so that libraries are resolved both in the proto area and system-wide
COMPONENT_POST_INSTALL_ACTION= \
  ( $(RM) $(PROTOUSRLIBDIR)/*.so; \
    $(MKDIR) $(PROTOUSRLIBDIR.$(BITS)); \
    $(RM) $(PROTOUSRLIBDIR.$(BITS))/*.so; \
    cp $(@D)/build/$(RUST_ARCH)/stage2/lib/rustlib/$(RUST_ARCH)/lib/librustc_driver-$(RUSTC_DRIVER_HASH).so $(PROTOUSRLIBDIR)/rustlib/$(RUST_ARCH)/lib/ ; \
    cd $(PROTOUSRLIBDIR.$(BITS)); \
    $(LN) -s ../rustlib/$(RUST_ARCH)/lib/*.so .; \
    for file in $(RUSTC_BIN_POST); \
    do \
      /usr/bin/elfedit -e \
        'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$$ORIGIN/../lib/rustlib/$(RUST_ARCH)/lib:$$ORIGIN/../lib/$(MACH64)"' \
        $(PROTOUSRBINDIR)/$$file ; \
      /usr/bin/elfedit -e \
        'dyn:value -s  RPATH   "$(GCC_LIBDIR):$$ORIGIN/../lib/rustlib/$(RUST_ARCH)/lib:$$ORIGIN/../lib/$(MACH64)"' \
        $(PROTOUSRBINDIR)/$$file ; \
    done; \
    for file in $(PROTOUSRLIBDIR)/rustlib/$(RUST_ARCH)/lib/*.so; \
    do \
      /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$$ORIGIN:$$ORIGIN/../../$(MACH64)"' $$file ; \
      /usr/bin/elfedit -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR):$$ORIGIN:$$ORIGIN/../../$(MACH64)"' $$file ; \
    done; \
    /usr/bin/elfedit -e 'dyn:value -s RUNPATH "$(GCC_LIBDIR):$$ORIGIN:$$ORIGIN/../../$(MACH64):/usr/clang/9.0/lib"' $(PROTOUSRLIBDIR)/rustlib/$(RUST_ARCH)/lib/librustc_driver-$(RUSTC_DRIVER_HASH).so; \
    /usr/bin/elfedit -e 'dyn:value -s RPATH "$(GCC_LIBDIR):$$ORIGIN:$$ORIGIN/../../$(MACH64):/usr/clang/9.0/lib"' $(PROTOUSRLIBDIR)/rustlib/$(RUST_ARCH)/lib/librustc_driver-$(RUSTC_DRIVER_HASH).so; \
  )

build:		$(BUILD_64)

install:	$(INSTALL_64)

# Build dependencies (make sure completions are installed)
REQUIRED_PACKAGES += utility/bash-completion
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += developer/clang-90
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/http-parser
# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
