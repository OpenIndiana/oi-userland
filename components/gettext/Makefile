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

COMPONENT_NAME=		gettext
COMPONENT_VERSION=	0.16.1
IPS_PKG_NAME=		text/gnu-gettext
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/gettext/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:8642f4346dfd6a18ecd883329e150bfe9e0886c3
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/gettext/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--disable-java
CONFIGURE_OPTIONS  +=		--disable-libasprintf
CONFIGURE_OPTIONS  +=		--without-emacs
CONFIGURE_OPTIONS  +=		--disable-openmp
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--disable-shared
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"

MAN1PAGES =	autopoint
MAN1PAGES +=	envsubst
MAN1PAGES +=	gettext
MAN1PAGES +=	gettextize
MAN1PAGES +=	msgattrib
MAN1PAGES +=	msgcat
MAN1PAGES +=	msgcmp
MAN1PAGES +=	msgcomm
MAN1PAGES +=	msgconv
MAN1PAGES +=	msgen
MAN1PAGES +=	msgexec
MAN1PAGES +=	msgfilter
MAN1PAGES +=	msgfmt
MAN1PAGES +=	msggrep
MAN1PAGES +=	msginit
MAN1PAGES +=	msgmerge
MAN1PAGES +=	msgunfmt
MAN1PAGES +=	msguniq
MAN1PAGES +=	ngettext
MAN1PAGES +=	xgettext

COMPONENT_POST_INSTALL_ACTION = \
	$(MAN_STABILITY) -n "GNU gettext" -p $(IPS_PKG_NAME) -s Uncommitted \
	    $(MAN1PAGES:%=$(PROTOUSRSHAREMAN1DIR)/%.1) ; \

include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
