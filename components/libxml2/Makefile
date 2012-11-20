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
COMPONENT_VERSION=	2.9.0
COMPONENT_PROJECT_URL=	http://xmlsoft.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ad25d91958b7212abdc12b9611cfb4dc4e5cddb6d1e9891532f48aacee422b82
COMPONENT_ARCHIVE_URL=	ftp://xmlsoft.org/libxml2/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libxml

# W3C XML Conformance Test Suites
COMPONENT_ARCHIVE_1= xmlts20080827.tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:96151685cec997e1f9f3387e3626d61e6284d4d6e66e0e440c209286c03e9cc7
COMPONENT_ARCHIVE_URL_1= http://www.w3.org/XML/Test/$(COMPONENT_ARCHIVE_1)

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
# Cannot link to lzma since it's not in /lib.
CONFIGURE_OPTIONS += --without-lzma
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS += PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES)

COMPONENT_PREP_ACTION += (cd $(@D) ; cp ../mapfile libxml2.syms ; autoreconf -if)

# After we have configured, make a copy of the python bits so we
# can build separate python 2.7 support.
COMPONENT_POST_CONFIGURE_ACTION = (cd $(@D) ; cp -rp python python2.7 ; \
			$(GSED) -i -e 's/2[.]6/2.7/g' python2.7/Makefile)

# After we have built/installed libxml2, build/install the python
# support for python 2.7
COMPONENT_POST_INSTALL_ACTION = \
    (cd $(@D)/python2.7 ; $(GMAKE) $(COMPONENT_INSTALL_ARGS) install)

COMPONENT_PRE_TEST_ACTION = (cd $(@D) ; gtar xf $(COMPONENT_DIR)/$(COMPONENT_ARCHIVE_1))

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
	$(PYTHON.2.6.32) -m compileall $(PROTO_DIR)/usr/lib/python2.6/vendor-packages
	$(PYTHON.2.7.32) -m compileall $(PROTO_DIR)/usr/lib/python2.7/vendor-packages

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
