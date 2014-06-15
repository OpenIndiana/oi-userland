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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= oppenjdk-7

OPENJDK_BUILD_NUMBER=45
COMPONENT_VERSION=1.7.$(OPENJDK_BUILD_NUMBER)
COMPONENT_SUMMARY= Open-source implementation of the Java Platform, Standard Edition
COMPONENT_SRC= openjdk
COMPONENT_ARCHIVE= openjdk-$(COMPONENT_VERSION)-20140101.tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:09f87c82ffd61d020c17faa3bca9580f93fde69b8140fd23f56105a23dabffa1
COMPONENT_ARCHIVE_URL= \
  http://ftp.netbsd.org/pub/pkgsrc/distfiles/LOCAL_PORTS/openjdk7/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://openjdk.java.net/

CLEAN_PATHS += $(BUILD_DIR)

ICEDTEA7=icedtea7-02bbff3d71ff
#ICEDTEA_WEB=icedtea-web-9e1f7dc48c20
ICEDTEA_WEB=icedtea-web-6ec72d653144
RHINO=rhino1_7R3

COMPONENT_ARCHIVE_1=cacerts-20091013.tar.bz2
COMPONENT_ARCHIVE_URL_1=http://ftp.netbsd.org/pub/pkgsrc/distfiles/LOCAL_PORTS/openjdk7/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1=sha256:c726fce803cbfba199f3d0787493ca42690658603402be9bb53bb0909a10b191
CLEAN_PATHS += cacerts
CLEAN_PATHS += cacerts.out

COMPONENT_ARCHIVE_2=$(ICEDTEA7).tar.bz2
COMPONENT_ARCHIVE_URL_2=http://icedtea.classpath.org/hg/icedtea7/archive/02bbff3d71ff.tar.bz2
CLEAN_PATHS += $(ICEDTEA7)
# Source is mercurial, hash is changing

COMPONENT_ARCHIVE_3=$(ICEDTEA_WEB).tar.bz2
COMPONENT_ARCHIVE_URL_3=http://icedtea.classpath.org/hg/icedtea-web/archive/6ec72d653144.tar.bz2
CLEAN_PATHS += $(ICEDTEA_WEB)
# Source is mercurial, hash is changing

COMPONENT_ARCHIVE_4=$(RHINO).zip
COMPONENT_ARCHIVE_URL_4=http://ftp.mozilla.org/pub/mozilla.org/js/$(COMPONENT_ARCHIVE_4)
COMPONENT_ARCHIVE_HASH_4=sha256:885b46e24fe5af23ad3712c5e08e8d97d6d92a4b89e1be860e8fe88e4a3dacd1
CLEAN_PATHS += $(RHINO)

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

COMPONENT_POST_UNPACK_ACTION += rm -fr $(ICEDTEA7) $(RHINO) $(ICEDTEA_WEB) cacerts cacerts.out;
COMPONENT_POST_UNPACK_ACTION += $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) ;
COMPONENT_POST_UNPACK_ACTION += $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_2) ;
COMPONENT_POST_UNPACK_ACTION += $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_3) ;
COMPONENT_POST_UNPACK_ACTION += $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_4) ;

COMPONENT_PREP_ACTION += cp -a $(ICEDTEA_WEB)/plugin/icedteanp/java/* $(COMPONENT_SRC)/jdk/src/share/classes ;
COMPONENT_PREP_ACTION += cp -a $(ICEDTEA_WEB)/netx/* $(COMPONENT_SRC)/jdk/src/share/classes ;

# build the configured source
# We need to copy, not use CLONEY, so this part of Makefile is rewritten
$(BUILD_DIR)/%/.built: $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	chmod -R u+r  $(SOURCE_DIR)
	cp -a $(SOURCE_DIR)/* $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
		$(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) build
endif
	$(TOUCH) $@


COMPONENT_ENV+=      LANG=C
COMPONENT_ENV+=      ALT_BOOTDIR=$(JAVA6_HOME)
COMPONENT_ENV+=      ALT_OBJCOPY=/usr/gnu/bin/objcopy
COMPONENT_ENV+=      ALT_COMPILER_PATH=$(GCC_ROOT)/bin
COMPONENT_ENV+=      ALT_CUPS_HEADERS_PATH=/usr/include
COMPONENT_ENV+=      ALT_FREETYPE_HEADERS_PATH=/usr/include/freetype2
COMPONENT_ENV+=      HOTSPOT_BUILD_JOBS=1
COMPONENT_ENV+=      NO_DOCS=true
COMPONENT_ENV+=      SKIP_COMPARE_IMAGES=true
COMPONENT_ENV+=      SKIP_FASTDEBUG_BUILD=yes
COMPONENT_ENV+=      SKIP_DEBUG_BUILD=yes
COMPONENT_ENV+=      USE_GCC=yes
COMPONENT_ENV+=      RHINO_JAR=$(COMPONENT_DIR)/rhino1_7R3/js.jar
COMPONENT_ENV+=      ARCH_DATA_MODEL=$(BITS)
COMPONENT_ENV+=      PREFIX=/usr
COMPONENT_ENV+=      JDK_MICRO_VERSION="0_0$(OPENJDK_BUILD_NUMBER)"
COMPONENT_ENV+=      STRIP=/usr/bin/strip
COMPONENT_ENV+=      ALT_PACKAGE_PATH=/usr
COMPONENT_ENV+=      ALT_X11_PATH=/usr/X11

COMPONENT_BUILD_ENV =   $(COMPONENT_ENV)

COMPONENT_BUILD_ARGS =

cacerts.out: $(BUILD_32)
	for cert in $(COMPONENT_DIR)/cacerts/*.crt; do                 \
                echo yes | LD_LIBRARY_PATH=/usr/lib:$(BUILD_DIR_32)/build/solaris-i586/j2sdk-image/jre/lib/i386 LC_ALL=C $(BUILD_DIR_32)/build/solaris-i586/j2sdk-image/bin/keytool              \
                  -importcert                                           \
                  -keystore $@                                  \
                  -alias `echo $$cert | $(GSED) -e 's,.*/\\([^/]*\\)\\.crt,\\1,'` \
                  -file $$cert                                          \
                  -storepass pkgsrc;                                    \
        done

$(BUILD_DIR)/%/.installed: $(BUILD_DIR)/%/.built cacerts.out
	$(MKDIR) $(PROTO_DIR)/usr/jdk/instances/openjdk1.7.0
	cp -a $(@D)/build/solaris-*/j2sdk-image/* $(PROTO_DIR)/usr/jdk/instances/openjdk1.7.0
	$(TOUCH) $@

build: $(BUILD_32_and_64) cacerts.out

install: $(INSTALL_32_and_64)

.NOTPARALLEL:
