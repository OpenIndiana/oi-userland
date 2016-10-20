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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		docbook-xsl
COMPONENT_VERSION=	1.75.2
COMPONENT_PROJECT_URL=	http://docbook.sourceforge.net/
# docs are in a separate tarball that unpacks into a subdirectory
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SRC_1= \
    $(COMPONENT_SRC:$(COMPONENT_NAME)-%=$(COMPONENT_NAME)-doc-%)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_1= 	$(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:0dcc3aebd2ada8719e47b77c62ab986c4f2747f9a7cab6f629b6472e6d058e09
COMPONENT_ARCHIVE_HASH_1= \
    sha256:e28ab23e61870204f7e693ee204c01fa802c06c8b5da45ae6b65450628f6a8f9
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/docbook/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL_1=$(COMPONENT_ARCHIVE_URL:$(COMPONENT_ARCHIVE)=$(COMPONENT_ARCHIVE_1))
COMPONENT_BUGDB=	utility/docbook

TPNO=			9656

TEST_TARGET = $(NO_TESTS)

PKG_VARS += COMPONENT_ARCHIVE_URL_1

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

# Docs archive tries to unpack into a subdir of the main archive, so we
# need to redirect to its own source dir to make userland-unpack work
UNPACK_ARGS_1= -r $(COMPONENT_SRC_1) 

# Install the subset of files we want to package, so it's easier to
# generate sample-manifests consistently from new versions
XSL_DIR=/usr/share/sgml/docbook/xsl-stylesheets-$(COMPONENT_VERSION)
DOC_DIR=/usr/share/doc/docbook-style-xsl/doc
GNUTAR = $(GNUBIN)/tar

install:        $(SOURCE_DIR)/.prep
	-$(RM) -r $(PROTO_DIR)/usr
	$(MKDIR) $(PROTO_DIR)$(XSL_DIR) $(PROTO_DIR)$(DOC_DIR)
	$(GNUTAR) -C $(SOURCE_DIR) --exclude-ignore=$(COMPONENT_DIR)/exclude \
		-cf - . | $(GNUTAR) -C $(PROTO_DIR)$(XSL_DIR) -xf -
	$(GNUTAR) -C $(SOURCE_DIR_1)/$(COMPONENT_SRC)/doc -cf - . \
		| $(GNUTAR) -C $(PROTO_DIR)$(DOC_DIR) -xf -
	$(SYMLINK) VERSION $(PROTO_DIR)$(XSL_DIR)/VERSION.xsl

# Used in SMF method scripts:
REQUIRED_PACKAGES += data/xml-common
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/bash
# SMF manifest dependencies:
REQUIRED_PACKAGES += system/core-os
