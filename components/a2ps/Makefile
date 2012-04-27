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
# Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		a2ps
COMPONENT_VERSION=	4.14
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/a2ps/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f3ae8d3d4564a41b6e2a21f237d2f2b104f48108591e8b83497500182a3ab3a4
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/a2ps/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# don't use LD_Z_IGNORE: causes linker problems
LD_Z_IGNORE=

CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--sysconfdir=/etc/gnu
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--with-medium=letter
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"

# because viewpathing isn't quite right in this version of a2ps
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; ln -s $(SOURCE_DIR)/auxdir/mkinstalldirs)
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D)/doc ; \
	 ln -s $(SOURCE_DIR)/doc/make-authors.pl ; \
	 ln -s $(SOURCE_DIR)/doc/translators.txt) ; \
	(cd $(@D)/sheets ; \
	 for sheet in $(SOURCE_DIR)/sheets/*.ssh ; do \
	     ln -s $$sheet ; \
	 done)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
