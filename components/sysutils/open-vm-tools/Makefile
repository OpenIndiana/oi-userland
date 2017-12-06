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
# Copyright 2017 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		open-vm-tools
COMPONENT_VERSION=	10.1.15
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=	open-vm-tools is a set of services and modules that enable several features in VMware products for better management of, and seamless user interactions with, guests.
COMPONENT_PROJECT_URL=	https://github.com/vmware/open-vm-tools
COMPONENT_FMRI=		system/virtualization/open-vm-tools
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-stable-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/vmware/$(COMPONENT_NAME)/archive/stable-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:2257122f5fee37bf1da1a764708a098b2e8d2847b5ba23dbffe97fd9c4b4214f
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION = \
	($(MV) $(SOURCE_DIR)/open-vm-tools/* $(SOURCE_DIR) && \
	$(RM) -r $(SOURCE_DIR)/open-vm-tools && \
  cd $(@D) && autoreconf -v -i )	

COMPONENT_PRE_CONFIGURE_ACTION = \
  ($(CLONEY) $(SOURCE_DIR) $(@D) ) 

CFLAGS += -std=gnu99
CFLAGS += -D__EXTENSIONS__
CFLAGS += -D_XOPEN_SOURCE=600
CFLAGS += -D__SOLARIS__=1
CFLAGS += -D_FILE_OFFSET_BITS=64
CFLAGS += -Wno-deprecated-declarations
CFLAGS += -Wno-unused-local-typedefs

LDFLAGS += -lnsl

CONFIGURE_OPTIONS += --disable-grabbitmqproxy
CONFIGURE_OPTIONS += --disable-multimon
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-tests
CONFIGURE_OPTIONS += --enable-deploypkg=no
CONFIGURE_OPTIONS += --without-gtk2
CONFIGURE_OPTIONS += --without-gtkmm
CONFIGURE_OPTIONS += --without-icu
CONFIGURE_OPTIONS += --without-kernel-modules
CONFIGURE_OPTIONS += --without-x
CONFIGURE_OPTIONS += --without-xerces

build:		$(BUILD_32)

install:	$(INSTALL_32)

# there are no tests defined
test:		  $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/libdnet
REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
