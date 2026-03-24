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

BUILD_STYLE = cargo

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cbindgen
HUMAN_VERSION =			0.29.2
COMPONENT_SUMMARY =		A tool for generating C bindings to Rust code.
COMPONENT_ARCHIVE_HASH =	\
	sha256:befbfd072a8e81c02f8c507aefce431fe5e7d051f83d48a23ffc9b9fe5a11799
COMPONENT_FMRI =		developer/rust/cbindgen
COMPONENT_CLASSIFICATION =	Development/Other Languages
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
