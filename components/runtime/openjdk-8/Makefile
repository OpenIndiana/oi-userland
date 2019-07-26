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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= oppenjdk-8

OPENJDK_BUILD_NUMBER=172
COMPONENT_VERSION=1.8.$(OPENJDK_BUILD_NUMBER)
COMPONENT_REVISION=1
COMPONENT_SUMMARY= Open-source implementation of the Java Platform, Standard Edition
COMPONENT_SRC= openjdk
COMPONENT_ARCHIVE= openjdk-$(COMPONENT_VERSION)-20180527.tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:2929378dd3a41b7953fd5f0244ea684a06a3d71e447516eb0a99ade8e952273f
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.netbsd.org/pub/pkgsrc/distfiles/openjdk7/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://openjdk.java.net/

CLEAN_PATHS += $(BUILD_DIR)
CLEAN_PATHS += cacerts.out

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/configure.mk

PATCH_LEVEL=0

CC=gcc
CXX=g++
PATH=$(GCC_ROOT)/bin:$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CP) -r $(SOURCE_DIR)/* $(@D))
CONFIGURE_SCRIPT=	$(BUILD_DIR_$(BITS))/common/autoconf/configure

CONFIGURE_OPTIONS+=        --with-boot-jdk=$(JAVA_HOME)
CONFIGURE_OPTIONS+=        --with-zlib=system
CONFIGURE_OPTIONS+=        --with-giflib=bundled
CONFIGURE_OPTIONS+=        --with-cups
CONFIGURE_OPTIONS+=        --disable-freetype-bundling
CONFIGURE_OPTIONS+=        --with-memory-size=768
CONFIGURE_OPTIONS+=        --disable-precompiled-headers
CONFIGURE_OPTIONS+=        --disable-ccache
CONFIGURE_OPTIONS+=        --with-user-release-suffix=oi-$(COMPONENT_VERSION)
CONFIGURE_OPTIONS+=        --with-update-version=$(OPENJDK_BUILD_NUMBER)
# OpenJDK uses CLFAGS for C and C++ unfortunately
CONFIGURE_OPTIONS+=        --with-extra-cflags="-std=gnu89 -std=gnu++98 -fno-lifetime-dse"
CONFIGURE_OPTIONS+=        --with-extra-cxxflags="-std=gnu++98 "

CONFIGURE_ENV+=	AS=$(GAS)
CONFIGURE_ENV+=	STRIP=$(STRIP)

COMPONENT_BUILD_ENV+=	USE_GCC=1

COMPONENT_BUILD_ARGS = JOBS=4

COMPONENT_BUILD_TARGETS = images

CACERTS_DIR=$(WS_TOP)/components/openindiana/ca-certificates
CACERTS_INSTALLED=$(CACERTS_DIR)/build/$(MACH32)/.installed
CACERTS_PROTO_DIR=$(CACERTS_DIR)/build/prototype/$(MACH)

MY_INSTALLED= $(BUILD_DIR_64)/.my_installed

$(MY_INSTALLED): $(BUILD_DIR_64)/.built
	[ -d $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0 ] || $(MKDIR) $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0
	chmod -R u+rw $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0
	cp -a $(@D)/build/solaris-*/images/j2sdk-image/* $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0
	/usr/bin/elfedit -e 'dyn:value -s  RPATH "$$ORIGIN:$$ORIGIN/../../jre/lib/$(MACH64)"' $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0/lib/$(MACH64)/libjawt.so
	/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$$ORIGIN:$$ORIGIN/../../jre/lib/$(MACH64)"' $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0/lib/$(MACH64)/libjawt.so
	$(TOUCH) $@

$(CACERTS_INSTALLED):
	gmake -C $(CACERTS_DIR) install

cacerts.out: $(BUILD_DIR_64)/.built $(CACERTS_INSTALLED)
	rm -f $@
	for cert in $(CACERTS_PROTO_DIR)/etc/certs/CA/*.pem; do                 \
                LC_ALL=en_US.UTF-8 $(BUILD_DIR_64)/build/solaris-x86_64-normal-server-release/jdk/bin/keytool \
                  -noprompt					\
                  -importcert                                   \
                  -keystore $@                                  \
                  -alias `echo $$cert | $(GSED) -e 's,.*/\\([^/]*\\)\\.pem,\\1,'` \
                  -file $$cert                                          \
                  -storepass openindiana;                                    \
        done

build:		$(BUILD_64)

install:	$(MY_INSTALLED) cacerts.out

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxtst
