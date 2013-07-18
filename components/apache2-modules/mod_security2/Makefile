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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_security2
COMPONENT_VERSION=	2.7.4
COMPONENT_PROJECT_URL=	http://www.modsecurity.org/
COMPONENT_SRC_NAME=	modsecurity-apache
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:605d6f1b03e648001ef1c7db7b18d51c01edd443b57cbbd4e298770ffdcd0eb9
COMPONENT_ARCHIVE_URL= \
    $(COMPONENT_PROJECT_URL)tarball/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

APACHE_USR_PREFIX=/usr/apache2/2.2

APXS.32=	$(APACHE_USR_PREFIX)/bin/apxs
APXS.64=	$(APACHE_USR_PREFIX)/bin/$(MACH64)/apxs

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += LTFLAGS="--silent --tag=CC"
CONFIGURE_OPTIONS += --with-apxs=$(APXS.$(BITS))
CONFIGURE_OPTIONS += --with-apr=`$(APXS.$(BITS)) -q APR_CONFIG`
CONFIGURE_OPTIONS += --with-apu=`$(APXS.$(BITS)) -q APU_CONFIG`

COMPONENT_TEST_ARGS += CFLAGS="$(CFLAGS) -DMSC_TEST"

build: $(BUILD_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
