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
# Copyright 2015 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2022 Niklas Poslovski
#
USE_OPENSSL11= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nghttp2
COMPONENT_VERSION=	1.50.0
COMPONENT_SUMMARY=	HTTP/2 C Library
COMPONENT_FMRI=		library/nghttp2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:af24007e34c18c782393a1dc3685f8fd5b50283e90a9191d25488eb50aa2c825
COMPONENT_ARCHIVE_URL= \
	https://github.com/nghttp2/nghttp2/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://nghttp2.org/
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	MIT
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-examples
CONFIGURE_OPTIONS += --disable-python-bindings
CONFIGURE_OPTIONS += --disable-app

# Build dependencies
REQUIRED_PACKAGES += developer/cunit

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
