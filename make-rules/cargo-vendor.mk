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
# To use it in a build style set CARGO_VENDOR to yes anywhere in the build
# style .mk file.  See cargo.mk for an example.
#

# Common Cargo home used as a cache for downloaded crates
CARGO_ARCHIVES ?= $(USERLAND_ARCHIVES)/.cargo

# The full path to the cargo binary.  It lives in the rustc package.
CARGO = /usr/bin/cargo
USERLAND_REQUIRED_PACKAGES += developer/lang/rustc

# Fetch all dependencies and vendor them locally
CARGO_VENDOR_DIR = $(BUILD_DIR)/cargo-vendor
COMPONENT_PREP_ACTION += [ -f $(SOURCE_DIR)/Cargo.toml ] || exit 1 ;
COMPONENT_PREP_ACTION += $(ENV) CARGO_HOME=$(CARGO_ARCHIVES) \
	$(CARGO) fetch --manifest-path $(SOURCE_DIR)/Cargo.toml || exit 1 ;
COMPONENT_PREP_ACTION += $(MKDIR) $(SOURCE_DIR)/.cargo ;
COMPONENT_PREP_ACTION += $(ENV) CARGO_HOME=$(CARGO_ARCHIVES) \
	$(CARGO) vendor --manifest-path $(SOURCE_DIR)/Cargo.toml \
		--versioned-dirs --offline $(CARGO_VENDOR_DIR) \
	| $(TEE) $(SOURCE_DIR)/.cargo/config.toml ;

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=
