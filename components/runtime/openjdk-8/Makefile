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
# Copyright 2022 Daniel Bell
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		jdk8u
OPENJDK_BUILD_NUMBER=	432
HUMAN_VERSION=		$(COMPONENT_NAME)$(OPENJDK_BUILD_NUMBER)-ga
COMPONENT_VERSION=      1.8.$(OPENJDK_BUILD_NUMBER)
COMPONENT_SUMMARY=      Open-source implementation of the Java Platform, Standard Edition
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:6ac8ee2b6932e4632ea2c33fe2320d6ceaca50a67521fac02a67027e40437460
COMPONENT_ARCHIVE_URL=  \
	https://github.com/openjdk/jdk8u/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://wiki.openjdk.org/display/jdk8u


# Java testing archives
JTREG_VERSION=6.1
PKG_MACROS += JTREG_VERSION=$(JTREG_VERSION).$(JTREG_SUFFIX)
PKG_MACROS += JTREG_HUMAN_VERSION=$(JTREG_VERSION)-$(JTREG_SUFFIX)
JTREG_SUFFIX=3
JPRT_JTREG_HOME=$(COMPONENT_DIR)/$(COMPONENT_SRC_1)/build/images/jtreg

COMPONENT_SRC_1= jtreg-jtreg-$(JTREG_VERSION)-$(JTREG_SUFFIX)
COMPONENT_ARCHIVE_1=      jtreg-$(JTREG_VERSION)+$(JTREG_SUFFIX).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
	sha256:38a7a3f8d48d50eac8e09eb2f9880c7792fa198ec44d246df88492d45d6ee4cf
COMPONENT_ARCHIVE_URL_1=  \
    https://github.com/openjdk/jtreg/archive/refs/tags/$(COMPONENT_ARCHIVE_1)

# jtreg support archives
COMPONENT_ARCHIVE_2 = hamcrest-2.2.jar
COMPONENT_ARCHIVE_URL_2 = https://repo1.maven.org/maven2/org/hamcrest/hamcrest/2.2/hamcrest-2.2.jar
COMPONENT_ARCHIVE_HASH_2 = sha256:5e62846a89f05cd78cd9c1a553f340d002458380c320455dd1f8fc5497a8a1c1
COMPONENT_ARCHIVE_3 = jt6.0-b14.zip
COMPONENT_ARCHIVE_URL_3 = https://git.openjdk.java.net/jtharness/archive/jt6.0-b14.zip
COMPONENT_ARCHIVE_HASH_3 = sha256:b0aa48f7c9841a9debd532a0f1ebdbc63e7d2da5f3c2e13c8b23c0d9924135bd
COMPONENT_ARCHIVE_4 = asm-8.0.jar
COMPONENT_ARCHIVE_URL_4 = https://repo1.maven.org/maven2/org/ow2/asm/asm/8.0/asm-8.0.jar
COMPONENT_ARCHIVE_HASH_4 = sha256:8d96021cad4104da4822cee3a5e5bf6a4737c8b0c67d58d17d7bf7d1b5f7d2fe
COMPONENT_ARCHIVE_5 = asm-tree-8.0.jar
COMPONENT_ARCHIVE_URL_5 = https://repo1.maven.org/maven2/org/ow2/asm/asm-tree/8.0/asm-tree-8.0.jar
COMPONENT_ARCHIVE_HASH_5 = sha256:8a390cef8aea3343342d7f255fd684f05e372b439639f803a4d827f1cdbb0b08
COMPONENT_ARCHIVE_6 = asm-util-8.0.jar
COMPONENT_ARCHIVE_URL_6 = https://repo1.maven.org/maven2/org/ow2/asm/asm-util/8.0/asm-util-8.0.jar
COMPONENT_ARCHIVE_HASH_6 = sha256:f9dbbd03a40a5a7fbd33708ab5e2c7c8dfe856679d99bd49e29ce5d2a415b33a
COMPONENT_ARCHIVE_7 = jcov3.0-b07.zip
COMPONENT_ARCHIVE_URL_7 = https://git.openjdk.java.net/jcov/archive/jcov3.0-b07.zip
COMPONENT_ARCHIVE_HASH_7 = sha256:9d6cbd1c7ea4ca1aa1a6e6549d149d00ecb4f2c7e3091bd0b771ea3c3f36b6c0
COMPONENT_ARCHIVE_8 = 7.0-b09.zip
COMPONENT_ARCHIVE_URL_8 = https://git.openjdk.java.net/asmtools/archive/7.0-b09.zip
COMPONENT_ARCHIVE_HASH_8 = sha256:8284479fda9be745b285356ae5e187e21e313fad9f571e5f78b1a9e786a87475
COMPONENT_ARCHIVE_9 = junit-4.13.2.jar
COMPONENT_ARCHIVE_URL_9 = https://repo1.maven.org/maven2/junit/junit/4.13.2/junit-4.13.2.jar
COMPONENT_ARCHIVE_HASH_9 = sha256:8e495b634469d64fb8acfa3495a065cbacc8a0fff55ce1e31007be4c16dc57d3

