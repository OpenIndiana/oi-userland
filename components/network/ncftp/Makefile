
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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ncftp
COMPONENT_VERSION=	3.2.6
COMPONENT_FMRI=         network/ftp/ncftp
COMPONENT_SUMMARY=      NcFTP - client application implementing FTP
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_PROJECT_URL=	http://www.ncftp.com/ncftp/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.xz
COMPONENT_ARCHIVE_HASH=	\
  sha256:5f200687c05d0807690d9fb770327b226f02dd86155b49e750853fce4e31098d
COMPONENT_ARCHIVE_URL=	ftp://ftp.ncftp.com/ncftp/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= Artistic

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --srcdir=$(BUILD_DIR_$(BITS)) 

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:	$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
