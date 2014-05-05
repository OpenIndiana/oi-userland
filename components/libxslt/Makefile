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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxslt
COMPONENT_VERSION=	1.1.28
COMPONENT_PROJECT_URL=	http://xmlsoft.org/XSLT/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5fc7151a57b89c03d7b825df5a0fae0a8d5f05674c0e7cf2937ecec4d54a028c
COMPONENT_ARCHIVE_URL=	ftp://xmlsoft.org/libxslt/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libxslt

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

LINT_FLAGS +=	-I/usr/include/libxml2 

CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-python=$(PYTHON.$(BITS))
CONFIGURE_OPTIONS += --without-crypto
CONFIGURE_OPTIONS += --with-html-dir=/usr/share/lib/xslt/doc
CONFIGURE_OPTIONS += --with-html-subdir=html
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS += PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES)

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; cp ../mapfile.xslt libxslt/libxslt.syms ; \
		    $(RM) libxslt/xsltconfig.h libexslt/exsltconfig.h ; \
		    libtoolize --force --copy ; aclocal ; \
		    automake --addmissing --copy ; autoconf)

# After we have configured, make a copy of the python bits so we
# can build separate python 2.7 support.
COMPONENT_POST_CONFIGURE_ACTION = (cd $(@D) ; cp -rp python python2.7)

# After we have built/installed libxslt, rebuild/install the python
# support for python 2.7
COMPONENT_POST_INSTALL_ACTION = \
    (cd $(@D)/python2.7 ; $(GMAKE) $(COMPONENT_INSTALL_ARGS) \
                                PYTHON=$(PYTHON.2.7.$(BITS)) \
                                PYTHON_VERSION=2.7 \
                                PYTHON_INCLUDES=/usr/include/python2.7 \
                                PYTHON_LIBS=$(PYTHON.2.7.VENDOR_PACKAGES) \
                                PYTHON_SITE_PACKAGES=$(PYTHON.2.7.VENDOR_PACKAGES) \
                                install)



# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
	$(PYTHON.2.6.32) -m compileall $(PROTO_DIR)/usr/lib/python2.6/vendor-packages
	$(PYTHON.2.7.32) -m compileall $(PROTO_DIR)/usr/lib/python2.7/vendor-packages

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

