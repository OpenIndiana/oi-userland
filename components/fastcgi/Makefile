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

COMPONENT_NAME=		fcgi
COMPONENT_VERSION=	2.4.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:2329404159e8b8315e524b9eaf1de763202c6e6a
COMPONENT_ARCHIVE_URL=	http://www.fastcgi.com/dist/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

LIBNAME=        fcgi
LINTOUT=        lint.out

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --includedir=$(CONFIGURE_INCLUDEDIR)/fastcgi
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += CXXFLAGS="$(CFLAGS)"

PKG_PROTO_DIRS +=       $(COMPONENT_DIR)/$(COMPONENT_SRC)

COMPONENT_POST_BUILD_ACTION = \
         (cd $(@D); $(LINT) -nsvx $(CC_BITS) -o $(LIBNAME) -I$(@D) \
                        -I$(COMPONENT_DIR)/$(COMPONENT_SRC)/include \
                        $(COMPONENT_DIR)/llib-lfcgi > $(LINTOUT) 2>&1)

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(@D); $(INSTALL) llib-lfcgi.ln \
                        $(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS)))

# common targets
build:     $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:
	@echo "no tests available"

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk

