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
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	tntnet
COMPONENT_VERSION=	2.2.1
COMPONENT_SUMMARY=	C++ web application development language and server
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:c83170d08ef04c5868051e1c28c74b9562fe71e9e8263828e755ad5bd3547521
COMPONENT_ARCHIVE_URL= \
	http://www.tntnet.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.tntnet.org/tntnet.html
COMPONENT_FMRI=	library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS+=	$(CPP_LARGEFILES)
CXXFLAGS+=	$(CPP_LARGEFILES)
CPPFLAGS+=	$(CPP_LARGEFILES)

COMPONENT_PREP_ACTION += \
        (cd $(@D); autoreconf --install --force)

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# Prepare config file for tntnet demo webapp server
COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTO_DIR)/etc/tntnet && $(GSED) \
            -e 's,\(\/tntnet\)\(\.log|\.pid\)<,\1-demos\2<,g' \
            -e 's,port>80<,port>8079<,g' \
            -e 's,>www-data<,>webservd<,g' \
            < tntnet.xml > tntnet-demos.xml )

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --localstatedir=/var

build: $(BUILD_32_and_64)

# Order the installations so we have the 32-bit paths in default config file
$(INSTALL_32): $(INSTALL_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += library/cxxtools
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
