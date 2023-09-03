#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
# Copyright 2019 Michal Nowak
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         slib
COMPONENT_VERSION=      3b7
IPS_COMPONENT_VERSION=  3.1.7
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      GNU slib - a portable library for the Scheme programming language
COMPONENT_DESCRIPTION=	SLIB is a portable scheme library providing compatibility and utility functions for standard Scheme implementations.
COMPONENT_PROJECT_URL=  https://people.csail.mit.edu/jaffer/SLIB.html
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= sha256:f5d5cdad335395a5a5aa37effe28aa8078b216ea39911f651929678f1ac228b6
COMPONENT_ARCHIVE_URL=  https://groups.csail.mit.edu/mac/ftpdir/scm/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/slib
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_LICENSE=      BSD-like, PD

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION = ( $(MV) $(COMPONENT_NAME) $(COMPONENT_SRC) )
COMPONENT_PRE_CONFIGURE_ACTION += $(CLONEY) $(SOURCE_DIR) $(@D)

# Remove configure options it does not understand, it is very simple.
# These as scripts, but binaries might look in the 32/64bit library path.
CONFIGURE_OPTIONS  = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))

COMPONENT_INSTALL_ENV += SCHEME_LIBRARY_PATH=$(SOURCE_DIR)

COMPONENT_INSTALL_ARGS += INSTALL=ginstall
COMPONENT_INSTALL_ARGS += INSTALL_INFO=install-info

# This disables regenerating the color database, which does not work
COMPONENT_PRE_INSTALL_ACTION += (touch $(SOURCE_DIR)/clrnamdb.scm);

# Manually added dependencies
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += text/texinfo
REQUIRED_PACKAGES += compress/gzip

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
