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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		docbook
# fake version for conglomeration of versions
COMPONENT_VERSION=	1.0
COMPONENT_PROJECT_URL=	http://www.oasis-open.org/docbook/
COMPONENT_BUGDB=	utility/docbook

TPNO=			9654

# see below for actual sources
COMPONENT_ARCHIVE_SRC=	none
COMPONENT_SRC=		
SOURCE_DIR=		$(COMPONENT_DIR)
CLEAN_PATHS +=		$(COMPONENT_DIR)/.prep $(COMPONENT_DIR)/.patched*

BUILD_STYLE=		archive
BUILD_TARGET +=		prep
TEST_TARGET= 		$(NO_TESTS)

DTDS_INC_FILE = 	$(BUILD_DIR)/manifest-$(MACH)-docbook-dtds.inc
BUILD_TARGET += 	$(DTDS_INC_FILE)
PUBLISH_TRANSFORMS +=	$(DTDS_INC_FILE)

### SGML DTD's

COMPONENT_VERSION_1 =	3.0
COMPONENT_ARCHIVE_1 =	docbk30.zip
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:ecf71cbe8ddbad7494ff520d5b4edf73a428c0b159178cb0cb619cba685e61c6

COMPONENT_VERSION_2 =	3.1
COMPONENT_ARCHIVE_2 =	docbk31.zip
COMPONENT_ARCHIVE_HASH_2 = \
    sha256:20261d2771b9a052abfa3d8fab1aa62be05791a010281c566f9073bf0e644538

COMPONENT_VERSION_3 =	4.0
COMPONENT_ARCHIVE_3 =	docbk40.zip
COMPONENT_ARCHIVE_HASH_3 = \
    sha256:dfef22f109779e4cfaafa27b6d381d975ac05eaafb5b3d4407d7043e310817bb

COMPONENT_VERSION_4 =	4.1
COMPONENT_ARCHIVE_4 =	docbk41.zip
COMPONENT_ARCHIVE_HASH_4 = \
    sha256:deaafcf0a3677692e7ad4412c0e41c1db3e9da6cdcdb3dd32b2cc1f9c97d6311

COMPONENT_VERSION_5 =	4.2
COMPONENT_ARCHIVE_5 =	docbook-4.2.zip
COMPONENT_ARCHIVE_HASH_5 = \
    sha256:67ebd2c94b342718c6865d2de60f5d4ff02d77a7e4b0d9e72a48c45f2b2635c3

COMPONENT_VERSION_6 =	4.3
COMPONENT_ARCHIVE_6 =	docbook-4.3.zip
COMPONENT_ARCHIVE_HASH_6 = \
    sha256:88f52fab7bd49b2e8f40c525014129c26a5a4b8bbd1494e00387556ec76f95ee

COMPONENT_VERSION_7 =	4.4
COMPONENT_ARCHIVE_7 =	docbook-4.4.zip
COMPONENT_ARCHIVE_HASH_7 = \
    sha256:0ac7960409b032c8e517483523ecb92af4e59196a33b3e2c5617daa22b7a8a6c

COMPONENT_VERSION_8 =	4.5
COMPONENT_ARCHIVE_8 =	docbook-4.5.zip
COMPONENT_ARCHIVE_HASH_8 = \
    sha256:8043e514e80c6c19cb146b5d37937d1305bf3abf9b0097c36df7f70f611cdf43

