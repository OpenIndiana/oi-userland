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
# Copyright 2025 Marcel Telka
#

#
# Generic cargo vendor support
#
# To use it in a component set CARGO_VENDOR to yes before the common.mk
# include.
#
# To use it in a build style set CARGO_VENDOR to yes in the
# $(BUILD_STYLE)-defaults.mk file.  See cargo-defaults.mk for an example.
#

# Common Cargo home used as a cache for downloaded crates
CARGO_ARCHIVES ?= $(USERLAND_ARCHIVES)/.cargo

# The full path to the cargo binary.  It lives in the rustc package.
CARGO = /usr/bin/cargo
USERLAND_REQUIRED_PACKAGES += developer/lang/rustc

# Directory for vendored dependencies
CARGO_VENDOR_DIR = $(SOURCE_DIR)-cargo-vendor

# Directory with the Cargo.toml manifest
CARGO_TOML_DIR = $(SOURCE_DIR)$(COMPONENT_SUBDIR:%=/%)$(CARGO_TOML_SUBDIR:%=/%)

# Directory with the config.toml file we are about to create
CARGO_CONFIG_DIR = $(SOURCE_DIR)$(COMPONENT_SUBDIR:%=/%)/.cargo

# Cargo.toml is available only after we unpack sources
$(CARGO_TOML_DIR)/Cargo.toml: unpack

# Download all dependencies
$(SOURCE_DIR)/.cargo-fetched: $(CARGO_TOML_DIR)/Cargo.toml
	$(ENV) CARGO_HOME=$(CARGO_ARCHIVES) \
		$(CARGO) fetch --manifest-path $(CARGO_TOML_DIR)/Cargo.toml
	$(TOUCH) $@

# Vendor all dependencies locally
$(SOURCE_DIR)/.cargo-vendored: $(SOURCE_DIR)/.cargo-fetched $(CARGO_TOML_DIR)/Cargo.toml
	$(RM) -r $(CARGO_VENDOR_DIR)
	$(RM) -r $(CARGO_CONFIG_DIR) ; $(MKDIR) $(CARGO_CONFIG_DIR)
	$(ENV) CARGO_HOME=$(CARGO_ARCHIVES) \
		$(CARGO) vendor --manifest-path $(CARGO_TOML_DIR)/Cargo.toml \
			--versioned-dirs --offline $(CARGO_VENDOR_DIR) \
		| $(TEE) $(CARGO_CONFIG_DIR)/config.toml
	$(TOUCH) $@

# Vendor Cargo dependencies during the patch step
patch:: $(SOURCE_DIR)/.cargo-vendored

#
# Few convenient targets.
#
# Please note that the cargo-patch target will be enhanced below to do the
# actual patching (if we do have any cargo vendor patches).
#
cargo-fetch: $(SOURCE_DIR)/.cargo-fetched
cargo-vendor: $(SOURCE_DIR)/.cargo-vendored
cargo-patch: cargo-vendor

.PHONY: cargo-fetch cargo-vendor cargo-patch

# Apply patches (if any) to vendored dependencies (we need to set
# SOURCE_DIR_cargo before we include the prep.mk file)
SOURCE_DIR_cargo = $(CARGO_VENDOR_DIR)

# Include prep.mk.  See common.mk for more details.
include $(WS_MAKE_RULES)/prep.mk

ifneq ($(strip $(PATCHES)),)
# If we do have some generic patches then Cargo.toml is available only after we
# patch sources
$(CARGO_TOML_DIR)/Cargo.toml: $(SOURCE_DIR)/.patched
endif

# Patching of vendored sources needs additional care
ifneq ($(strip $(PATCHES_cargo)),)
# Force zero patch level to root patches into $(CARGO_VENDOR_DIR)
$(SOURCE_DIR_cargo)/.patched: PATCH_LEVEL = 0

#
# Vendored sources are considered read-only by Cargo and so should not be
# modified.  Since we need to patch them we need to fool Cargo to do not check
# vendored checksums.
#
# See also https://github.com/rust-lang/cargo/issues/11063
#
$(SOURCE_DIR_cargo)/.patched: $(SOURCE_DIR_cargo)/.cargo-checksum
$(SOURCE_DIR_cargo)/.cargo-checksum: $(SOURCE_DIR)/.cargo-vendored
	$(FIND) $(@D) -name .cargo-checksum.json \
		  -exec $(GSED) -i -e 's/\("files":{\)[^}]*}/\1 }/' '{}' '+'
	$(TOUCH) $@

# Make sure we patch vendored sources only after they are actually vendored
$(PATCH_STAMPS_cargo): $(SOURCE_DIR)/.cargo-vendored

# Additional prerequisite for the cargo-patch target
cargo-patch: $(SOURCE_DIR_cargo)/.patched
endif

# Cleanup
CLEAN_PATHS += $(CARGO_VENDOR_DIR)

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=
