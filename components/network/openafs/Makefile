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
# Copyright 2016 Aurelien Larcher. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= openafs
COMPONENT_VERSION= 1.6.20.1
COMPONENT_SUMMARY= OpenAFS - Distributed file system
COMPONENT_PROJECT_URL= http://www.openafs.org
COMPONENT_FMRI= network/openafs 
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-src.tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://www.openafs.org/dl/openafs/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:dc869eecf6c81949d3dd2021eaf87118ef9b90ec5012a35f64836a02a58a8826
COMPONENT_LICENSE=	IBM Public License Version 1.0

COMPONENT_ARCHIVE_1= $(COMPONENT_SRC)-doc.tar.bz2
COMPONENT_ARCHIVE_URL_1= \
  http://www.openafs.org/dl/openafs/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= \
  sha256:2c4bf6f53030e8a9cf3460d9c9292bcdbfea356930ed1d436506e8dc60db0f1c

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL= 0

COMPILER= studio

CONFIGURE_ENV += KRB5_CONFIG=/usr/bin/krb5-config

CPPFLAGS+=-I/usr/include/ncurses

CONFIGURE_OPTIONS += --includedir=/usr/include/openafs
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR.$(BITS))
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-kernel-module
CONFIGURE_OPTIONS += --enable-namei-fileserver
CONFIGURE_OPTIONS += --enable-bitmap-later
CONFIGURE_OPTIONS += --with-krb5

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
