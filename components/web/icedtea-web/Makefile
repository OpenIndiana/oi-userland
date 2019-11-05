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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	icedtea-web
COMPONENT_VERSION= 	1.5.3
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	Java browser plugin and Web Start launcher
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
   sha256:9b4b4477711930cb1d40bde752b17492fe8462a9c0cbd89bfe2c361b64d466b9
COMPONENT_ARCHIVE_URL= \
   http://icedtea.wildebeest.org/download/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://icedtea.classpath.org/wiki/Main_Page
COMPONENT_FMRI=	web/browser/firefox/plugin/firefox-java
COMPONENT_CLASSIFICATION=	Applications/Plug-ins and Run-times
COMPONENT_LICENSE=	GPLv2

#Use Java 7
JAVA_HOME=$(JAVA7_HOME)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION += ($(GSED) -i -e 's/mozilla-plugin/firefox-plugin/' $(SOURCE_DIR)/acinclude.m4)
COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -if)

CONFIGURE_OPTIONS+=        --with-jdk-home=$(JAVA_HOME)
CONFIGURE_OPTIONS+=        --with-rhino=$(JAVA_HOME)/jre/lib/rhino.jar
CONFIGURE_OPTIONS+=        --disable-docs

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
