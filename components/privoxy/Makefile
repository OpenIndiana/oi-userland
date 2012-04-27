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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		privoxy
COMPONENT_VERSION=	3.0.17
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-stable
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_PROJECT_URL=	http://www.privoxy.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:d1de36dc141180a5ab5e910507551564e958cc23a7d8daaa411e1564c208cd77
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/ijbswa/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
        (cd $(@D) ; \
            autoheader; \
            autoconf )

# Needed to installed most of the files into the proto area.
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)
	$(CP) $(BUILD_DIR_32)/templates/* $(PROTOETCDIR)/templates

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
