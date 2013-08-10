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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		procmail
COMPONENT_VERSION=	3.22
COMPONENT_PROJECT_URL=	http://www.procmail.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:087c75b34dd33d8b9df5afe9e42801c9395f4bf373a784d9bc97153b0062e117
COMPONENT_BUGDB=	utility/procmail

# ftp://ftp.procmail.org/pub/procmail/procmail-3.22.tar.gz no longer works.
COMPONENT_ARCHIVE_URL=	ftp://ftp.ucsb.edu/pub/mirrors/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

COMPONENT_INSTALL_ARGS +=	BASENAME=$(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS +=	MANDIR=$(PROTOUSRSHAREMANDIR)

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
