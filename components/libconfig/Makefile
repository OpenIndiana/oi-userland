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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libconfig
COMPONENT_VERSION=	1.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://github.com/hyperrealm/libconfig
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:18739792eb463d73525d7aea9b0a48b14106fae1cfec09aedc668d8c1079adf1
COMPONENT_ARCHIVE_URL=	https://github.com/hyperrealm/libconfig/archive/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libconfig
COMPONENT_FMRI=		library/libconfig
COMPONENT_SUMMARY=	C/C++ library for processing configuration files
COMPONENT_CLASSIFICATION= System/Libraries

COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_LICENSE=	GPLv2


include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        (rm -f $(SOURCE_DIR)/lib/scanner.{c,h} && $(CLONEY) $(SOURCE_DIR) $(@D) )

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
