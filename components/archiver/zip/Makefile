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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zip
COMPONENT_VERSION=	3.0
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.info-zip.org/Zip.html
COMPONENT_SRC=		$(COMPONENT_NAME)30
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f0e8bb1f9b7eb0b01285495a2699df3a4b766784c1765a8f1aeedf63c0806369
COMPONENT_ARCHIVE_URL=	ftp://ftp.info-zip.org/pub/infozip/src/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/zip
COMPONENT_FMRI=		compress/zip

LD_OPTIONS=

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# remove the unwanted file.
COMPONENT_PREP_ACTION = rm -f $(SOURCE_DIR)/match.S

# The Makefile we want is under unix/Makefile
COMPONENT_BUILD_ARGS    += -f unix/Makefile
COMPONENT_BUILD_TARGETS += generic CC="$(CC) $(CC_BITS)"
COMPONENT_INSTALL_ARGS  += -f unix/Makefile

# This doesn't respect DESTDIR, so overload BINDIR and MANDIR when we install.
COMPONENT_INSTALL_ARGS += BINDIR=$(PROTOUSRBINDIR)
COMPONENT_INSTALL_ARGS += MANDIR=$(PROTOUSRSHAREMAN1DIR)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += system/library
