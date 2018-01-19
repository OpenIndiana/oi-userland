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
# Copyright 2014 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		hercules
COMPONENT_VERSION=	3.11
COMPONENT_PROJECT_URL=	http://hercules-390.eu
COMPONENT_FMRI=		emulator/hercules
COMPONENT_SRC=		hercules-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:a75fa0138548f93749991adab954c4a473b961bae23ad06822903df0cf2fd2ca
COMPONENT_ARCHIVE_URL=	http://downloads.hercules-390.eu/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Q
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	The Hercules S/370, ESA/390, and z/Architecture Emulator
COMPONENT_CLASSIFICATION=org.opensolaris.category.2008:System/Virtualization

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS += --disable-ipv6

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
