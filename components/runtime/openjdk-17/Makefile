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
# Copyright 2022-2025 Niklas Poslovski
# Copyright 2023 Franklin Ronald <franklin@wiselabs.com.br>
# Copyright 2026 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

OPENJDK_VERSION=	17
OPENJDK_UPDATE=	0
OPENJDK_BUILD=	20
COMPONENT_NAME=		openjdk
COMPONENT_VERSION=	$(OPENJDK_VERSION).$(OPENJDK_UPDATE).$(OPENJDK_BUILD)
COMPONENT_REVISION=	1
COMPONENT_FMRI=	runtime/java/$(COMPONENT_NAME)$(OPENJDK_VERSION)
COMPONENT_SUMMARY=	Open-source implementation of the Java Platform, Standard Edition
COMPONENT_SRC=	jdk$(OPENJDK_VERSION)u-jdk-$(OPENJDK_VERSION).$(OPENJDK_UPDATE).$(OPENJDK_BUILD)-ga
COMPONENT_ARCHIVE=	jdk-$(OPENJDK_VERSION).$(OPENJDK_UPDATE).$(OPENJDK_BUILD)-ga.tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:ba3ac4b9d7f2c050f46ddcec39b4258660a3f09836f5a71617fd3f7311d06c0b
COMPONENT_ARCHIVE_URL= \
	https://github.com/openjdk/jdk$(OPENJDK_VERSION)u/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://openjdk.java.net/
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_LICENSE=	GPLv2 with Classpath Exception

OPENJDK_INSTANCE=	openjdk$(COMPONENT_VERSION)
CACERTS_STORE=	cacerts.out

include $(WS_MAKE_RULES)/common.mk

# COMPONENT_POST_UNPACK_ACTION= ( cd $(@D) ; \
# 	$(GPATCH) -p1 -R < ../patches/readd-jdk-17.0.17-ga.illumos )

# some of them break x86_64 builds, that's why they are here.
ifeq ($(strip $(MACH)),sparc)
COMPONENT_PRE_CONFIGURE_ACTION += cd $(COMPONENT_SRC) ; \
	$(GPATCH) -p1 -R < ../sparc/0011-8256238-Remove-Matcher-pass_original_key_for_aes.patch ; \
	$(GPATCH) -p1 -R < ../sparc/0048-8256205-Simplify-compiler-calling-convention-handlin.patch ; \
	$(GPATCH) -p1 < ../sparc/restore_cpu_sparc.patch ; \
	$(GPATCH) -p1 < ../sparc/restore_os_cpu_solaris_sparc.patch ; \
	$(GPATCH) -p1 < ../sparc/TemplateInterpreterGenerator-sparc.patch ; \
	$(GPATCH) -p1 < ../sparc/c1-sparc.patch ; \
	$(GPATCH) -p1 < ../sparc/jfr-sparc.patch ; \
	$(GPATCH) -p1 < ../sparc/memset-sparc.patch ; \
	$(GPATCH) -p1 < ../sparc/sparc-misc.patch ; \
	$(GPATCH) -p1 < ../sparc/8254231-for-sparc.patch ; \
	$(GPATCH) -p1 -R < ../sparc/0001-8264868-Reduce-inclusion-of-registerMap.hpp-and-regi.patch ; \
	$(GPATCH) -p1 < ../sparc/sparc-linker.patch ; \
	$(GPATCH) -p1 -R < ../sparc/0001-8282477-x86-aarch64-vmassert-_last_Java_pc-NULL-alre.patch ; \
	$(GPATCH) -p1 < ../sparc/sparc-safefetch.patch ; \
	$(GPATCH) -p1 -R < ../sparc/0001-8283520-JFR-Memory-leak-in-dcmd_arena.patch ; \
	$(GPATCH) -p1 -R < ../sparc/0001-8270491-SEGV-at-read_string_field-oopDesc-char-const.patch ; \
	$(GPATCH) -p1 -R < ../sparc/0001-8268702-JFR-diagnostic-commands-lack-argument-descri.patch ; \
	$(GPATCH) -p1 < ../sparc/sparc-noflatten.patch ; \
	$(GPATCH) -p1 < ../sparc/c1_CodeStubs_sparc.cpp.patch ; \
	$(GPATCH) -p1 < ../sparc/c1_Runtime1_sparc.cpp.patch ; \
	$(GPATCH) -p1 < ../sparc/templateInterpreterGenerator_sparc.cpp.patch ; \
	$(GPATCH) -p1 < ../sparc/templateTable_sparc.cpp.patch
endif

PKG_MACROS  += OPENJDK_INSTANCE=$(OPENJDK_INSTANCE)
PKG_MACROS  += OPENJDK_VERSION=$(OPENJDK_VERSION)

CLEAN_PATHS += $(BUILD_DIR)
CLEAN_PATHS += $(CACERTS_STORE) install

# read the number of jobs from the arguments for make
JOBS=$(patsubst -j%,%,$(filter -j%,$(MAKEFLAGS)))

CFLAGS += -c99

# patches are provided in four directories: patches-reverse (from tribblix - do not modify), patches-p0 (from tribblix - do not modify), patches-p1 (from tribblix - do not modify), and patches-oi (all local openindiana patches go here).  The userland patch does not support reverse and assume only p0 or p1.  There is no support for series.  Put each patch format in a seperate directory and process each one.  Pretend to be a make dependency and check for .patched file and add .patched file at end.
COMPONENT_PREP_ACTION= \
	if [ ! -f $(SOURCE_DIR)/.patched ]; then \
		for patchfile in patches-reverse/*.patch; do \
			/usr/gnu/bin/patch -d $(SOURCE_DIR) --backup --version-control=numbered --strip=1 -R  < $$patchfile; \
		done; \
		for patchfile in patches-p0/*.patch; do \
			/usr/gnu/bin/patch -d $(SOURCE_DIR) --backup --version-control=numbered --strip=0   < $$patchfile; \
		done; \
		for patchfile in patches-p0/patch-*; do \
			/usr/gnu/bin/patch -d $(SOURCE_DIR) --backup --version-control=numbered --strip=0   < $$patchfile; \
		done; \
		for patchfile in patches-p1/*.patch; do \
			/usr/gnu/bin/patch -d $(SOURCE_DIR) --backup --version-control=numbered --strip=1   < $$patchfile; \
		done; \
		for patchfile in patches-oi/*.patch; do \
			/usr/gnu/bin/patch -d $(SOURCE_DIR) --backup --version-control=numbered --strip=1   < $$patchfile; \
		done; \
		touch $(SOURCE_DIR)/.patched; \
	fi

CONFIGURE_OPTIONS+=        --with-jobs=$(JOBS)
CONFIGURE_OPTIONS+=        --x-includes=$(USRDIR)
CONFIGURE_OPTIONS+=        --x-libraries=$(USRLIBDIR64)
CONFIGURE_OPTIONS+=        --with-version-pre=
CONFIGURE_OPTIONS+=        --with-conf-name=oi
CONFIGURE_OPTIONS+=        --with-boot-jdk=/usr/jdk/openjdk17
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

# manually added to use common BOOT-JDK.
REQUIRED_PACKAGES += runtime/java/openjdk17

# manually added to support audio
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += system/library/c++/sunpro

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
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
