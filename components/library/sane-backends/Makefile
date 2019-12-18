#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS=		32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sane-backends
COMPONENT_VERSION=	1.0.28
COMPONENT_REVISION=	1
COMPONENT_FMRI=         image/scanner/xsane/sane-backends
COMPONENT_SUMMARY=      SANE library and backends
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	http://www.sane-project.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:31260f3f72d82ac1661c62c5a4468410b89fb2b4a811dabbfcc0350c1346de03
COMPONENT_ARCHIVE_URL=	https://gitlab.com/sane-project/backends/uploads/9e718daff347826f4cfe21126c8d5091/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2+ and GPLv2+ with exceptions and Public Domain and IJG and LGPLv2+ and MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lnsl -lsocket

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--disable-locking
CONFIGURE_OPTIONS +=	--enable-pthread
CONFIGURE_OPTIONS +=	--with-gphoto2
CONFIGURE_OPTIONS +=	--with-usb
CONFIGURE_OPTIONS +=	--without-api-spec

COMPONENT_TEST_ENV += PATH="$(PATH.gnu)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/libgphoto2-2
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
