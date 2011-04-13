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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxslt
COMPONENT_VERSION=	1.1.26
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:69f74df8228b504a87e2b257c2d5238281c65154
COMPONENT_ARCHIVE_URL=	ftp://xmlsoft.org/libxslt/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

LINT_FLAGS +=	-I/usr/include/libxml2 

CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-threads
CONFIGURE_OPTIONS += --with-python=$(PYTHON.$(BITS))
CONFIGURE_OPTIONS += --without-crypto
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS += PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES)

COMPONENT_TEST_TARGETS = tests

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; cp ../mapfile.xslt libxslt/libxslt.syms ; \
		    cp ../mapfile.exslt libexslt/libexslt.syms ; \
		    $(RM) libxslt/xsltconfig.h libexslt/exsltconfig.h ; \
		    libtoolize --force --copy ; aclocal-1.10 ; \
		    automake-1.10 --addmissing --copy ; autoconf)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

