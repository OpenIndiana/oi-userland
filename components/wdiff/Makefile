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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		wdiff
COMPONENT_VERSION=	1.1.0
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/wdiff/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b154bba7f5a6b76c9eff1ddd5d5850b0a6dc2332d2a1eda29444c68ecea7e5d1
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/wdiff/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/wdiff

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Needed to properly build the wdiff.info file to not include the
# experimental utilities (mdiff, unify and wdiff2).
COMPONENT_PRE_CONFIGURE_ACTION = \
	(cd $(SOURCE_DIR)/doc; $(RM) flags.texi)

CONFIGURE_OPTIONS +=	CC="$(CC) -m64"

CFLAGS +=	-DDIFF_PROGRAM="/usr/gnu/bin/diff"

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
