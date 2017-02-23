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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS = 	64_and_32
COMPILER =	gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         jpeg
COMPONENT_VERSION=      6.0.2
HUMAN_VERSION=          v6b
COMPONENT_PROJECT_URL=  https://sourceforge.net/projects/libjpeg/
COMPONENT_SRC=          jpeg-6b
COMPONENT_SRC_NAME=     jpegsrc.$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC_NAME).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:75c3ec241e9996504fe02a9ed4d12f16b74ade713972f3db9e65ce95cd27e35d
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)files/libjpeg/6b/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libjpeg
COMPONENT_ANITYA_ID=	1628

TPNO=			9298

include $(WS_MAKE_RULES)/common.mk

LDFLAGS +=		$(CC_BITS)

CONFIGURE_OPTIONS +=	--prefix=$(PROTOUSRDIR)
CONFIGURE_OPTIONS +=	--enable-shared

CONFIGURE_ENV += INSTALL="$(INSTALL) -D"

# Prevent libtool from embedding runpath (via -R).
COMPONENT_POST_CONFIGURE_ACTION += \
	$(GSED) -i -e 's/hardcode_into_libs=yes/hardcode_into_libs=no/' $(@D)/libtool; \
	$(GSED) -i -e 's/hardcode_libdir_flag_spec=.*/hardcode_libdir_flag_spec=""/' $(@D)/libtool;

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += shell/ksh93
