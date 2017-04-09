#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017, Wiselabs Software Ltda - http://www.wiselabs.com.br . All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		java-commons-bsf
COMPONENT_VERSION=	2.4.0
COMPONENT_SUMMARY= Bean Scripting Framework (BSF) is a set of Java classes which provides scripting language support within Java applications, and access to Java objects and methods from scripting languages.
COMPONENT_PROJECT_URL=	https://commons.apache.org/proper/commons-bsf
COMPONENT_SRC=		bsf-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	bsf-bin-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:28bbd69c6218922a94ae0c2fcbf5a7bf2a8de5dabc849167687933e4c986c3d7
COMPONENT_ARCHIVE_URL=  http://ftp.unicamp.br/pub/apache/commons/bsf/binaries/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/java/commons-bsf
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_LICENSE=	ASLv1.1

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION= $(MV) $(COMPONENT_SRC)/lib/bsf.jar $(COMPONENT_SRC)/lib/bsf-$(COMPONENT_VERSION).jar

build:

install: prep
	[ -d $(PROTO_DIR)/usr/share/lib/java ] || mkdir -p $(PROTO_DIR)/usr/share/lib/java
	[ -f $(PROTO_DIR)/usr/share/lib/java/bsf-$(COMPONENT_VERSION).jar ] || \
		$(CP) $(SOURCE_DIR)/lib/bsf-$(COMPONENT_VERSION).jar $(PROTO_DIR)/usr/share/lib/java

clean::
	rm -rf $(BUILD_DIR)

