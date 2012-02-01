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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxml2
COMPONENT_VERSION=	2.7.6
COMPONENT_PROJECT_URL=	http://xmlsoft.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:b0f6bf8408e759ac4b8b9650005ee8adea911e1d
COMPONENT_ARCHIVE_URL=	ftp://xmlsoft.org/libxml2/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-threads
CONFIGURE_OPTIONS += --with-python=$(PYTHON.$(BITS))
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS += PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES)

COMPONENT_PREP_ACTION += (cd $(@D) ; cp ../mapfile libxml2.syms ; autoreconf -if)

COMPONENT_TEST_TARGETS = tests

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
	$(PYTHON.2.6.32) -m compileall $(PROTO_DIR)/usr/lib/python2.6/vendor-packages

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
