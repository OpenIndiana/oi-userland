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

COMPONENT_NAME=		unzip
COMPONENT_VERSION=	6.0
COMPONENT_SRC=		$(COMPONENT_NAME)60
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha1:abf7de8a4018a983590ed6f5cbd990d4740f8a22
COMPONENT_ARCHIVE_URL=	ftp://ftp.info-zip.org/pub/infozip/src/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=http://www.info-zip.org/UnZip.html

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

# remove the unwanted file.
COMPONENT_PREP_ACTION = $(RM) $(SOURCE_DIR)/crc_i386.S

COMPONENT_BUILD_ENV += \
 "LOCAL_UNZIP=-DUNICODE_SUPPORT -DNO_WORKING_ISPRINT -DUNICODE_WCHAR"

# The Makefile we want is under unix/Makefile
COMPONENT_BUILD_ARGS += -f unix/Makefile
COMPONENT_BUILD_TARGETS += generic
COMPONENT_INSTALL_ARGS += -f unix/Makefile

# This doesn't respect DESTDIR, so overload BINDIR and MANDIR when we install.
COMPONENT_INSTALL_ARGS += BINDIR=$(PROTOUSRBINDIR)
COMPONENT_INSTALL_ARGS += MANDIR=$(PROTOUSRSHAREMAN1DIR)

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
