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

COMPONENT_NAME=		enscript
COMPONENT_VERSION=	1.6.4
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/enscript
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:45299a4db47c9c08c3649d4f62b211ae79ef5143360c264a40371a728f6ad99b
COMPONENT_ARCHIVE_URL=  http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/enscript

# Ruby enscript support
COMPONENT_ARCHIVE_1=    ruby-enscript.tar.gz
COMPONENT_ARCHIVE_HASH_1=       \
    sha256:29c87c4cd5d36b221fd50ad0b2e35a2cc0e1422519bb7f41d400c61db117cff7
COMPONENT_ARCHIVE_URL_1= http://neugierig.org/software/ruby/ruby-enscript.tar.gz

# PHP enscript support
COMPONENT_ARCHIVE_2=    php.st
COMPONENT_ARCHIVE_HASH_2=	\
    sha256:64d5b1ed1044202cda1ddcd591a966d1faff58d60156c4368d485f0405d7a9ee
COMPONENT_ARCHIVE_URL_2= http://home.raxnet.net/downloads/viewcvs/php.st

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 1

# Get just the ruby enscript support file out of the downloaded tarball, and
# move ruby.st and php.st into the correct directory for "gmake install".
COMPONENT_PREP_ACTION = \
	/usr/bin/tar xvf $(COMPONENT_ARCHIVE_1) ruby.st ; \
	$(MV) php.st ruby.st $(SOURCE_DIR)/states/hl ;

# There are patches that change a Makefile.am and configure.in
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf -fiv);

# Needed so that enscript can find the enscript.cfg file.
CONFIGURE_OPTIONS +=    --sysconfdir=/etc

CONFIGURE_OPTIONS +=	--with-media=Letter
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
