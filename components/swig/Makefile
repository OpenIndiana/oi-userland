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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		swig
COMPONENT_VERSION=	2.0.8
COMPONENT_PROJECT_URL=	http://www.swig.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:aeeefa20bbe1c03bacf23f0af9e7d6193e8b807b7585470615b71b1ee0c8ca4f
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/swig/swig/swig-2.0.8/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/swig

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=$(SPRO_VROOT)/bin:$(JAVA_HOME)/bin:/usr/bin

# This is needed because the community provided 'check' target is not viewpath aware
COMPONENT_PRE_CONFIGURE_ACTION =      ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += JAVA_HOME="$(JAVA_HOME)"
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS +=	--with-javaincl="$(JAVA_HOME)/include"

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

# Fails due to deprecated OCAML example and boost library problems
test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