TESTNG_VERSION=7.3.0
COMPONENT_ARCHIVE_10 = testng-$(TESTNG_VERSION).jar
COMPONENT_ARCHIVE_URL_10 = https://repo1.maven.org/maven2/org/testng/testng/$(TESTNG_VERSION)/$(COMPONENT_ARCHIVE_10)
COMPONENT_ARCHIVE_HASH_10 = sha256:63727488f9717d57f0d0a0fee5a1fc10a2be9cfcff2ec3a7187656d663c0774e
COMPONENT_ARCHIVE_13 = testng-$(TESTNG_VERSION)-LICENSE.txt
COMPONENT_ARCHIVE_URL_13 = https://raw.githubusercontent.com/cbeust/testng/$(TESTNG_VERSION)/LICENSE.txt
COMPONENT_ARCHIVE_HASH_13 = sha256:c1b9df1275e769f3dbab000d1e457a2d4b0f28eb5da6c77e48dc37eeba202ed7

COMPONENT_ARCHIVE_11 = jcommander-1.78.jar
COMPONENT_ARCHIVE_URL_11 = https://repo1.maven.org/maven2/com/beust/jcommander/1.78/jcommander-1.78.jar
COMPONENT_ARCHIVE_HASH_11 = sha256:7891debb84b5f83e9bd57593ebece3399abbe0fd938cf306b3534c57913b9615
COMPONENT_ARCHIVE_12 = guice-4.2.3.jar
COMPONENT_ARCHIVE_URL_12 = https://repo1.maven.org/maven2/com/google/inject/guice/4.2.3/guice-4.2.3.jar
COMPONENT_ARCHIVE_HASH_12 = sha256:a21e50ffbb67e7adc5b46cf7b9e1a480f1e0f04fd4201ddb1c65da91290601af


CLEAN_PATHS += $(BUILD_DIR) $(JPRT_JTREG_HOME)
CLEAN_PATHS += cacerts.out

# Use OpenJDK 8 as the boot JDK
JAVA_HOME = $(JAVA8_HOME)

# Build fails with GCC 14
GCC_VERSION = 13

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TARGETS=test
COMPONENT_TEST_ENV=$(COMPONENT_BUILD_ENV)
COMPONENT_TEST_ENV+=USERLAND_ARCHIVES=$(USERLAND_ARCHIVES)
COMPONENT_TEST_ENV+=ANT=/usr/bin/ant
COMPONENT_TEST_ENV+=ANT_JAR=/usr/share/lib/ant/ant.jar
COMPONENT_TEST_ENV+=JOBS=$(PARALLEL_JOBS)

COMPONENT_TEST_ARGS+=JPRT_JTREG_HOME=$(JPRT_JTREG_HOME)
COMPONENT_TEST_ARGS+=JTREG_HOME=$(JPRT_JTREG_HOME)
COMPONENT_TEST_ARGS+=JT_HOME=$(JPRT_JTREG_HOME)

