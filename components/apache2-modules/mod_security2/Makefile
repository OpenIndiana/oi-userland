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

COMPONENT_NAME=		modsecurity-apache
COMPONENT_VERSION=	2.5.9
COMPONENT_PROJECT_URL=	http://www.modsecurity.org/
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:02352221ea268f8ae9aae5b84507f51eba2a67c0f7d2efd5cc88e85f1f394056
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

APACHE_USR_PREFIX=/usr/apache2/2.2

APXS.32=	$(APACHE_USR_PREFIX)/bin/apxs
APXS.64=	$(APACHE_USR_PREFIX)/bin/$(MACH64)/apxs

CONFIGURE_OPTIONS +=	LTFLAGS="--silent --tag=CC"
CONFIGURE_OPTIONS += --with-apxs=$(APXS.$(BITS))
CONFIGURE_OPTIONS += --with-apr=`$(APXS.$(BITS)) -q APR_CONFIG`
CONFIGURE_OPTIONS += --with-apu=`$(APXS.$(BITS)) -q APU_CONFIG`

# Need to get right version of C compiler and GNU sed first.
PATH=$(SPRO_VROOT)/bin:/usr/gnu/bin:/usr/bin

# Some patches need configure script re-creation.
COMPONENT_PREP_ACTION = (cd $(@D)/apache2; autoconf)

CONFIGURE_SCRIPT = $(SOURCE_DIR)/apache2/configure

# Header files are missing during build without cloning.
COMPONENT_PRE_BUILD_ACTION += ($(CLONEY) $(SOURCE_DIR)/apache2 $(@D));

build: $(BUILD_32_and_64)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
