#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c), 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2017, Wiselabs Software Ltda - http://www.wiselabs.com.br. All rights reserved.
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ant
COMPONENT_VERSION=	1.10.17
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Apache Ant is a Java-based build tool
COMPONENT_PROJECT_URL=	https://ant.apache.org/
COMPONENT_SRC_NAME=	apache-ant
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-bin.tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:5210fc9d77e96bf5f4639287f29826da85e54a542e0a409463b1642bc3caaee7
COMPONENT_ARCHIVE_URL=	https://dlcdn.apache.org//ant/binaries/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/build/ant
COMPONENT_CLASSIFICATION=	Development/Distribution Tools
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

# Needed for GNU ln
PATH=$(PATH.gnu)

build: 

install: prep
	mkdir -p $(PROTO_DIR)/etc
	mkdir -p $(PROTO_DIR)/usr/bin
	mkdir -p $(PROTO_DIR)/usr/share/ant/bin
	mkdir -p $(PROTO_DIR)/usr/share/ant/etc
# 	mkdir -p $(PROTO_DIR)/usr/share/ant/lib
	mkdir -p $(PROTO_DIR)/usr/share/doc/ant
	mkdir -p $(PROTO_DIR)/usr/share/java/ant
	cp $(COMPONENT_DIR)/files/ant.conf $(PROTO_DIR)/etc
	cp -pr $(SOURCE_DIR)/bin $(PROTO_DIR)/usr/share/ant/
	cp -pr $(SOURCE_DIR)/etc $(PROTO_DIR)/usr/share/ant/
	cp -p $(SOURCE_DIR)/lib/*jar $(PROTO_DIR)/usr/share/java/ant/
	cp -pr $(SOURCE_DIR)/manual $(PROTO_DIR)/usr/share/doc/ant/
	cp -p $(SOURCE_DIR)/CONTRIBUTORS $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/contributors.xml  $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/fetch.xml $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/get-m2.xml $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/INSTALL $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/KEYS $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/LICENSE $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/NOTICE $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/patch.xml $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/README $(PROTO_DIR)/usr/share/doc/ant
	cp -p $(SOURCE_DIR)/WHATSNEW $(PROTO_DIR)/usr/share/doc/ant
	ln -frs $(PROTO_DIR)/usr/share/ant/bin/ant $(PROTO_DIR)/usr/bin/ant
	ln -frs $(PROTO_DIR)/usr/share/java/ant $(PROTO_DIR)/usr/share/ant/lib
	rm $(PROTO_DIR)/usr/share/ant/bin/*.bat
	rm $(PROTO_DIR)/usr/share/ant/bin/*.cmd
	gsed -i -e 's?\/usr\/bin\/python?\/usr\/bin\/python$(PYTHON_VERSION)?' $(PROTO_DIR)/usr/share/ant/bin/runant.py

clean::
	rm -rf $(BUILD_DIR)

# COMPONENT_POST_INSTALL_ACTION += \
#      $(GSED) -i -e 's?\/usr\/bin\/python?\/usr\/bin\/python$(PYTHON_VERSION)?' \
#      $(PROTO_DIR)/usr/share/ant/bin/runant.py

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES.python += runtime/python
