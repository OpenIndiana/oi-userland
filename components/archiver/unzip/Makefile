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

COMPONENT_NAME=		unzip
COMPONENT_VERSION=	6.0
COMPONENT_REVISION=	5
COMPONENT_SRC=		$(COMPONENT_NAME)60
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:036d96991646d0449ed0aa952e4fbe21b476ce994abc276e49d30e686708bd37
COMPONENT_ARCHIVE_URL=	ftp://ftp.info-zip.org/pub/infozip/src/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.info-zip.org/UnZip.html
COMPONENT_BUGDB=	utility/zip
COMPONENT_FMRI=		compress/unzip

LD_OPTIONS=

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# remove the unwanted file.
COMPONENT_PREP_ACTION = $(RM) $(SOURCE_DIR)/crc_i386.S

COMPONENT_BUILD_ENV += \
 "LOCAL_UNZIP=-DUNICODE_SUPPORT -DNO_WORKING_ISPRINT -DUNICODE_WCHAR -DNO_LCHMOD"

# The Makefile we want is under unix/Makefile
COMPONENT_BUILD_ARGS    += -f unix/Makefile
COMPONENT_BUILD_TARGETS += generic CC="$(CC) $(CC_BITS)"
COMPONENT_INSTALL_ARGS  += -f unix/Makefile
COMPONENT_TEST_ARGS     += -f unix/Makefile

# This doesn't respect DESTDIR, so overload BINDIR and MANDIR when we install.
COMPONENT_INSTALL_ARGS += BINDIR=$(PROTOUSRBINDIR)
COMPONENT_INSTALL_ARGS += MANDIR=$(PROTOUSRSHAREMAN1DIR)

# common targets

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
