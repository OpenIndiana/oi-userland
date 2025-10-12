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
# Copyright 2022 Gary Mills
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		antlr4
COMPONENT_VERSION=	4.13.2
COMPONENT_SUMMARY=	ANother Tool for Language Recognition
COMPONENT_DESCRIPTION=	ANTLR, ANother Tool for Language Recognition, (formerly PCCTS) is a language tool that provides a framework \
						for constructing recognizers, compilers, and translators from grammatical descriptions containing C++ or \
						Java actions [You can use PCCTS 1.xx to generate C-based parsers].
COMPONENT_PROJECT_URL=	https://www.antlr.org/
COMPONENT_SRC=		antlr-$(COMPONENT_VERSION)-complete
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).jar
COMPONENT_ARCHIVE_HASH= sha256:eae2dfa119a64327444672aff63e9ec35a20180dc5b8090b7a6ab85125df4d76
COMPONENT_ARCHIVE_URL=	https://www.antlr.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			developer/parser/antlr4
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=		BSD-3-Clause
COMPONENT_LICENSE_FILE=	LICENSE.txt

# Needed for GNU ln
PATH=$(PATH.gnu)

include $(WS_MAKE_RULES)/ips.mk

build:

install:
	mkdir -p $(SOURCE_DIR)
	mkdir -p $(PROTO_DIR)/usr/share/java
	mkdir -p /$(PROTO_DIR)/usr/bin
	cp $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) $(PROTO_DIR)/usr/share/java
	ln -frs $(PROTO_DIR)/usr/share/$(COMPONENT_ARCHIVE) $(PROTO_DIR)/usr/share/java/antlr-complete.jar
	cp $(COMPONENT_DIR)/files/antlr4 $(PROTO_DIR)/usr/bin
	cp $(COMPONENT_DIR)/files/grun $(PROTO_DIR)/usr/bin

clean::
	rm -rf $(BUILD_DIR)
	rm -rf $(SOURCE_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
