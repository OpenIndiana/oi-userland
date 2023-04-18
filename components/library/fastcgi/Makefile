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

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         fastcgi
COMPONENT_VERSION=      2.4.2
COMPONENT_SUMMARY=      the FastCGI web server interface
COMPONENT_PROJECT_URL=  https://fastcgi-archives.github.io/
COMPONENT_SRC_NAME=		fcgi2
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1fe83501edfc3a7ec96bb1e69db3fd5ea1730135bd73ab152186fd0b437013bc
COMPONENT_ARCHIVE_URL=	https://github.com/FastCGI-Archives/fcgi2/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         library/fastcgi
COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_LICENSE=      FastCGI
COMPONENT_LICENSE_FILE= LICENSE.TERMS

#TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D) && \
	touch INSTALL NEWS AUTHORS ChangeLog COPYING && \
	autoreconf --force --install )

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --includedir=$(CONFIGURE_INCLUDEDIR)/fastcgi

COMPONENT_BUILD_ARGS=

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
