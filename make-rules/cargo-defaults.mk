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
# Component defaults for cargo build style
#

COMPONENT_VERSION ?=		$(shell echo $(HUMAN_VERSION) | $(GSED) -e 's/+.*//')
COMPONENT_SRC ?=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE ?=		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL ?=	https://crates.io/crates/$(COMPONENT_NAME)/
# see https://github.com/rust-lang/crates.io/issues/13482#issuecomment-4304855751
COMPONENT_ARCHIVE_URL ?=	https://static.crates.io/crates/$(COMPONENT_NAME)/$(HUMAN_VERSION)/download

# Use the generic cargo vendor support
CARGO_VENDOR = yes
