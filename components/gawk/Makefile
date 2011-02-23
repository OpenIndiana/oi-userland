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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gawk
COMPONENT_VERSION=	3.1.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:6cb385b4bc33780a5a4288b787523cbd4a30a900
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gawk/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS	+=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS	+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS	+=	CFLAGS="$(CFLAGS)"

include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32)

install:	$(PROTOGNUBIN) $(PROTOGNUSHAREMAN1) $(INSTALL_32)
	$(RM) $(PROTOGNUBIN)/awk
	$(SYMLINK) ../../bin/gawk $(PROTOGNUBIN)/awk
	$(RM) $(PROTOGNUSHAREMAN1)/awk.1
	$(SYMLINK) ../../../../share/man/man1/gawk.1 \
			$(PROTOGNUSHAREMAN1)/awk.1

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test: build
	@cd $(BUILD_DIR_32); $(MAKE) check

include ../../make-rules/depend.mk
