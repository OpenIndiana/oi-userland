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
# Copyright 2017 Alexander Pyhalov
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	icedtea-web
COMPONENT_VERSION= 	1.8.8
COMPONENT_SUMMARY= 	Java browser plugin and Web Start launcher
COMPONENT_SRC_NAME= 	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SRC=		IcedTea-Web-$(COMPONENT_SRC_NAME)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC_NAME).tar.gz
COMPONENT_ARCHIVE_HASH= \
   sha256:f4203a605a3c9c50acdcc6eef4a366b9fdd36d95edcd76bcbfede01107cb5fe6
COMPONENT_ARCHIVE_URL= \
   https://github.com/AdoptOpenJDK/IcedTea-Web/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://icedtea.classpath.org/wiki/Main_Page
COMPONENT_FMRI=	web/browser/firefox/plugin/firefox-java
COMPONENT_CLASSIFICATION=	Applications/Plug-ins and Run-times
COMPONENT_LICENSE=	GPLv2

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CXXFLAGS+=-I$(COMPONENT_DIR)/files

COMPONENT_POST_UNPACK_ACTION += ($(GSED) -i -e 's/mozilla-plugin/firefox-plugin/' $(SOURCE_DIR)/acinclude.m4)
COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -if \
			 && cp -f $(COMPONENT_DIR)/files/*.h $(SOURCE_DIR)/plugin/icedteanp/)

CONFIGURE_OPTIONS+=        --with-jdk-home=$(JAVA_HOME)
CONFIGURE_OPTIONS+=        --without-rhino
CONFIGURE_OPTIONS+=        --disable-docs
CONFIGURE_OPTIONS+=        --with-itw-libs=BUNDLED
CONFIGURE_OPTIONS+=        --disable-native-plugin

# Build dependencies
REQUIRED_PACKAGES += developer/java/openjdk8
REQUIRED_PACKAGES += developer/lang/rustc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += system/library
