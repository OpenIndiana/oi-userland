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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cvs
COMPONENT_VERSION=	1.12.13
COMPONENT_REVISION=	2
COMPONENT_FMRI=	developer/versioning/cvs
COMPONENT_SUMMARY=	The CVS version control system
COMPONENT_CLASSIFICATION=	Development/Source Code Management
COMPONENT_PROJECT_URL=	http://www.nongnu.org/cvs/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:78853613b9a6873a30e1cc2417f738c330e75f887afdaf7b3d0800cb19ca515e
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnu.org/non-gnu/cvs/source/feature/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += -D__ATTRIBUTE_DISABLED

CONFIGURE_BINDIR.64 = $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS  +=	--with-external-zlib

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# "check" is not working yet.  It's asking for a password.
COMPONENT_TEST_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_TEST_TARGETS = localcheck

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
