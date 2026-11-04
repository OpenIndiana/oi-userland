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
BUILD_STYLE=		cargo
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkg6depotd
HUMAN_VERSION=		1.0.0
COMPONENT_VERSION=	1.0.0
COMPONENT_REVISION=	0
COMPONENT_SUMMARY=	pkg6 IPS repository depot server and operator tools
COMPONENT_DESCRIPTION=	pkg6depotd serves IPS package repositories to pkg(1) clients over the pkg5 depot protocol, with a web interface for browsing and searching packages. Includes the SMF service svc:/application/pkg/pkg6depotd and the local repository tools pkg6repo and pkg6recv.
COMPONENT_PROJECT_URL=	https://code.aopc.cloud/OpenIndiana/ips
COMPONENT_FMRI=		package/pkg6/depotd
COMPONENT_CLASSIFICATION=	System/Packaging
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ee083a0f00a877f25e588b090e6178c6e71a43e1fe513fd3f4c99de7c093a0ad
COMPONENT_ARCHIVE_URL=	https://static.crates.io/crates/pkg6depotd/$(COMPONENT_SRC).crate

COMPONENT_SRC_1=	pkg6repo-$(HUMAN_VERSION)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:044e7099eaf8fe23f76a4295bcab7bdaf3d1a33b33c379e29509f79ea4c8d674
COMPONENT_ARCHIVE_URL_1= https://static.crates.io/crates/pkg6repo/$(COMPONENT_SRC_1).crate

COMPONENT_SRC_2=	pkg6recv-$(HUMAN_VERSION)
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_HASH_2= sha256:7422b95ff50ec689d8d6a9136aee105340f585bb0b1281c06ea3a19b71ad0aae
COMPONENT_ARCHIVE_URL_2= https://static.crates.io/crates/pkg6recv/$(COMPONENT_SRC_2).crate

COMPONENT_LICENSE=	MPL-2.0
COMPONENT_LICENSE_FILE=	LICENSE

# The upstream test suite needs cargo-nextest (per-test process isolation)
# and loopback listeners; it runs in the upstream CI and release gates.
TEST_TARGET=		$(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

# Assemble the three published crates into one build workspace. Packaging files
# in files/ are unchanged from upstream v1.0.0 (dc8e5e0f91ea).
$(SOURCE_DIR)/.unpacked: $(SOURCE_DIR_1)/.unpacked $(SOURCE_DIR_2)/.unpacked
COMPONENT_POST_UNPACK_ACTION = \
	$(CP) -rp $(SOURCE_DIR_1) $(SOURCE_DIR)/pkg6repo && \
	$(CP) -rp $(SOURCE_DIR_2) $(SOURCE_DIR)/pkg6recv && \
	printf '\n[workspace]\nmembers = ["pkg6repo", "pkg6recv"]\n' >> $(SOURCE_DIR)/Cargo.toml && \
	$(CP) $(COMPONENT_DIR)/files/Cargo.lock $(SOURCE_DIR)/Cargo.lock

# A Cargo workspace: build only the shipped binaries.
COMPONENT_BUILD_ARGS +=	--locked
COMPONENT_BUILD_ARGS +=	-p pkg6depotd -p pkg6repo -p pkg6recv
# Pin the target directory: a cargo config.toml in a parent directory of the
# workspace (as on the CI builders) may otherwise move it.
COMPONENT_BUILD_ARGS +=	--target-dir $(BUILD_DIR_64)/target

# cargo install cannot install from a virtual workspace manifest, so stage
# the built binaries and the upstream service, configuration and manual
# page files directly.
COMPONENT_INSTALL_CMD =	$(TRUE)
COMPONENT_INSTALL_ARGS =
CARGO_RELEASE_DIR =	$(BUILD_DIR_64)/target/release
PKG6_PACKAGING =	$(COMPONENT_DIR)/files

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRBINDIR) $(PROTOUSRLIBDIR) \
	    $(PROTOETCDIR)/pkg6depotd \
	    $(PROTO_DIR)/lib/svc/manifest/application/pkg \
	    $(PROTO_DIR)/lib/svc/method \
	    $(PROTOUSRSHAREMANDIR)/man1 $(PROTOUSRSHAREMANDIR)/man5 \
	    $(PROTOUSRSHAREMANDIR)/man8 ; \
	$(INSTALL) -m 0555 $(CARGO_RELEASE_DIR)/pkg6depotd $(PROTOUSRLIBDIR)/pkg6depotd ; \
	$(INSTALL) -m 0555 $(CARGO_RELEASE_DIR)/pkg6repo $(PROTOUSRBINDIR)/pkg6repo ; \
	$(INSTALL) -m 0555 $(CARGO_RELEASE_DIR)/pkg6recv $(PROTOUSRBINDIR)/pkg6recv ; \
	$(INSTALL) -m 0644 $(PKG6_PACKAGING)/pkg6depotd.kdl $(PROTOETCDIR)/pkg6depotd/pkg6depotd.kdl ; \
	$(INSTALL) -m 0444 $(PKG6_PACKAGING)/pkg6depotd.xml $(PROTO_DIR)/lib/svc/manifest/application/pkg/pkg6depotd.xml ; \
	$(INSTALL) -m 0555 $(PKG6_PACKAGING)/svc-pkg6depotd $(PROTO_DIR)/lib/svc/method/svc-pkg6depotd ; \
	$(INSTALL) -m 0444 $(SOURCE_DIR)/pkg6repo/pkg6repo.1 $(PROTOUSRSHAREMANDIR)/man1/pkg6repo.1 ; \
	$(INSTALL) -m 0444 $(PKG6_PACKAGING)/pkg6-policy.5 $(PROTOUSRSHAREMANDIR)/man5/pkg6-policy.5 ; \
	$(INSTALL) -m 0444 $(PKG6_PACKAGING)/pkg6depotd.8 $(PROTOUSRSHAREMANDIR)/man8/pkg6depotd.8 ; \
	$(INSTALL) -m 0444 $(PKG6_PACKAGING)/pkg6repo-retire.8 $(PROTOUSRSHAREMANDIR)/man8/pkg6repo-retire.8 ;

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
