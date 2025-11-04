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

USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		protobuf-c
COMPONENT_VERSION =		1.5.2
COMPONENT_SUMMARY =		Protocol Buffers implementation in C
COMPONENT_PROJECT_URL =		https://github.com/protobuf-c/protobuf-c
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL =		https://github.com/protobuf-c/protobuf-c/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH =	sha256:e2c86271873a79c92b58fef7ebf8de1aa0df4738347a8bd5d4e65a80a16d0d24
COMPONENT_FMRI =		library/protobuf-c
COMPONENT_CLASSIFICATION =	System/Libraries
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# configure needs GNU make
CONFIGURE_ENV += MAKE="$(GMAKE)"

# We do not need static libraries
CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/abseil-cpp
REQUIRED_PACKAGES += library/c++/abseil-cpp-2501
REQUIRED_PACKAGES += library/c++/protobuf
REQUIRED_PACKAGES += library/c++/protobuf-302
REQUIRED_PACKAGES += system/library
