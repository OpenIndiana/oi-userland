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

COMPONENT_NAME=		swig
COMPONENT_VERSION=	1.3.35
COMPONENT_PROJECT_URL=	http://www.swig.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2b03c44c8802e16ff4a493dd486de23c027fd5a46dedb08bf7561171b16cd084
COMPONENT_ARCHIVE_URL=	http://iweb.dl.sourceforge.net/project/swig/swig/swig-1.3.35/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# This is needed because the community provided 'check' target is not viewpath aware
COMPONENT_PRE_CONFIGURE_ACTION =      ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CXXFLAGS)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

# Fails due to deprecated OCAML example and boost library problems
test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
