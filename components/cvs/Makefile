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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cvs
COMPONENT_VERSION=	1.12.13
COMPONENT_PROJECT_URL=	http://www.nongnu.org/cvs/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:78853613b9a6873a30e1cc2417f738c330e75f887afdaf7b3d0800cb19ca515e
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/non-gnu/cvs/source/feature/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	384

TPNO=			6323

SYSTEM_TEST_TARGET= $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -D__ATTRIBUTE_DISABLED
CONFIGURE_OPTIONS  +=	--with-external-zlib

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

# need gnu grep
COMPONENT_TEST_ENV += PATH=$(GNUBIN):$(PATH)
# "check" is not working yet.  It's asking for a password.
COMPONENT_TEST_TARGETS = localcheck

# mimic localcheck from src/Makefile
COMPONENT_SYSTEM_TEST_DIR = $(SOURCE_DIR)/src
COMPONENT_SYSTEM_TEST_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_SYSTEM_TEST_CMD = ./sanity.sh
COMPONENT_SYSTEM_TEST_ARGS = $(USRBINDIR)/cvs
COMPONENT_SYSTEM_TEST_TARGETS =

# extract just the final results
# delete make lines
# delete cp lines
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^This/,/^make/!d" ' \
	'-e "/^[mM]ake/d" ' \
	'-e "/^cp.*/d" '

REQUIRED_PACKAGES += library/zlib
