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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tomcat-connectors
COMPONENT_VERSION=	1.2.28
COMPONENT_PROJECT_URL=	http://tomcat.apache.org/connectors-doc/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:898fddced320754121b53b3292d1d20a31bebc6733d5aeb92367143f8941fe6f
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/tomcat/tomcat-connectors/jk/source/jk-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

PATCH_LEVEL=0

APACHE_USR_PREFIX=/usr/apache2/2.2

CONFIGURE_SCRIPT = $(SOURCE_DIR)/native/configure

# Forcing CC from environment instead. Using one provided by apxs doesn't
# make mod_jk build.
CC=

CONFIGURE_OPTIONS.32 += --with-apxs=$(APACHE_USR_PREFIX)/bin/apxs
CONFIGURE_OPTIONS.64 += --with-apxs=$(APACHE_USR_PREFIX)/bin/$(MACH64)/apxs

# Header files are missing during build without cloning.
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR)/native $(@D));

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

build: $(BUILD_32_and_64)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
