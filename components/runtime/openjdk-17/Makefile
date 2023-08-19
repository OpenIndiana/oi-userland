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
# Copyright 2019 Michal Nowak
# Copyright 2021 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
# Copyright 2022-2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

OPENJDK_VERSION=	17
OPENJDK_UPDATE=	0
OPENJDK_BUILD=	8
COMPONENT_NAME=		openjdk
COMPONENT_VERSION=	$(OPENJDK_VERSION).$(OPENJDK_UPDATE).$(OPENJDK_BUILD)
COMPONENT_FMRI=	runtime/java/$(COMPONENT_NAME)$(OPENJDK_VERSION)
COMPONENT_SUMMARY=	Open-source implementation of the Java Platform, Standard Edition
COMPONENT_SRC=	jdk$(OPENJDK_VERSION)u-jdk-$(OPENJDK_VERSION).$(OPENJDK_UPDATE).$(OPENJDK_BUILD)-ga
COMPONENT_ARCHIVE=	jdk-$(OPENJDK_VERSION).$(OPENJDK_UPDATE).$(OPENJDK_BUILD)-ga.tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:8d631dac790ec3eab008639db5b449e8a36310171b3cd68cb7f0b1260ca2467f
COMPONENT_ARCHIVE_URL= \
	https://github.com/openjdk/jdk$(OPENJDK_VERSION)u/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://openjdk.java.net/
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_LICENSE=	GPLv2 with Classpath Exception

COMPONENT_NAME_1= jdk17
COMPONENT_SRC_1= $(COMPONENT_NAME_1)-jdk-17-35
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_HASH_1= sha256:973b576b3ba0b78451cf26c835162fba10216ac2d5a6141a6040dddcde9ac6c6
COMPONENT_ARCHIVE_URL_1= http://pkgs.tribblix.org/openjdk/$(COMPONENT_ARCHIVE_1)
PKG_PROTO_DIRS += $(COMPONENT_SRC_1)

OPENJDK_INSTANCE=	openjdk$(COMPONENT_VERSION)
CACERTS_STORE=	cacerts.out

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS  += OPENJDK_INSTANCE=$(OPENJDK_INSTANCE)
PKG_MACROS  += OPENJDK_VERSION=$(OPENJDK_VERSION)

CLEAN_PATHS += $(BUILD_DIR)
CLEAN_PATHS += $(CACERTS_STORE)
CLEAN_PATHS += $(COMPONENT_SRC_1)

# read the number of jobs from the arguments for make
JOBS=$(patsubst -j%,%,$(filter -j%,$(MAKEFLAGS)))

CFLAGS += -c99

CONFIGURE_OPTIONS+=        --with-jobs=$(JOBS)
CONFIGURE_OPTIONS+=        --x-includes=$(USRDIR)
CONFIGURE_OPTIONS+=        --x-libraries=$(USRLIBDIR64)
CONFIGURE_OPTIONS+=        --with-version-pre=
CONFIGURE_OPTIONS+=        --with-conf-name=oi
CONFIGURE_OPTIONS+=        --with-boot-jdk=$(COMPONENT_DIR)/$(COMPONENT_SRC_1)
CONFIGURE_OPTIONS+=        --with-freetype=system
CONFIGURE_OPTIONS+=        --with-giflib=system
CONFIGURE_OPTIONS+=        --with-harfbuzz=system
CONFIGURE_OPTIONS+=        --with-lcms=bundled
CONFIGURE_OPTIONS+=        --with-libjpeg=system
CONFIGURE_OPTIONS+=        --with-libpng=system
CONFIGURE_OPTIONS+=        --with-zlib=system
CONFIGURE_OPTIONS+=        --with-x=yes
CONFIGURE_OPTIONS+=        --with-native-debug-symbols=none
CONFIGURE_OPTIONS+=        --with-jvm-variants=server
CONFIGURE_OPTIONS+=        --with-debug-level=release
CONFIGURE_OPTIONS+=        --with-toolchain-type=gcc
CONFIGURE_OPTIONS+=        --with-extra-cxxflags="$(CXXFLAGS)"
CONFIGURE_OPTIONS+=        --with-extra-ldflags="-m64"
CONFIGURE_OPTIONS+=        --with-cups=$(USRDIR)
CONFIGURE_OPTIONS+=        --with-fontconfig=$(USRDIR)
CONFIGURE_OPTIONS+=        --enable-unlimited-crypto
CONFIGURE_OPTIONS+=        --disable-dtrace
CONFIGURE_OPTIONS+=        --disable-hotspot-gtest
CONFIGURE_OPTIONS+=        --disable-warnings-as-errors
CONFIGURE_OPTIONS+=        --disable-precompiled-headers
CONFIGURE_OPTIONS+=        --disable-ccache
CONFIGURE_OPTIONS+=        --disable-option-checking
CONFIGURE_OPTIONS+=        --enable-deprecated-ports=yes

CONFIGURE_ENV+= LD=/usr/bin/gld
CONFIGURE_ENV+= LD_LIBRARY_PATH=/usr/gcc/7/lib/amd64
COMPONENT_BUILD_ENV+= LD=/usr/bin/gld
COMPONENT_BUILD_ENV+= LD_LIBRARY_PATH=/usr/gcc/7/lib/amd64

COMPONENT_POST_BUILD_ACTION=	($(LN) -s server/libjvm.so $(@D)/images/jdk/lib/libjvm.so)

COMPONENT_BUILD_TARGETS = images

# reset arguments from Jenkins
COMPONENT_BUILD_ARGS=

CACERTS_DIR=$(WS_TOP)/components/openindiana/ca-certificates
CACERTS_INSTALLED=$(CACERTS_DIR)/build/$(MACH32)/.installed
CACERTS_PROTO_DIR=$(CACERTS_DIR)/build/prototype/$(MACH)

$(CACERTS_INSTALLED):
	gmake -C $(CACERTS_DIR) install

$(CACERTS_STORE): $(BUILD_DIR_64)/.built $(CACERTS_INSTALLED)
	$(RM) $@
	for cert in $(CACERTS_PROTO_DIR)/etc/certs/CA/*.pem; do              \
                LC_ALL=en_US.UTF-8  $(BUILD_DIR_64)/images/jdk/bin/keytool \
                  -noprompt					                                   \
                  -importcert                                          \
                  -keystore $@                                         \
                  -alias `echo $$cert | $(GSED) -e 's,.*/\\([^/]*\\)\\.pem,\\1,'` \
                  -file $$cert                                         \
                  -storetype jks                                       \
                  -storepass changeit;                                 \
        done

build:		$(BUILD_64)

install: $(BUILD_DIR_64)/.built	$(CACERTS_STORE)
	$(RM) -r $(PROTO_DIR)/usr/jdk/instances/$(OPENJDK_INSTANCE)
	$(MKDIR) $(PROTO_DIR)/usr/jdk/instances/$(OPENJDK_INSTANCE)
	$(CP) -a $(BUILD_DIR_64)/images/jdk/* $(PROTO_DIR)/usr/jdk/instances/$(OPENJDK_INSTANCE)
	$(CHMOD) +x $(PROTO_DIR)/usr/jdk/instances/$(OPENJDK_INSTANCE)/lib/jspawnhelper
	$(CP) $(CACERTS_STORE) $(PROTO_DIR)/usr/jdk/instances/$(OPENJDK_INSTANCE)/lib/security/cacerts
	$(TOUCH) $@

test:		$(NO_TESTS)

# manually added to support audio
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += system/library/c++/sunpro

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/giflib
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxtst
