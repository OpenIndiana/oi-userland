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
# Copyright 2019 Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		open-vm-tools
COMPONENT_VERSION=	10.3.10
COMPONENT_SUMMARY=	open-vm-tools is a set of services and modules that enable several features in VMware products for better management of, and seamless user interactions with, guests.
COMPONENT_PROJECT_URL=	https://github.com/vmware/open-vm-tools
COMPONENT_FMRI=		system/virtualization/open-vm-tools
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-stable-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/vmware/$(COMPONENT_NAME)/archive/stable-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6e39e643edcd85bae04ba8db608bd500d14ff3771e6e89b171ffb31020fed945
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION = \
	($(MV) $(SOURCE_DIR)/open-vm-tools/* $(SOURCE_DIR) && \
	$(RM) -r $(SOURCE_DIR)/open-vm-tools) 

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -v -i -f )	

COMPONENT_PRE_CONFIGURE_ACTION = \
  ($(CLONEY) $(SOURCE_DIR) $(@D) ) 

CFLAGS += -std=gnu99

# This package need defines in CPPFLAGS so they apply to
# C++ compiles as well as C.
CPPFLAGS += -D__EXTENSIONS__
CPPFLAGS += -D_XOPEN_SOURCE=600
CPPFLAGS += -D__SOLARIS__=1
# open-vm-tools have if defined(sun) all over (should be __sun)
CPPFLAGS += -Dsun
# and this one means S11 or later (not S10, S9)
CPPFLAGS += -DSOL11

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CFLAGS += -Wno-deprecated-declarations
CFLAGS += -Wno-unused-local-typedefs
CFLAGS += -Wno-unused-variable

LDFLAGS += -lnsl

CONFIGURE_OPTIONS += --disable-grabbitmqproxy
CONFIGURE_OPTIONS += --disable-multimon
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-tests
CONFIGURE_OPTIONS += --enable-deploypkg=no
CONFIGURE_OPTIONS += --with-gtk3
CONFIGURE_OPTIONS += --with-gtkmm3
CONFIGURE_OPTIONS += --without-icu
CONFIGURE_OPTIONS += --without-kernel-modules
CONFIGURE_OPTIONS += --without-xerces
CONFIGURE_OPTIONS += --sysconfdir=/etc

# Need C++ compatible xdr headers
CONFIGURE_OPTIONS += RPCGENFLAGS="-C"

build:		$(BUILD_64)

install:	$(INSTALL_64)

# there are no tests defined
test:		  $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Not found automatically
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/cairomm
REQUIRED_PACKAGES += library/desktop/c++/gtkmm3
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdnet
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxtst
