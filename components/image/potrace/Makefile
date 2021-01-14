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
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS=			32_and_64
PREFERRED_BITS=		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		potrace
COMPONENT_VERSION=	1.16
COMPONENT_SUMMARY=	tool and library for tracing a bitmap, which means, transforming a bitmap into a smooth, scalable image
COMPONENT_PROJECT_URL=	http://potrace.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:be8248a17dedd6ccbaab2fcc45835bb0502d062e40fbded3bc56028ce5eb7acc
COMPONENT_ARCHIVE_URL=	http://potrace.sourceforge.net/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			image/potrace
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE=		GPLv2

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--with-libpotrace=yes
CONFIGURE_OPTIONS +=	--disable-static

# Prevent test failure:
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
         '-n ' \
         '-e "/^ TOTAL:/p" ' \
         '-e "/^ PASS:/p" ' \
         '-e "/^ SKIP:/p" ' \
         '-e "/^ XFAIL:/p" ' \
         '-e "/^ FAIL:/p" ' \
         '-e "/^ XPASS:/p" ' \
         '-e "/^ ERROR:/p" ' \
         '-e "/^\# /p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
