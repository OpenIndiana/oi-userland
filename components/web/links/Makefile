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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		links
COMPONENT_VERSION=	2.20.1
COMPONENT_SUMMARY=	Text based web browser
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://links.twibright.com/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:17619208e75bb45890982b37b834c70cf9c56b6f9f98aadb787efd6a88db7e86
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_FMRI=		web/browser/links
COMPONENT_LICENSE=	GPLv2

TEST_TARGET=	$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Configure in links does not understand CC, CXX, etc.  Need to generate a
# new configure for it to configure and build properly.
COMPONENT_PREP_ACTION=	( cd $(@D) ; autoconf )

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
