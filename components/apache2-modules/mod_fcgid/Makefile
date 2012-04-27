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

COMPONENT_NAME=		mod_fcgid
COMPONENT_VERSION=	2.3.6
COMPONENT_PROJECT_URL=	http://httpd.apache.org/mod_fcgid/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e831795498d91cf27a519ea1332c2a92a2a9920b0844d817b2ea7f079056d12b
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/httpd/mod_fcgid/$(COMPONENT_ARCHIVE)

include ../../../make-rules/prep.mk
include ../../../make-rules/justmake.mk
include ../../../make-rules/ips.mk

PATCH_LEVEL=0

APACHE_USR_PREFIX=/usr/apache2/2.2

$(BUILD_DIR_32)/.built:	APXS=$(APACHE_USR_PREFIX)/bin/apxs
$(BUILD_DIR_64)/.built:	APXS=$(APACHE_USR_PREFIX)/bin/$(MACH64)/apxs

COMPONENT_PRE_BUILD_ACTION= ( cd $(@D); APXS=$(APXS) ./configure.apxs )

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
