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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_dtrace
COMPONENT_VERSION=	0.3.1
COMPONENT_SRC=		src

include ../../../make-rules/justmake.mk
include ../../../make-rules/ips.mk

APACHE_USR_PREFIX=/usr/apache2/2.2

$(BUILD_DIR_32)/.built:	COMPONENT_BUILD_ARGS +=	APXS=$(APACHE_USR_PREFIX)/bin/apxs
$(BUILD_DIR_64)/.built:	COMPONENT_BUILD_ARGS +=	APXS=$(APACHE_USR_PREFIX)/bin/$(MACH64)/apxs
$(BUILD_DIR_32)/.built:	COMPONENT_BUILD_ARGS +=	DTRACE="/usr/sbin/dtrace -32"
$(BUILD_DIR_64)/.built:	COMPONENT_BUILD_ARGS +=	DTRACE="/usr/sbin/dtrace -64"

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

download:

clobber: clean

$(SOURCE_DIR)/.prep:
	$(TOUCH) $@

clean::
	$(RM) $(SOURCE_DIR)/.prep

build: $(BUILD_32_and_64)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
