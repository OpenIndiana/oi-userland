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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		guile
COMPONENT_VERSION=	1.8.6
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/guile/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:69a2f9491480ff756d1cc4c8ea2bdc13d40ea8ddc8f93f26957bade8219a1d86
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/guile/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Built in SFW with gcc and builds cleanly now only with gcc
COMPILER = gcc
CONFIGURE_OPTIONS +=	CPPFLAGS="-I/usr/include/gmp -D__USE_LEGACY_PROTOTYPES__"
CONFIGURE_OPTIONS +=	--disable-static 
CONFIGURE_OPTIONS +=	--disable-error-on-warning
CONFIGURE_OPTIONS +=	ac_cv_type_complex_double=no
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
