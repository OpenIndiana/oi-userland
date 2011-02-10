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
# Copyright (c) 2010, 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		a2ps
COMPONENT_VERSION=	4.13
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)b.tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:cfc79a3e54115e569f667fa3fd2c2ec16d22b31a
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/a2ps/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

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
	 for sheet in $(SOURCE_DIR)/sheets/*.ssh ; do ; \
	     ln -s $$sheet ; \
	 done)

SFWPROGS =	a2ps card composeglyphs fixnt fixps ogonkify pdiff psmandup \
		psset texi2dvi4a2ps

PROTOETCLPFD = $(PROTO_DIR)/etc/lp/fd
FILTERDEFS =	a2ps.fd
PROTOFILTERDEFS = $(FILTERDEFS:%=$(PROTOETCLPFD)/%)

$(PROTOFILTERDEFS):	$(PROTOETCLPFD)
	$(INSTALL) -m 444 $(@F) $(@D)

$(PROTOETCLPFD):	$(INSTALL_32)
	$(MKDIR) $@

include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) $(PROTOFILTERDEFS) $(PROTOSFWLINKS)

test: build
	@cd $(BUILD_DIR_32); $(MAKE) check

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
