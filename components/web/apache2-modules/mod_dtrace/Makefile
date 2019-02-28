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
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_dtrace
COMPONENT_VERSION=	0.3.1
COMPONENT_REVISION=	4
COMPONENT_SRC=		src
COMPONENT_PROJECT_URL=	http://prefetch.net/projects/apache_modtrace/
COMPONENT_BUGDB=	utility/apache

include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

APXS = /usr/apache2/2.4/bin/apxs

DTRACE = /usr/sbin/dtrace -$(BITS)

COMPONENT_BUILD_ARGS += DTRACE="$(DTRACE)"
COMPONENT_BUILD_ARGS += APXS="$(APXS)"

COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"

COMPONENT_POST_BUILD_ACTION = $(TOUCH) $(BUILD_DIR)

download:

clobber: clean

$(SOURCE_DIR)/.prep: $(MAKEFILE_PREREQ)
	$(TOUCH) $@

clean::
	$(RM) $(SOURCE_DIR)/.prep

build: $(BUILD_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/server/apache-24
