#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2020, Aurelien Larcher. All rights reserved.
#
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		liblangtag
COMPONENT_VERSION=	0.6.3
COMPONENT_REVISION=	1
COMPONENT_FMRI=     	library/liblangtag
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	http://tagoh.github.io/liblangtag/
COMPONENT_SUMMARY=      liblangtag - library to access/deal with tags for identifying languages (RFC 5646)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:1f12a20a02ec3a8d22e54dedb8b683a43c9c160bda1ba337bf1060607ae733bd
COMPONENT_ARCHIVE_URL=	https://bitbucket.org/tagoh/liblangtag/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      LGPLv3, MPLv2

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

unexport SHELLOPTS

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
