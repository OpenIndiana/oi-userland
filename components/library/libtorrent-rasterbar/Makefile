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

#
# Copyright (c) 2022, Daniel Chan
# Copyright (c) 2023 Niklas Poslovski
#

BUILD_STYLE=	cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtorrent-rasterbar
COMPONENT_VERSION=	2.0.8
COMPONENT_SUMMARY=	An open source C++ library implementing the BitTorrent protocol
COMPONENT_GIT_URL= https://github.com/arvidn
COMPONENT_PROJECT_URL=	$(COMPONENT_GIT_URL)/libtorrent
COMPONENT_SRC=		libtorrent-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:29e5c5395de8126ed1b24d0540a9477fbb158b536021cd65aaf9de34d0aadb46
COMPONENT_FMRI=	network/libtorrent-rasterbar
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	BSLv1
COMPONENT_LICENSE_FILE=	LICENSE

GIT_BRANCH_1=39144efe83fcd38778cf76fc609e3475694642ca
COMPONENT_SRC_1=		libsimulator-$(GIT_BRANCH_1)
COMPONENT_ARCHIVE_1=      $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_URL_1=  $(COMPONENT_GIT_URL)/libsimulator/archive/$(GIT_BRANCH_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:2c7ce02d7ea3499d98bb5551560e1cc58bb5b08dfeeb75a8fca39a2306403439

GIT_BRANCH_2=105cce59972f925a33aa6b1c3109e4cd3caf583d
COMPONENT_SRC_2=		try_signal-$(GIT_BRANCH_2)
COMPONENT_ARCHIVE_2=      $(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_URL_2=  $(COMPONENT_GIT_URL)/try_signal/archive/$(GIT_BRANCH_2).tar.gz
COMPONENT_ARCHIVE_HASH_2= sha256:6f111b0d77429a8051be4faed06cf23fb03cf6ee233967c84fdd9d8d3b42ba8e

GIT_BRANCH_3=a57d4d36923c5fafa9698e14be16b8bc2913700a
COMPONENT_SRC_3=		boost-asio-gnutls-$(GIT_BRANCH_3)
COMPONENT_ARCHIVE_3=      $(COMPONENT_SRC_3).tar.gz
COMPONENT_ARCHIVE_URL_3=  $(COMPONENT_GIT_URL)/boost-asio-gnutls/archive/$(GIT_BRANCH_3).tar.gz
COMPONENT_ARCHIVE_HASH_3= sha256:865a21256de08945b79ebdc66270f10afb928a638e2c1829e7948c5976f289d5

COMPONENT_POST_UNPACK_ACTION_1= \
	mv $(COMPONENT_SRC_1)/* $(SOURCE_DIR)/simulation/libsimulator/
COMPONENT_POST_UNPACK_ACTION_2= \
	mv $(COMPONENT_SRC_2)/* $(SOURCE_DIR)/deps/try_signal/
COMPONENT_POST_UNPACK_ACTION_3= \
	mv $(COMPONENT_SRC_3)/* $(SOURCE_DIR)/deps/asio-gnutls/

include $(WS_MAKE_RULES)/common.mk

OPENSSL_VERSION=1.1
CMAKE_OPTION+=-DCMAKE_INSTALL_PREFIX:PATH='/usr'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
