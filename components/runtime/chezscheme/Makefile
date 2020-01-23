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
# Copyright 2019 Richard Lowe
#

BUILD_BITS= 64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		chezscheme
COMPONENT_VERSION=	9.5.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Chez Scheme
COMPONENT_PROJECT_URL=	https://github.com/cisco/ChezScheme
COMPONENT_FMRI=		runtime/chezscheme
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_SRC=		ChezScheme-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:3a370fdf2ffd67d6a0ccbb993dfab1cbaf4a0a97983c869cfaab40528c33c48b
COMPONENT_ARCHIVE_URL= \
  https://github.com/cisco/ChezScheme/archive/v$(COMPONENT_VERSION).tar.gz

COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	Apache-2.0

# SunOS-ish bootstrap files not included in the release tarballs These must be
# generated according to the instructions provided by ChezScheme on a system
# which _is_ supported for bootstrap, and then provided by us
COMPONENT_NAME_1= chezscheme-bootstrap
COMPONENT_VERSION_1= $(COMPONENT_VERSION)
COMPONENT_SRC_1= $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_URL_1= https://github.com/OpenIndiana/$(COMPONENT_NAME_1)/archive/$(COMPONENT_VERSION_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
  sha256:1f00d017e5ebf8eb0ee2c6ae6b101917c0e10bf5bcbcebe2827882eb1025015e
COMPONENT_SRC_BOOTSTRAP= $(COMPONENT_SRC_1)

# Nanopass
COMPONENT_NAME_2= nanopass-framework-scheme
COMPONENT_VERSION_2= 1.9
COMPONENT_SRC_2= $(COMPONENT_NAME_2)-$(COMPONENT_VERSION_2)
COMPONENT_ARCHIVE_2= $(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_URL_2= https://github.com/nanopass/$(COMPONENT_NAME_2)/archive/v$(COMPONENT_VERSION_2).tar.gz
COMPONENT_ARCHIVE_HASH_2=	\
  sha256:625b239f9030d0b1e86b1fffd8b69f7249a63e8b8ca85195a00cf22889f7fc86
COMPONENT_SRC_NANOPASS= $(COMPONENT_SRC_2)

# stex
COMPONENT_NAME_3= stex
COMPONENT_VERSION_3= 1.2.1
COMPONENT_SRC_3= $(COMPONENT_NAME_3)-$(COMPONENT_VERSION_3)
COMPONENT_ARCHIVE_3= $(COMPONENT_SRC_3).tar.gz
COMPONENT_ARCHIVE_URL_3= https://github.com/dybvig/stex/archive/v$(COMPONENT_VERSION_3).tar.gz
COMPONENT_ARCHIVE_HASH_3=	\
  sha256:bf784ca46aaca9b665b7eb0c39f04f6a695aa40e99b11d8a6d4440648c1bf40e
COMPONENT_SRC_STEX= $(COMPONENT_SRC_3)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION= ($(CLONEY) $(SOURCE_DIR) $(@D)) && \
	($(CP) -R $(COMPONENT_SRC_NANOPASS)/* $(@D)/nanopass) && \
	($(CP) -R $(COMPONENT_SRC_STEX)/* $(@D)/stex) && \
	($(CP) -R $(COMPONENT_SRC_BOOTSTRAP)/* $(@D)/boot/)

CONFIGURE_OPTIONS= --64 --threads --installlib=/usr/lib/amd64

COMPONENT_INSTALL_ARGS +=	TempRoot=$(PROTO_DIR)
COMPONENT_TEST_TARGETS= test

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += library/zlib
