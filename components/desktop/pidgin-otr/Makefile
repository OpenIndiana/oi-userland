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
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pidgin-otr
COMPONENT_VERSION=	4.0.2
COMPONENT_PROJECT_URL=	http://www.cypherpunks.ca/otr/
COMPONENT_ARCHIVE_HASH= \
    sha256:f4b59eef4a94b1d29dbe0c106dd00cdc630e47f18619fc754e5afbf5724ebac4
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        utility/pidgin
COMPONENT_ANITYA_ID=	10240

TPNO=			27403

# Pidgin is on the do-not-publish list (depends on S12-only changes in ON &
# Desktop), so no point publishing this without that.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Need to pick up the GNU version of xgettext.
PATH=$(GNUBIN):$(USRBINDIR)

CFLAGS +=		-DG_IMPLEMENT_INLINES -DG_HAVE_ISO_VARARGS

REQUIRED_PACKAGES += communication/im/libotr
REQUIRED_PACKAGES += communication/im/pidgin
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += system/library/security/libgcrypt
