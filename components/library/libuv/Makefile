#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020, Michal Nowak
#

BUILD_BITS=		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libuv
COMPONENT_VERSION=	1.44.1
COMPONENT_SUMMARY=	Cross-platform asynchronous I/O library
COMPONENT_PROJECT_URL=	https://libuv.org/
COMPONENT_FMRI=		library/libuv
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://dist.libuv.org/dist/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:9d37b63430fe3b92a9386b949bebd8f0b4784a39a16964c82c9566247a76f64a
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION=	( cd $(SOURCE_DIR) && ./autogen.sh ; )

CONFIGURE_OPTIONS += --disable-silent-rules
CONFIGURE_OPTIONS += --disable-static

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^ok /p" ' \
	'-e "/^not ok /p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
