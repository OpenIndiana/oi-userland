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

#
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		antlr
COMPONENT_VERSION=	2.7.7
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.antlr.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:853aeb021aef7586bda29e74a6b03006bcb565a755c86b66032d8ec31b67dbb9
COMPONENT_ARCHIVE_URL=	http://www.antlr2.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	java-class/antlr

# Use version of Java defined in ../../make-rules/shared-macros.mk
PATH=$(SPRO_VROOT)/bin:$(JAVA_HOME)/bin:/usr/bin

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATCH_LEVEL =		0

CONFIGURE_OPTIONS +=	--without-examples

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python2.6'
COMPONENT_POST_CONFIGURE_ACTION = \
	$(GSED) -i -e 's/env python/python2.7/' \
		$(BUILD_DIR_32)/scripts/pyantlr.sh

COMPONENT_INSTALL_ARGS += prefix=$(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS += libdir=$(PROTOUSRLIBDIR)
COMPONENT_INSTALL_ARGS += bindir=$(PROTOUSRBINDIR)
COMPONENT_INSTALL_ARGS += sbindir=$(PROTOUSRSBINDIR)

# Needed to find the antlr man page.
PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

COMPONENT_TEST_TARGETS = test

ASLR_MODE = $(ASLR_ENABLE)

CONFIGURE_ENV += PYTHON=$(PYTHON)

# common targets
build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TEST_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += runtime/python-27
