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
# Copyright 2016 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		keepassx
COMPONENT_VERSION=	2.0.2
COMPONENT_PROJECT_URL=	https://www.keepassx.org/
COMPONENT_FMRI=		desktop/keepassx
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:204bdcf49c72078cd6f02b4f29b062923cca9e7b2d3551f2bf352763daa236b8
COMPONENT_ARCHIVE_URL=	https://www.keepassx.org/releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2-or-GPLv3
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	A password manager
COMPONENT_CLASSIFICATION=Applications/System Utilities

include ../../../make-rules/prep.mk
include ../../../make-rules/cmake.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)

REQUIRED_PACKAGES += library/qt4
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxtst

include ../../../make-rules/depend.mk
