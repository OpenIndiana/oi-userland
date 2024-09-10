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
# Copyright 2024, Friedrich Kink. All rights reserved.
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xca
COMPONENT_VERSION=	2.6.0
COMPONENT_SUMMARY=	XCA - X Certificate and Key Management
COMPONENT_DESCRIPTION=	This application is intended for creating and managing \
			X.509 certificates, certificate requests, RSA, DSA and EC \
			private keys, Smartcards and CRLs.\
			Everything that is needed for a CA is implemented. \
			All CAs can sign sub-CAs recursively. These certificate chains \
			are shown clearly.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:55a39f22eabadcce4532ebfcf07f796372bdb0d323720db6b6e0deaf267b1709
COMPONENT_PROJECT_URL=	http://xca.hohnstaedt.de
COMPONENT_ARCHIVE_URL=	https://github.com/chris2511/$(COMPONENT_NAME)/releases/download/RELEASE.$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= 	sysutils/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	Christian Hohnstaedt
COMPONENT_LICENSE_FILE=	COPYRIGHT

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_ENV= DISPLAY=:1

COMPONENT_PRE_TEST_ACTION = $(SHELL) $(COMPONENT_DIR)/start_Xvfb $(COMPONENT_DIR)
COMPONENT_POST_TEST_ACTION = $(SHELL) $(COMPONENT_DIR)/stop_Xvfb $(COMPONENT_DIR)

PATH=			$(PATH.gnu)

ENV += 	Qt5_DIR=$(QT5_BASEDIR)
ENV += 	QT_DIR=$(QT5_BASEDIR)

CXXFLAGS += -std=c++17 -D__SOLARIS__

CMAKE_OPTIONS += -DADDRESS_SANITIZER=OFF
CMAKE_OPTIONS += -DAPPSTORE_COMPLIANT=ON

COMPONENT_TEST_TRANSFORMS = \
        '-n ' \
        '-e "s/Passed.*$$/Passed/p" ' \
        '-e "s/Failed .*$$/Failed/p" '

COMPONENT_POST_INSTALL_ACTION = \
        /usr/bin/elfedit -e 'dyn:value -s RUNPATH "$(GCC_LIBDIR):$(QT5_LIBDIR)"' $(PROTO_DIR)/usr/bin/xca; \
        /usr/bin/elfedit -e 'dyn:value -s RPATH   "$(GCC_LIBDIR):$(QT5_LIBDIR)"' $(PROTO_DIR)/usr/bin/xca;

TEST_REQUIRED_PACKAGES += x11/server/xvfb

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += system/library
