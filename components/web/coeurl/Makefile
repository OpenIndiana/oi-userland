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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         coeurl
COMPONENT_VERSION=      0.3.0
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      A simple async wrapper around CURL for C++
COMPONENT_PROJECT_URL=  https://nheko.im/nheko-reborn/coeurl
COMPONENT_FMRI=         web/coeurl
COMPONENT_SRC=          $(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:48b07482364edcbed03e352f6b8b07e327c331eaa45707ad58e62930fa361382
COMPONENT_ARCHIVE_URL=	https://nheko.im/nheko-reborn/$(COMPONENT_NAME)/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

# Tests need doctest which we don't have yet.
TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/spdlog
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
