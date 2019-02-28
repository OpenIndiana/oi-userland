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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_jk
COMPONENT_VERSION=	1.2.42
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://tomcat.apache.org/connectors-doc/
COMPONENT_SRC_NAME=	tomcat-connectors
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ea119f234c716649d4e7d4abd428852185b6b23a9205655e45554b88f01f3e31
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/tomcat/tomcat-connectors/jk/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

APXS = /usr/apache2/2.4/bin/apxs

CONFIGURE_SCRIPT = $(SOURCE_DIR)/native/configure

# Forcing CC from environment instead. Using one provided by apxs doesn't
# make mod_jk build.
CC=

CONFIGURE_OPTIONS += --with-apxs=$(APXS)

COMPONENT_PREP_ACTION += (cd $(SOURCE_DIR)/native && autoreconf -fi);

# Header files are missing during build without cloning.
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR)/native $(@D));

build: $(BUILD_64)

install: $(BUILD_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/server/apache-24
