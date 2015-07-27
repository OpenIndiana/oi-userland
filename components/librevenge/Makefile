#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2015, Apostolos Syropoulos. All rights reserved.
# Copyright (c) 2015, Aurelien Larcher. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		librevenge
COMPONENT_VERSION=	0.0.2
COMPONENT_FMRI=     	library/c++/librevenge
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_PROJECT_URL=	https://sourceforge.net/p/libwpd/wiki/librevenge/
COMPONENT_SUMMARY=      librevenge - base library for writing document import filters
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:f6f280c4345546aad16aeafd5cf2e4a4ac31a81606171755465bba0d96efcf0f
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/libwpd/files/librevenge/librevenge-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      LGPLv2.1 MPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--disable-werror

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =    $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk

