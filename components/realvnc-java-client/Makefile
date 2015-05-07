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

COMPONENT_NAME= 	realvnc-java-client
COMPONENT_VERSION= 	4.1
COMPONENT_SUMMARY= 	RealVNC Java Viewer
COMPONENT_SRC= 		vnc-4_1-javasrc
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8fb8843c0be67aef39422ac456c56df4523a14be23eb003664da80a7aff33aa8
COMPONENT_ARCHIVE_URL= \
  http://dlc.openindiana.org/oi/jds/downloads/sources/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.realvnc.com

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=$(JAVA_HOME)/bin:/usr/gnu/bin:/usr/bin

COMPONENT_BUILD_ARGS += -C $(BUILD_DIR_32)/java
COMPONENT_INSTALL_ARGS += -C $(BUILD_DIR_32)/java

build: $(BUILD_32)

install: $(INSTALL_32)
