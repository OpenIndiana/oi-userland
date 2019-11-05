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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#
PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         wdiff
COMPONENT_VERSION=      1.2.2
COMPONENT_SUMMARY=      GNU wdiff - a front end to GNU diff for comparing files on a word per word basis
COMPONENT_PROJECT_URL=  http://www.gnu.org/software/wdiff/
COMPONENT_FMRI=         text/wdiff
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:34ff698c870c87e6e47a838eeaaae729fa73349139fc8db12211d2a22b78af6b
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/wdiff/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv3 

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS +=	CC="$(CC) $(CC_BITS)"
CONFIGURE_OPTIONS +=	--enable-experimental

CFLAGS_BUILD +=	-DDIFF_PROGRAM="$(GNUBINDIR)/diff"

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS) $(CFLAGS_BUILD)"

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "/^  [0-9]:/p"'

ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += text/gnu-diffutils
