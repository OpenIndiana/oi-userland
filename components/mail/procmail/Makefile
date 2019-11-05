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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		procmail
COMPONENT_VERSION=	3.22
COMPONENT_REVISION=	4
COMPONENT_PROJECT_URL=	http://www.procmail.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:087c75b34dd33d8b9df5afe9e42801c9395f4bf373a784d9bc97153b0062e117

# ftp://ftp.procmail.org/pub/procmail/procmail-3.22.tar.gz no longer works.
COMPONENT_ARCHIVE_URL=	 ftp://ftp.informatik.rwth-aachen.de/pub/packages/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_INSTALL_ARGS +=	BASENAME=$(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS +=	MANDIR=$(PROTOUSRSHAREMANDIR)

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += RPM_OPT_FLAGS="$(CC_BITS)"

# common targets
build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
