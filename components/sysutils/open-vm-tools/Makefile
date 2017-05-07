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
# Copyright 2016 Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		open-vm-tools
COMPONENT_VERSION=	9.4.6
COMPONENT_SUMMARY=	open-vm-tools is a set of services and modules that enable several features in VMware products for better management of, and seamless user interactions with, guests.
COMPONENT_PROJECT_URL=	https://github.com/vmware/open-vm-tools
COMPONENT_FMRI=		system/virtualization/open-vm-tools
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-stable-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/vmware/open-vm-tools/archive/stable-9.4.6.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:df2022be414be4c3ba4275873e864c3aace4f201ea1c51d016d373c1e25e69d1
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
	($(MV) $(SOURCE_DIR)/open-vm-tools/* $(SOURCE_DIR) && \
	$(RM) -r $(SOURCE_DIR)/open-vm-tools && \
	cd $(@D) && autoreconf -v -i)

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS+= -std=gnu99
CFLAGS+= -D__EXTENSIONS__
CFLAGS+= -D_XOPEN_SOURCE=600
CFLAGS+= -Wno-deprecated-declarations
CFLAGS+= -Wno-unused-local-typedefs

CONFIGURE_OPTIONS+= --without-kernel-modules
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --without-x
CONFIGURE_OPTIONS+= --without-pam
CONFIGURE_OPTIONS+= --without-icu
CONFIGURE_OPTIONS+= --without-gtk2
CONFIGURE_OPTIONS+= --without-gtkmm
CONFIGURE_OPTIONS+= --disable-tests

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdnet
