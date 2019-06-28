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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		slib
COMPONENT_VERSION=	3b5
COMPONENT_FMRI=		library/slib
COMPONENT_PROJECT_URL=	http://people.csail.mit.edu/jaffer/SLIB/
COMPONENT_SUMMARY=	GNU slib - a portable library for the Scheme programming language
COMPONENT_DESCRIPTION=	SLIB is a portable scheme library providing compatibility and utility functions for standard Scheme implementations.
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:f8b64a9820c2ccbdb263a0cb7bcf4caadce0857fdf4e2f52111ca33b4a131760
COMPONENT_ARCHIVE_URL=	http://groups.csail.mit.edu/mac/ftpdir/scm/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= 	BSD-like, PD
COMPONENT_CLASSIFICATION=Development/Other Languages

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Lie to IPS packaging about the version because it doesn't like
# COMPONENT_VERSION's with letters.
# So if COMPONENT_VERSION changes above this needs to change as well.
IPS_COMPONENT_VERSION=  3.1.5

COMPONENT_PRE_CONFIGURE_ACTION += $(CLONEY) $(SOURCE_DIR) $(@D)

# Remove configure options it does not understand, it is very simple.
# These as scripts, but binaries might look in the 32/64bit library path.
CONFIGURE_OPTIONS  = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))

COMPONENT_INSTALL_ARGS += INSTALL=ginstall
COMPONENT_INSTALL_ARGS += INSTALL_INFO=install-info

# nothing to really build
build:	$(BUILD_32)

install: $(INSTALL_32)

test:	$(NO_TESTS)

REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += text/texinfo
REQUIRED_PACKAGES += compress/gzip
# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
