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
# Copyright 2023 Till Wegmueller
#

# Allow overriding via environment and default to relying on PATH
PKGDEV ?= pkgdev

# Ensure Cargo-installed tools (e.g., pkgdev) are on PATH
PATH := $(PATH):$(HOME)/.cargo/bin
export PATH

.PHONY: generate-package-kdl

# Generate package.kdl using pkgdev with component metadata
generate-package-kdl:
	@compname="$(COMPONENT_NAME)"; \
	[ -z "$$compname" ] && compname="$$(/usr/bin/basename "$$PWD")"; \
	if [ -f "package.kdl" ]; then \
		echo "Skipping package.kdl generation for $$compname: package.kdl already exists"; \
		exit 0; \
	fi; \
	missing=""; \
	[ -z "$(COMPONENT_NAME)" ] && missing="$$missing COMPONENT_NAME"; \
	[ -z "$(COMPONENT_FMRI)" ] && missing="$$missing COMPONENT_FMRI"; \
	[ -z "$(COMPONENT_SUMMARY)" ] && missing="$$missing COMPONENT_SUMMARY"; \
	[ -z "$(COMPONENT_CLASSIFICATION)" ] && missing="$$missing COMPONENT_CLASSIFICATION"; \
	[ -z "$(COMPONENT_LICENSE)" ] && missing="$$missing COMPONENT_LICENSE"; \
	[ -z "$(COMPONENT_LICENSE_FILE)" ] && missing="$$missing COMPONENT_LICENSE_FILE"; \
	[ -z "$(COMPONENT_VERSION)" ] && missing="$$missing COMPONENT_VERSION"; \
	[ -z "$(COMPONENT_PROJECT_URL)" ] && missing="$$missing COMPONENT_PROJECT_URL"; \
	[ -z "$(COMPONENT_ARCHIVE_URL)" ] && missing="$$missing COMPONENT_ARCHIVE_URL"; \
	[ -z "$(COMPONENT_ARCHIVE_HASH)" ] && missing="$$missing COMPONENT_ARCHIVE_HASH"; \
	if [ -n "$$missing" ]; then \
		echo "Skipping package.kdl generation for $$compname: missing variables:$$missing"; \
		if [ -n "$(WS_TOP)" ]; then echo "$$compname" >> "$(WS_TOP)/components.missing-metadata"; fi; \
		exit 0; \
	else \
		echo "generating package.kdl for $$compname"; \
		$(PKGDEV) create $(COMPONENT_FMRI); \
		for package in $(REQUIRED_PACKAGES) ; do \
			$(PKGDEV) edit add dependency --dev --kind require $$package ; \
		done; \
		$(PKGDEV) edit set project-name "$(COMPONENT_NAME)"; \
		$(PKGDEV) edit set summary "$(COMPONENT_SUMMARY)"; \
		$(PKGDEV) edit set classification "$(COMPONENT_CLASSIFICATION)"; \
		$(PKGDEV) edit set license "$(COMPONENT_LICENSE)" -f "$(COMPONENT_LICENSE_FILE)"; \
		$(PKGDEV) edit set version "$(COMPONENT_VERSION)"; \
		$(PKGDEV) edit set project-url "$(COMPONENT_PROJECT_URL)"; \
		$(PKGDEV) edit add source archive "$(COMPONENT_ARCHIVE_URL)" "$(COMPONENT_ARCHIVE_HASH)"; \
		if [ -d "patches" ]; then $(PKGDEV) edit add source patch patches; fi; \
		if [ "$(strip $(BUILD_STYLE))" = "configure" ]; then \
			$(PKGDEV) edit add build --gate $(WS_TOP)/userland-gate.kdl configure $(foreach var,$(CONFIGURE_OPTIONS),"$(var)"); \
		fi; \
	fi
