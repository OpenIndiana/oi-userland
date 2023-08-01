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
# Copyright (c) 2011, 2020, Oracle and/or its affiliates.
# Copyright (c) 2020, Michal Nowak
# Copyright (c) 2020, Marco van Wieringen
# Copyright (c) 2022, Niklas Poslovski
#

BUILD_BITS=		64
BUILD_STYLE=		cmake

include ../../../make-rules/shared-macros.mk

MAJOR_VERSION=3.6
MICRO_VERSION=8

COMPONENT_NAME=		wireshark
COMPONENT_VERSION=	$(MAJOR_VERSION).$(MICRO_VERSION)
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=	https://www.wireshark.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:67ab23ee09a646ab8cc0ddcc985209f24f253337461e3d9644c6cfe1c097260c
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/src/all-versions/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET:		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Set path to Qt5 libs
QT5_LIBDIR = /usr/lib/qt/5.15/lib/amd64

# Set path to Qt5 cmake modules.
CMAKE_OPTIONS += -DCMAKE_PREFIX_PATH=$(QT5_LIBDIR)/cmake
# Add non-standard path to perl pod2man and pod2html commands.
CMAKE_OPTIONS += -DCMAKE_PROGRAM_PATH=$(USRDIR)/perl5/bin/
# Install all the wireshark executables to sbin directory.
CMAKE_OPTIONS += -DCMAKE_INSTALL_BINDIR=/usr/sbin
# Install all the wireshark Read-only architecture-independent data to share/wireshark directory.
CMAKE_OPTIONS += -DCMAKE_INSTALL_DATADIR=/usr/share/wireshark

CMAKE_OPTIONS += -DBUILD_androiddump=OFF
CMAKE_OPTIONS += -DBUILD_randpkt=OFF
CMAKE_OPTIONS += -DBUILD_dftest=OFF

PKG_MACROS += MAJOR_VERSION=$(MAJOR_VERSION)
PKG_MACROS += MICRO_VERSION=$(MICRO_VERSION)

CFLAGS += -I/usr/include/kerberosv5
CFLAGS += -D__EXTENSIONS__
LDFLAGS += -lsocket -lnsl

COMPONENT_POST_INSTALL_ACTION  = \
    for file in $(PROTO_DIR)/usr/sbin/wireshark; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$(QT5_LIBDIR)"' $$file ; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "$(GCC_LIBDIR):$(QT5_LIBDIR)"' $$file ; \
    done ;

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libcares
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
