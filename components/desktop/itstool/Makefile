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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		itstool
COMPONENT_VERSION=	2.0.2
COMPONENT_PROJECT_URL=	http://itstool.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:bf909fb59b11a646681a8534d5700fec99be83bb2c57badf8c1844512227033a
COMPONENT_ARCHIVE_URL=	 http://files.itstool.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13109

TPNO=			25891

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# pkgdepend complains if it doesn't find a version of python specified
# Uses 2.7 as upstream is still working on Python 3 compatibility:
#  https://github.com/itstool/itstool/pull/3
CONFIGURE_OPTIONS += PYTHON="$(PYTHON.2.7)"

REQUIRED_PACKAGES += library/python/libxml2-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += text/gawk
