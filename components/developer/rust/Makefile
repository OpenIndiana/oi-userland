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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rustc
COMPONENT_VERSION=	1.23.0
COMPONENT_FMRI=	developer/lang/rustc
COMPONENT_SUMMARY=	Safe, concurrent, practical languag
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_PROJECT_URL=	http://www.rust-lang.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7464953871dcfdfa8afcc536916a686dd156a83339d8ec4d5cb4eb2fe146cb91
# 1.16    sha256:f966b31eb1cd9bd2df817c391a338eeb5b9253ae0a19bf8a11960c560f96e8b4
COMPONENT_ARCHIVE_URL=	http://static.rust-lang.org/dist/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT or Apache-2.0

RUST_STAGE0_VER=        1.22.1
RUST_ARCH:=             x86_64-sun-solaris

COMPONENT_NAME_1    = rust
COMPONENT_VERSION_1 = $(RUST_STAGE0_VER)
COMPONENT_SRC_1     = $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)-$(RUST_ARCH)
COMPONENT_ARCHIVE_1  = $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1 =	\
    sha256:e512206e0c5bce691421f88b2479d4930351468f1e81e901d46f58bee42f7400
COMPONENT_ARCHIVE_URL_1 = https://us-east.manta.joyent.com/pkgsrc/public/pkg-bootstraps/$(COMPONENT_ARCHIVE_1)

SOURCE_DIR_1	= $(COMPONENT_DIR)/$(COMPONENT_SRC_1)
RUST_BOOTSTRAP_PATH = $(SOURCE_DIR_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += CC=clang
CONFIGURE_ENV += CXX=clang++
# CONFIGURE_ENV += PATH=$(PATH)

CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
# CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --docdir=/usr/share/doc
CONFIGURE_OPTIONS += --infodir=/usr/share/info
CONFIGURE_OPTIONS += --datadir=/usr/share
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
# CONFIGURE_OPTIONS += --enable-local-rust
CONFIGURE_OPTIONS += --local-rust-root=$(RUST_BOOTSTRAP_PATH)
CONFIGURE_OPTIONS += --enable-extended       # Build and install cargo too.
# CONFIGURE_OPTIONS += --disable-libcpp
# CONFIGURE_OPTIONS += --enable-dist-host-only
# CONFIGURE_OPTIONS += --enable-ccache
# CONFIGURE_OPTIONS += --enable-sccache
# CONFIGURE_OPTIONS += --enable-clang
# CONFIGURE_OPTIONS += --default-linker=gcc
# CONFIGURE_OPTIONS += --disable-rustbuild
CONFIGURE_OPTIONS += --enable-rpath
CONFIGURE_OPTIONS += --disable-codegen-tests
CONFIGURE_OPTIONS += --disable-dist-src
CONFIGURE_OPTIONS += --disable-llvm-static-stdcpp
CONFIGURE_OPTIONS += --disable-ninja
CONFIGURE_OPTIONS += --enable-vendor
CONFIGURE_OPTIONS += --disable-docs
CONFIGURE_OPTIONS += --disable-jemalloc
CONFIGURE_OPTIONS += --release-channel=stable
CONFIGURE_OPTIONS += --python=$(PYTHON)
CONFIGURE_OPTIONS.$(BITS) += CCACHE_BASEDIR="$(BUILD_DIR_$(BITS))"
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

# cleanup standard enviroment!
COMPONENT_BUILD_ENV =
COMPONENT_BUILD_ENV += CC=gcc
COMPONENT_BUILD_ENV += RUSTC=$(RUST_BOOTSTRAP_PATH)/bin/rustc
COMPONENT_BUILD_ENV += RUSTFLAGS="-C linker=gcc"
COMPONENT_BUILD_ENV += RUST_BACKTRACE=1
# rustc builds libs without any search path!
COMPONENT_BUILD_ENV += LD_LIBRARY_PATH=$(CONFIGURE_LIBDIR.$(BITS)):$(RUST_BOOTSTRAP_PATH)/lib

GMAKE = $(PYTHON)
COMPONENT_BUILD_GMAKE_ARGS = 
COMPONENT_BUILD_TARGETS = dist
COMPONENT_BUILD_ARGS = ./x.py -v -v -v -v

COMPONENT_INSTALL_ARGS = ./x.py -v -v -v
# cleanup istandard environemnt
COMPONENT_INSTALL_ENV = 
COMPONENT_INSTALL_ENV += $(COMPONENT_BUILD_ENV)
# set install path
COMPONENT_INSTALL_ENV += DESTDIR=$(PROTO_DIR)

COMPONENT_PRE_INSTALL_ACTION = \
	mkdir -p $(PROTO_DIR)

build: $(BUILD_64)

install: $(INSTALL_64)

REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
