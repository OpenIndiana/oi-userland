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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		groff
COMPONENT_VERSION=	1.19.2
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/groff/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:d864fbd0bf6dea24e4f71736da9902a1cae86d0a1a893b5fe17118927257ec3e
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/groff

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION = \
	( cd $(@D) ; \
		libtoolize -force ; \
		aclocal -I. ; \
		autoconf ; \
		autoheader )

# The grog.sh script needs GNU awk not the Solaris one.
COMPONENT_PRE_CONFIGURE_ACTION = \
	$(GSED) -i -e 's?awk?/usr/gnu/bin/awk?' \
		$(SOURCE_DIR)/src/roff/grog/grog.sh

CONFIGURE_OPTIONS += \
    --with-appresdir=$(CONFIGURE_PREFIX)/X11/lib/X11/app-defaults

CONFIGURE_OPTIONS +=	CXX="$(CXX)"
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ARGS += prefix=$(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS += bindir=$(PROTOUSRBINDIR)
COMPONENT_INSTALL_ARGS += libdir=$(PROTOUSRLIBDIR)
COMPONENT_INSTALL_ARGS += mandir=$(PROTOUSRSHAREMANDIR)
COMPONENT_INSTALL_ARGS += legacyfontdir=$(PROTOUSRLIBDIR)/font
COMPONENT_INSTALL_ARGS += appresdir=$(PROTOUSRDIR)/X11/lib/X11/app-defaults
COMPONENT_INSTALL_ARGS += sys_tmac_prefix=$(PROTOUSRSHARELIBDIR)/tmac/

COMPONENT_PRE_INSTALL_ACTION = \
	($(MKDIR) $(PROTOUSRBINDIR) )

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

# groff tests use dejagnu which isn't currently included in Solaris.
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