# Normalize test results
COMPONENT_TEST_TRANSFORMS += "-e '/make\[/d'"						# delete make logs
COMPONENT_TEST_TRANSFORMS += "-e '/^Agent id: [0-9]/d'"					# random Agend id
COMPONENT_TEST_TRANSFORMS += "-e '/^elapsed time/d'"					# timing
COMPONENT_TEST_TRANSFORMS += "-e 's/ (build time [0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\})//'"	# timing
COMPONENT_TEST_TRANSFORMS += "-e '/^[0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\}/d'"		# timing
COMPONENT_TEST_TRANSFORMS += "-e '/^TIME:/d'"						# timing
COMPONENT_TEST_TRANSFORMS += "-e 's/[0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\} [0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\}/\$$(TIMESTAMP)/'"	# timestamp
COMPONENT_TEST_TRANSFORMS += "-e 's/\(timeout handling was \)[0-9]\{1,\}ms/\1\$$(TIMEOUT)/'"	# timeout
COMPONENT_TEST_TRANSFORMS += "-e 's|$(COMPONENT_DIR)|\$$(COMPONENT_DIR)|g'"		# COMPONENT_DIR

PATCH_LEVEL=0

CONFIGURE_SCRIPT=	$(BUILD_DIR_$(BITS))/configure
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CP) -r $(SOURCE_DIR)/* $(@D))

CONFIGURE_OPTIONS+=        --with-boot-jdk=$(JAVA_HOME)
CONFIGURE_OPTIONS+=        --with-zlib=system
CONFIGURE_OPTIONS+=        --with-giflib=bundled
CONFIGURE_OPTIONS+=        --with-cups
CONFIGURE_OPTIONS+=        --disable-freetype-bundling
CONFIGURE_OPTIONS+=        --with-memory-size=2048
CONFIGURE_OPTIONS+=        --disable-precompiled-headers
CONFIGURE_OPTIONS+=        --disable-ccache
CONFIGURE_OPTIONS+=        --with-user-release-suffix=oi-$(HUMAN_VERSION)
CONFIGURE_OPTIONS+=        --with-update-version=$(OPENJDK_BUILD_NUMBER)
CONFIGURE_OPTIONS+=        --with-extra-cflags="-fno-lifetime-dse"
CONFIGURE_OPTIONS+=        --with-extra-ldflags="$(LDFLAGS)"
CONFIGURE_OPTIONS+=        AS=$(GAS)
CONFIGURE_OPTIONS+=        STRIP=$(STRIP)

COMPONENT_BUILD_ENV+=	USE_GCC=1

COMPONENT_BUILD_ARGS = JOBS=$(PARALLEL_JOBS)

COMPONENT_BUILD_TARGETS = images

CACERTS_DIR=$(WS_TOP)/components/openindiana/ca-certificates
CACERTS_INSTALLED=$(CACERTS_DIR)/build/$(MACH32)/.installed
CACERTS_PROTO_DIR=$(CACERTS_DIR)/build/prototype/$(MACH)

MY_INSTALLED= $(BUILD_DIR_64)/.installed
TESTS_BUILT= $(COMPONENT_DIR)/$(COMPONENT_SRC_1)/.built


$(MY_INSTALLED): $(BUILD_DIR_64)/.built $(TESTS_BUILT)
	[ -d $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0 ] || $(MKDIR) $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0
	chmod -R u+rw $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0
	cp -a $(@D)/build/solaris-*/images/j2sdk-image/* $(PROTO_DIR)/usr/jdk/instances/openjdk1.8.0
	rm -rf $(PROTO_DIR)/usr/jdk/jtreg; cp -a $(SOURCE_DIR_1)/build/images/jtreg $(PROTO_DIR)/usr/jdk/
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
                  -storepass changeit;                                    \
        done

$(TESTS_BUILT): prep
	cd $(SOURCE_DIR_1) &&\
	rm -rf $(SOURCE_DIR_1)/build &&\
	/usr/bin/env $(COMPONENT_TEST_ENV) TESTNG_LICENSE_VERSION=$(TESTNG_VERSION) bash make/build.sh --jdk $(JAVA_HOME)
	$(TOUCH) $@


install:	$(MY_INSTALLED) cacerts.out

$(BUILD_DIR_64)/.tested:   $(TESTS_BUILT) build

$(BUILD_DIR_64)/.tested-and-compared:   $(TESTS_BUILT) build

REQUIRED_PACKAGES += developer/build/ant

# Manually added boot JDK
REQUIRED_PACKAGES += runtime/java/openjdk8

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxtst
