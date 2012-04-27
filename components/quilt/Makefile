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

COMPONENT_NAME=		quilt
COMPONENT_VERSION=	0.60
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://savannah.nongnu.org/projects/quilt/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3d72a292e432beb9a73f9d0acfe3a77c9b4d7e42209919bb244e9958c7cfe64b
COMPONENT_ARCHIVE_URL=	http://download.savannah.gnu.org/releases/quilt/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
    (cd $(@D) ; autoconf )

PATCH_LEVEL=	0

# without this, some make messages end up in the
# generated README and man pages.
COMPONENT_BUILD_ARGS+=	--no-print-directory

# Quilt will need this option until Solaris has GNU getopt.
CONFIGURE_OPTIONS += --without-getopt

CONFIGURE_OPTIONS += --with-cp=/usr/gnu/bin/cp
CONFIGURE_OPTIONS += --with-date=/usr/gnu/bin/date
CONFIGURE_OPTIONS += --with-grep=/usr/gnu/bin/grep
CONFIGURE_OPTIONS += --with-tail=/usr/gnu/bin/tail
CONFIGURE_OPTIONS += --with-tr=/usr/gnu/bin/tr
CONFIGURE_OPTIONS += --with-sed=/usr/gnu/bin/sed
CONFIGURE_OPTIONS += --with-diff=/usr/gnu/bin/diff
CONFIGURE_OPTIONS += --with-find=/usr/gnu/bin/find
CONFIGURE_OPTIONS += --with-patch=/usr/gnu/bin/patch
CONFIGURE_OPTIONS += --with-perl=/usr/perl5/$(PERL_VERSION)/bin/perl
CONFIGURE_OPTIONS += --with-pod2man=/usr/perl5/$(PERL_VERSION)/bin/pod2man
CONFIGURE_OPTIONS += --with-xgettext=/usr/bin/gxgettext
CONFIGURE_OPTIONS += --with-msgfmt=/usr/bin/gmsgfmt

CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ARGS +=	BUILD_ROOT=$(PROTO_DIR)


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
