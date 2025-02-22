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
# Copyright (c) 2023, Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sane-backends
COMPONENT_VERSION=	1.1.1
COMPONENT_REVISION= 8
COMPONENT_SUMMARY=      SANE library and backends
COMPONENT_PROJECT_URL=	http://www.sane-project.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:dd4b04c37a42f14c4619e8eea6a957f4c7c617fe59e32ae2872b373940a8b603
COMPONENT_ARCHIVE_URL=	https://gitlab.com/sane-project/backends/uploads/7d30fab4e115029d91027b6a58d64b43/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         image/scanner/xsane/sane-backends
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      GPLv2+ and GPLv2+ with exceptions and Public Domain and IJG and LGPLv2+ and MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

# gcc-14 complains about these
CFLAGS += -Wno-error=implicit-function-declaration
CFLAGS += -Wno-error=int-conversion

LDFLAGS += -lnsl -lsocket

CONFIGURE_OPTIONS += --disable-locking
CONFIGURE_OPTIONS += --enable-pthread
CONFIGURE_OPTIONS += --with-gphoto2
CONFIGURE_OPTIONS += --with-usb
CONFIGURE_OPTIONS += --without-systemd

COMPONENT_TEST_ENV += PATH="$(PATH.gnu)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgphoto2-2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += web/curl
