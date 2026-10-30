#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 Till Wegmueller
#

BUILD_STYLE = archive
BUILD_BITS = 64
GCC_VERSION = 14
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME = illumos-drm
COMPONENT_VERSION = 0.0.2
COMPONENT_SUMMARY = Native illumos DRM stack
COMPONENT_PROJECT_URL = https://code.aopc.cloud/illumos/illumos-drm
COMPONENT_CLASSIFICATION = Drivers/Display
COMPONENT_SRC = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE = $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL = https://code.aopc.cloud/illumos/illumos-drm/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH = sha256:d7f48a67b879cd48a9cff07c81a579fd44119d63b8adc66d9fe4165098f9302b
COMPONENT_LICENSE = MPL-2.0, MIT
COMPONENT_LICENSE_FILE = LICENSE

COMPONENT_SRC_1 = linux-7.2
COMPONENT_ARCHIVE_1 = linux-7.2.tar.xz
COMPONENT_ARCHIVE_URL_1 = https://cdn.kernel.org/pub/linux/kernel/v7.x/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1 = sha256:f9fef3d14c0df53819026f4be74459835c2a0b0dcbf5b5bbd9ea19f0829402b3

ILLUMOS_DDI_VERSION = 0.0.1
COMPONENT_ARCHIVE_2 = illumos-ddi-$(ILLUMOS_DDI_VERSION).tar.gz
COMPONENT_ARCHIVE_URL_2 = https://code.aopc.cloud/illumos/illumos-ddi/releases/download/v$(ILLUMOS_DDI_VERSION)/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2 = sha256:888af83d91f4a2e514f7b0460b01f4fac54edfb3147b355974187774fdfceb2a

# The DDI mapfile is an upstream link-editor input, not a generated scratch
# file. Pin it to the same gate revision as the illumos-ddi bindings.
COMPONENT_ARCHIVE_3 = illumos-ddi-cda5b9a49f.mapfile
COMPONENT_ARCHIVE_URL_3 = https://raw.githubusercontent.com/illumos/illumos-gate/cda5b9a49f77a86a151a20cdde0e948a49b37160/usr/src/uts/common/mapfiles/ddi.mapfile
COMPONENT_ARCHIVE_HASH_3 = sha256:e54803cdfbe4f9e2877594489971e24201cff4f8ba05085f7f55bb3bec8af080

# libdrm 2.4.134 uAPI headers, also used when the installed header-drm is
# older. The C facade and its CTF shadow need precisely these two headers.
COMPONENT_ARCHIVE_4 = gfx-drm-e95220c-drm.h
COMPONENT_ARCHIVE_URL_4 = https://raw.githubusercontent.com/OpenIndiana/gfx-drm/e95220c/usr/src/uts/common/drm/drm.h
COMPONENT_ARCHIVE_HASH_4 = sha256:2d066b9fdd2e9a5b14537eb676b21b1ae79bc53d0830c7f2b3ac6f0aae38806b
COMPONENT_ARCHIVE_5 = gfx-drm-e95220c-drm_mode.h
COMPONENT_ARCHIVE_URL_5 = https://raw.githubusercontent.com/OpenIndiana/gfx-drm/e95220c/usr/src/uts/common/drm/drm_mode.h
COMPONENT_ARCHIVE_HASH_5 = sha256:ee4068c026dfb6c85c668cb4e41ff9cbf30e99c10c5e7ef2ad1c7870d3f9a3bf

RUSTC = /usr/bin/rustc
CARGO = /usr/bin/cargo
RUST_SRC = /usr/lib/rustlib/src/rust/library
VENDOR_DIR = $(COMPONENT_DIR)/vendor
BUILD_OUT = $(BUILD_DIR)/amd64
TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# As with cargo-vendor.mk, replace both crates.io and git sources with
# checksummed directory sources. Fetch here rather than at build time;
# the git dependency comes from its pinned archive, never a mutable branch.
download:: $(COMPONENT_DIR)/.vendor-ready
$(COMPONENT_DIR)/.vendor-ready: $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_2) vendor.py
	/usr/bin/python3.13 vendor.py $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) \
	    $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_2) $(USERLAND_ARCHIVES) $(VENDOR_DIR)
	$(TOUCH) $@

COMPONENT_PREP_ACTION = /usr/bin/bash $(COMPONENT_DIR)/prepare.sh \
    $(SOURCE_DIR) $(SOURCE_DIR_1) $(BUILD_OUT) $(USERLAND_ARCHIVES) $(VENDOR_DIR) $(RUST_SRC)

$(SOURCE_DIR)/.prep: $(COMPONENT_DIR)/.vendor-ready prepare.sh

$(BUILD_OUT)/.built: $(SOURCE_DIR)/.prep build.sh
	$(MKDIR) $(BUILD_OUT)/tmp
	cd $(SOURCE_DIR) && $(ENV) TMPDIR=$(BUILD_OUT)/tmp \
	    CC=$(CC) LD=/usr/bin/ld JOBS=2 RUSTC=$(RUSTC) CARGO=$(CARGO) \
	    CARGO_HOME=$(BUILD_OUT)/cargo-home CARGO_TARGET_DIR=$(BUILD_OUT)/target \
	    SYSINC=$(BUILD_OUT)/sysinc DDI_MAPFILE=$(BUILD_OUT)/ddi.mapfile \
	    LINUX=$(SOURCE_DIR_1) /usr/bin/bash $(COMPONENT_DIR)/build.sh $(BUILD_OUT)
	$(TOUCH) $@

$(BUILD_OUT)/.installed: $(BUILD_OUT)/.built install.sh
	/usr/bin/bash install.sh $(SOURCE_DIR) $(BUILD_OUT) $(PROTO_DIR)
	$(TOUCH) $@

build: $(BUILD_OUT)/.built
install: $(BUILD_OUT)/.installed
CLEAN_PATHS += $(BUILD_DIR) $(VENDOR_DIR) $(COMPONENT_DIR)/.vendor-ready

# Build requirements (no rustup or package installation by this recipe).
REQUIRED_PACKAGES += developer/build/onbld
REQUIRED_PACKAGES += developer/lang/rustc
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += runtime/python-313
REQUIRED_PACKAGES += system/header
REQUIRED_PACKAGES += system/header/header-drm
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
