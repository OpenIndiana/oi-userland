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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	icedtea-web
COMPONENT_VERSION= 	1.4.1
COMPONENT_SUMMARY= 	Java browser plugin and Web Start launcher
COMPONENT_SRC= 		$(COMPONENT_NAME)-6ec72d653144
COMPONENT_ARCHIVE= 	6ec72d653144.tar.bz2
COMPONENT_ARCHIVE_HASH= \
   sha256:0fa93e2fbbb2ea59abcaa03de909796489d506da9398ea626e74df77a3e55387
COMPONENT_ARCHIVE_URL= \
   http://icedtea.classpath.org/hg/icedtea-web/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://icedtea.classpath.org/wiki/Main_Page

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_POST_UNPACK_ACTION += ($(GSED) -i -e 's/mozilla-plugin/firefox-plugin/' $(SOURCE_DIR)/acinclude.m4)
COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -if)

CONFIGURE_OPTIONS+=        --with-jdk-home=/usr/jdk/instances/openjdk1.7.0
CONFIGURE_OPTIONS+=        --with-rhino=/usr/jdk/instances/openjdk1.7.0/jre/lib/rhino.jar
CONFIGURE_OPTIONS+=        --disable-docs

build: $(BUILD_32)

install: $(INSTALL_32)
