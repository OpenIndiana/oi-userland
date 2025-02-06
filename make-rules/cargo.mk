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
# Copyright 2024 Marcel Telka
#

#
# cargo build style
#
# Cargo is the Rust package manager used to download, compile, and install Rust
# packages and their dependencies.
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

# Common cargo environment
CARGO_ENV += CARGO_HOME=$(@D)/.cargo
CARGO_ENV += CARGO_TARGET_$(shell echo $(RUST_TRIPLET) | $(TR) '[a-z]-' '[A-Z]_')_LINKER=$(CARGO_TARGET_LINKER)
CARGO_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# Configure
# Some tests fails with the default symlink cloney mode
CLONEY_MODE = copy
COMPONENT_CONFIGURE_ACTION = true

# Build
COMPONENT_BUILD_CMD = $(CARGO) build
COMPONENT_BUILD_ARGS += --release
COMPONENT_BUILD_ARGS += --offline
COMPONENT_BUILD_ENV += $(CARGO_ENV)

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# Install
COMPONENT_INSTALL_CMD = $(CARGO) install
COMPONENT_INSTALL_ARGS += --path .
COMPONENT_INSTALL_ARGS += --root $(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS += --force
COMPONENT_INSTALL_ARGS += --no-track
COMPONENT_INSTALL_ARGS += --offline
COMPONENT_INSTALL_ARGS += --locked
# this is needed to override the default set in shared-macros.mk
COMPONENT_INSTALL_TARGETS =
COMPONENT_INSTALL_ENV += $(CARGO_ENV)

# Test
COMPONENT_TEST_CMD = $(CARGO) test
COMPONENT_TEST_ARGS += --release
COMPONENT_TEST_ARGS += --offline
COMPONENT_TEST_TARGETS =
COMPONENT_TEST_ENV += $(CARGO_ENV)

# drop header
COMPONENT_TEST_TRANSFORMS += "-e '0,/Finished/d'"
# remove timing
COMPONENT_TEST_TRANSFORMS += "-e 's/\(finished\) in [0-9]\{1,\}\.[0-9]\{2\}s\$$/\1/g'"
# sort tests
COMPONENT_TEST_TRANSFORMS += "| ( while true ; do \
		$(GSED) -u -e '/^running [0-9]\{1,\} tests\$$/q1' && break ; \
		$(GSED) -u -e '/^\$$/Q' | $(SORT) ; \
		echo "" ; \
	done ) | $(COMPONENT_TEST_TRANSFORMER) -e ''"

# Cleanup
clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)

# Use common rules
USE_COMMON_RULES = yes
