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
# Copyright 2026 Till Wegmueller
#

BUILD_BITS=		64
BUILD_STYLE=		justmake
# Vendor the Cargo dependencies at the patch step (make-rules/cargo-vendor.mk).
CARGO_VENDOR=		yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkg6depotd
HUMAN_VERSION=		1.0.2
COMPONENT_VERSION=	$(HUMAN_VERSION)
COMPONENT_SUMMARY=	pkg6 IPS repository depot server and operator tools
COMPONENT_DESCRIPTION=	pkg6depotd serves IPS package repositories to pkg(1) clients over the pkg5 depot protocol, with a web interface for browsing and searching packages. Includes the SMF service svc:/application/pkg/pkg6depotd and the local repository tools pkg6repo and pkg6recv.
COMPONENT_PROJECT_URL=	https://code.aopc.cloud/OpenIndiana/ips
COMPONENT_FMRI=		package/pkg6/depotd
COMPONENT_CLASSIFICATION=	System/Packaging
COMPONENT_LICENSE=	MPL-2.0
COMPONENT_LICENSE_FILE=	LICENSE

# The upstream Cargo workspace; its GNU Makefile builds and installs the
# release binaries, SMF service, configuration and manual pages.
GIT_REPO=		https://code.aopc.cloud/OpenIndiana/ips.git
GIT_BRANCH=		v$(HUMAN_VERSION)
GIT_COMMIT_ID=		9daf7335ca8762bbfa54a9d3c48d9e586b3137c1
GIT_HASH=		sha256:1a8f64ed65867f2d8e0bfc06ea874550d688ece0f91e559e9c137c0c51b0a1ae
COMPONENT_SRC=		ips-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=

# The upstream test suite needs cargo-nextest (per-test process isolation)
# and loopback listeners; it runs in the upstream CI and release gates.
TEST_TARGET=		$(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

# The git source rule writes the archive without creating the archives
# directory; a fresh workspace (CI) has none.
$(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE): | $(USERLAND_ARCHIVES)

CLONEY_MODE=		copy

PKG6_MAKE_ARGS =	CARGO=$(CARGO) CARGO_FLAGS="--locked --offline"
PKG6_MAKE_ARGS +=	prefix=$(USRDIR) INSTALL=$(INSTALL)
COMPONENT_BUILD_ARGS +=	$(PKG6_MAKE_ARGS)
COMPONENT_INSTALL_ARGS += $(PKG6_MAKE_ARGS)

PKG6_CARGO_ENV =	CARGO_TARGET_$(shell echo $(RUST_TRIPLET) | $(TR) '[a-z]-' '[A-Z]_')_LINKER=$(CARGO_TARGET_LINKER)
PKG6_CARGO_ENV +=	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
COMPONENT_BUILD_ENV +=	$(PKG6_CARGO_ENV)
COMPONENT_INSTALL_ENV += $(PKG6_CARGO_ENV)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