$(foreach n, 1 2 3 4 5 6 7 8, \
    $(eval COMPONENT_ARCHIVE_URL_$(n) = $(COMPONENT_PROJECT_URL)sgml/$(COMPONENT_VERSION_$(n))/$(COMPONENT_ARCHIVE_$(n))) \
    $(eval COMPONENT_ARCHIVE_URLS += $(COMPONENT_ARCHIVE_URL_$(n))) \
    $(eval COMPONENT_SRC_$(n) = $(COMPONENT_VERSION_$(n))-sgml) \
    $(eval UNPACK_ARGS_$(n) = -r $(COMPONENT_SRC_$(n))) \
    $(eval COMPONENT_POST_UNPACK_ACTION_$(n) += \
	$(SYMLINK) docbook.cat $(COMPONENT_SRC_$(n))/catalog ; \
	$(GSED) -e's,\(NAMELEN\s\+\)44\(\s\*\)\?,\1256,' -i.namelen \
	$(COMPONENT_SRC_$(n))/docbook.dcl ; ) \
    $(eval INSTALL_TARGET += \
	$(PROTOETCDIR)/sgml/sgml-docbook-$(COMPONENT_VERSION_$(n))-1.0-51.cat) \
)

### XML DTD's

COMPONENT_VERSION_50 =	4.1.2
COMPONENT_ARCHIVE_50 =	docbkx412.zip
COMPONENT_ARCHIVE_HASH_50 = \
    sha256:30f0644064e0ea71751438251940b1431f46acada814a062870f486c772e7772

COMPONENT_VERSION_51 =	4.2
COMPONENT_ARCHIVE_51 =	docbook-xml-4.2.zip
COMPONENT_ARCHIVE_HASH_51 = \
    sha256:acc4601e4f97a196076b7e64b368d9248b07c7abf26b34a02cca40eeebe60fa2

COMPONENT_VERSION_52 =	4.3
COMPONENT_ARCHIVE_52 =	docbook-xml-4.3.zip
COMPONENT_ARCHIVE_HASH_52 = \
    sha256:23068a94ea6fd484b004c5a73ec36a66aa47ea8f0d6b62cc1695931f5c143464

COMPONENT_VERSION_53 =	4.4
COMPONENT_ARCHIVE_53 =	docbook-xml-4.4.zip
COMPONENT_ARCHIVE_HASH_53 = \
    sha256:02f159eb88c4254d95e831c51c144b1863b216d909b5ff45743a1ce6f5273090

COMPONENT_VERSION_54 =	4.5
COMPONENT_ARCHIVE_54 =	docbook-xml-4.5.zip
COMPONENT_ARCHIVE_HASH_54 = \
    sha256:4e4e037a2b83c98c6c94818390d4bdd3f6e10f6ec62dd79188594e26190dc7b4

$(foreach n, 50 51 52 53 54, \
    $(eval COMPONENT_ARCHIVE_URL_$(n) = $(COMPONENT_PROJECT_URL)xml/$(COMPONENT_VERSION_$(n))/$(COMPONENT_ARCHIVE_$(n))) \
    $(eval COMPONENT_ARCHIVE_URLS += $(COMPONENT_ARCHIVE_URL_$(n))) \
    $(eval COMPONENT_SRC_$(n) = $(COMPONENT_VERSION_$(n))-xml) \
    $(eval UNPACK_ARGS_$(n) = -r $(COMPONENT_SRC_$(n))) \
    $(eval COMPONENT_POST_UNPACK_ACTION_$(n) += \
	$(SYMLINK) docbook.cat $(COMPONENT_SRC_$(n))/catalog ; ) \
    $(eval INSTALL_TARGET += \
	$(PROTOETCDIR)/sgml/xml-docbook-$(COMPONENT_VERSION_$(n))-1.0-51.cat) \
)

include $(WS_MAKE_RULES)/common.mk

$(PROTOETCDIR)/sgml:
	$(MKDIR) $@

$(PROTOETCDIR)/sgml/%.cat: $(PROTOETCDIR)/sgml
	$(TOUCH) $@

# generate the source-url metadata for the package manifest from all the URLs
$(DTDS_INC_FILE): $(BUILD_DIR)
	-$(RM) $@
	printf 'set name=info.source-url ' >> $@
	for url in $(COMPONENT_ARCHIVE_URLS) ; do \
	    printf ' value="%s" ' "$${url}" >> $@ ; \
	done
	print '' >> $@



REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
