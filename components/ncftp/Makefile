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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ncftp
COMPONENT_VERSION=	3.2.5
COMPONENT_PROJECT_URL=	http://www.ncftp.com/ncftp/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:b4ebe2415761a5137cd1d313c8fc1352f26d8963cc9e9e354e29720aa2089d42
COMPONENT_ARCHIVE_URL=	ftp://ftp.ncftp.com/ncftp/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/ncftp-client

TPNO=			24893

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --srcdir=$(BUILD_DIR_64) 
