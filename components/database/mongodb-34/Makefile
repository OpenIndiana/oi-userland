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
# Copyright 2017 Alexander Pyhalov
#
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	mongodb
COMPONENT_VERSION= 3.4.2
COMPONENT_SUMMARY= MongoDB distributed document-oriented database
COMPONENT_PROJECT_URL=	https://www.mongodb.com/
COMPONENT_FMRI=	database/mongodb-34
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_SRC=		$(COMPONENT_NAME)-src-r$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://fastdl.mongodb.org/src/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:29b60f6c5331fd2ff5242171a65c03e3b47c1ff957fa317bfaa2ddccd8d51b59
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	APACHE-2.0.txt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# MongoDB 3.4 wants GCC 5 compiler
GCC_ROOT=/usr/gcc/5

BUILD_TOOLS= $(BUILD_DIR)/tools/.built
INSTALL_TOOLS= $(BUILD_DIR)/tools/.installed

MONGO_PREFIX=usr/mongodb/3.4

GMAKE=scons

COMPONENT_BUILD_ARGS += TARGET_ARCH=x86_64
COMPONENT_BUILD_ARGS += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CXX="$(CXX)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LIBPATH=/usr/lib/$(MACH64)
COMPONENT_BUILD_ARGS += LINKFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ARGS += --prefix=$(PROTO_DIR)/$(MONGO_PREFIX)
COMPONENT_BUILD_ARGS += --use-system-zlib
COMPONENT_BUILD_ARGS += --ssl
COMPONENT_BUILD_ARGS += --release

COMPONENT_BUILD_TARGETS=	all

COMPONENT_INSTALL_ARGS = $(COMPONENT_BUILD_ARGS)

$(BUILD_TOOLS):	$(BUILD_64)
	$(MKDIR) $(@D)/bin
	$(CP) -a $(SOURCE_DIR)/src/mongo/gotools/* $(@D) 
	cd $(@D) && /usr/bin/bash build.sh ssl
	$(TOUCH) $(@)

$(INSTALL_TOOLS): $(BUILD_TOOLS) $(INSTALL_64)
	$(CP) $(BUILD_DIR)/tools/bin/* $(PROTO_DIR)/$(MONGO_PREFIX)/bin
	$(TOUCH) $(@)

build:		$(BUILD_64) $(BUILD_TOOLS)

install:	$(INSTALL_64) $(INSTALL_TOOLS)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/build/scons
REQUIRED_PACKAGES += developer/gcc-5
REQUIRED_PACKAGES += developer/golang
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
