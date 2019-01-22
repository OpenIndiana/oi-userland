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
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rustc
COMPONENT_VERSION=	1.32.0
COMPONENT_FMRI=		developer/lang/rustc
COMPONENT_SUMMARY=	Rust - Safe, concurrent, practical language
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_PROJECT_URL=	http://www.rust-lang.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:4c594c7712a0e7e8eae6526c464bf6ea1d82f77b4f61717c3fc28fb27ba2224a
COMPONENT_ARCHIVE_URL=	https://static.rust-lang.org/dist/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT or Apache-2.0

RUST_STAGE0_VER=        1.32.0
RUST_ARCH:=             x86_64-sun-solaris

COMPONENT_NAME_1=	rust
COMPONENT_VERSION_1=	$(RUST_STAGE0_VER)
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)-$(RUST_ARCH)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1=	sha256:689586af4297df329884239f5e82b09ac3f8ac9f425ffcbfdb5382b1c7465496
COMPONENT_ARCHIVE_URL_1=	https://us-east.manta.joyent.com/pkgsrc/public/pkg-bootstraps/$(COMPONENT_ARCHIVE_1)

SOURCE_DIR_1=		$(COMPONENT_DIR)/$(COMPONENT_SRC_1)
RUST_BOOTSTRAP_PATH=	$(SOURCE_DIR_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(GCC_BINDIR):$(PATH.gnu)

PATCH_LEVEL=0

# Need some help to pick the correct ar binary
GNUAR=$(GNUBIN)/ar

# getpwuid_r failure
CFLAGS   +=	-D_POSIX_PTHREAD_SEMANTICS
CXXFLAGS +=	-D_POSIX_PTHREAD_SEMANTICS

# Add arch triplet to pkg macros
PKG_MACROS+= RUST_ARCH="$(RUST_ARCH)"

COMPONENT_PREP_ACTION = \
	$(GSED) -i -e 's/9c6af198a2f80da827054784faf70bc404673d9568fb45664b4f73c46245fdbd/c3851969a854d6ccaa8a94369f1288025149d1ebdc74b36f224423f35b18f7a7/' \
		$(SOURCE_DIR)/vendor/libc/.cargo-checksum.json; \
	$(GSED) -i -e 's/cb94a0b54e47022b2e9b58b45e0196785c61d083760333276226da435cc040d9/bcb195562cf830c9e2078757e6d0976f86ede59816ff305e21a2764a4a4cf43e/' \
		$(SOURCE_DIR)/vendor/rand/.cargo-checksum.json;

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Rust expects the library path to be /usr/lib and is broken otherwise 
RUSTC_LIBDIR= $(USRLIBDIR)

CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(RUSTC_LIBDIR)
CONFIGURE_OPTIONS += --docdir=$(USRSHAREDOCDIR)/rust-$(COMPONENT_VERSION)
CONFIGURE_OPTIONS += --infodir=$(USRSHAREDIR)/info
CONFIGURE_OPTIONS += --datadir=$(USRSHAREDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
# CONFIGURE_OPTIONS += --enable-local-rust
CONFIGURE_OPTIONS += --local-rust-root=$(RUST_BOOTSTRAP_PATH)
CONFIGURE_OPTIONS += --enable-extended       # Build and install cargo too.
# CONFIGURE_OPTIONS += --disable-libcpp
# CONFIGURE_OPTIONS += --enable-dist-host-only
# CONFIGURE_OPTIONS += --enable-ccache
# CONFIGURE_OPTIONS += --enable-sccache
# CONFIGURE_OPTIONS += --enable-clang
# Otherwise sunstudio 12.1 cc is default selected
CONFIGURE_OPTIONS += --default-linker=$(CC)
CONFIGURE_OPTIONS += --set rust.default-linker=$(CC)
# Need also to override target specific configuration variables
CONFIGURE_OPTIONS += --set target.$(RUST_ARCH).cc=$(CC)
CONFIGURE_OPTIONS += --set target.$(RUST_ARCH).cxx=$(CXX)
CONFIGURE_OPTIONS += --set target.$(RUST_ARCH).ar=$(GNUAR)
CONFIGURE_OPTIONS += --set target.$(RUST_ARCH).linker=$(CC)
# CONFIGURE_OPTIONS += --disable-rustbuild
CONFIGURE_OPTIONS += --enable-rpath
CONFIGURE_OPTIONS += --disable-codegen-tests
CONFIGURE_OPTIONS += --disable-dist-src
CONFIGURE_OPTIONS += --disable-llvm-static-stdcpp
CONFIGURE_OPTIONS += --disable-ninja
CONFIGURE_OPTIONS += --enable-vendor
CONFIGURE_OPTIONS += --disable-docs
CONFIGURE_OPTIONS += --release-channel=stable
CONFIGURE_OPTIONS += --python=$(PYTHON)

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
# rustc builds libs without any search path!
# We need to add the path to GCC runtime libraries
COMPONENT_BUILD_ENV += LD_LIBRARY_PATH=$(GCC_ROOT)/lib/$(MACH64):$(USRLIBDIR.$(BITS)):$(RUST_BOOTSTRAP_PATH)/lib

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

# Create symlinks in place of copies to generate proper link actions
# Edit runpath so that libraries are resolved both in the proto area and system-wide
COMPONENT_POST_INSTALL_ACTION= \
  ( $(RM) $(PROTOUSRLIBDIR)/*.so; \
    $(MKDIR) $(PROTOUSRLIBDIR.$(BITS)); \
    $(RM) $(PROTOUSRLIBDIR.$(BITS))/*.so; \
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
    done; )

build:		$(BUILD_64)

install:	$(INSTALL_64)

# Build dependencies (make sure completions are installed)
REQUIRED_PACKAGES += utility/bash-completion
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/http-parser
# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
