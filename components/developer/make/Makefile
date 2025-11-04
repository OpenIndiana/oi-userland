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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		make
COMPONENT_VERSION=	4.4.1
COMPONENT_SUMMARY=	A utility for directing compilation
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/make/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:dd16fb1d67bfab79a72f5e8390735c49e3e8e70b4945a15ab1f81ddb78658fb3
COMPONENT_FMRI=		developer/build/gnu-make
COMPONENT_CLASSIFICATION=	Development/GNU
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/make/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPL-3.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --program-prefix=g
CONFIGURE_OPTIONS += --with-guile

ASLR_MODE = $(ASLR_ENABLE)

# Strip compilation lines from test output
COMPONENT_TEST_TRANSFORMS += "-e '/^Clearing /d'"
COMPONENT_TEST_TRANSFORMS += -n
COMPONENT_TEST_TRANSFORMS += "-e '/^-------/,/^======/p'"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += system/library
