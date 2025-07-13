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

COMPONENT_NAME =		cargo-c
HUMAN_VERSION =			0.10.14+cargo-0.89.0
COMPONENT_SUMMARY =		Helper program to build and install c-like libraries
COMPONENT_ARCHIVE_HASH =	\
	sha256:fe82742019f0e5c1a9f8549b0f41b20f1bc834f5ed0626c47019f15be566b321
COMPONENT_FMRI =		developer/cargo-c
COMPONENT_CLASSIFICATION =	Development/Other Languages
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/libgit2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
