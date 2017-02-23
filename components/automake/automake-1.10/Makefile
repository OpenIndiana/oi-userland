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
BUILD_BITS= NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		automake
COMPONENT_VERSION=	1.10
COMPONENT_ARCHIVE_HASH=	\
    sha256:d92c77acdc3b132ff6b2de06a1321654a556defa21b7dd3e8d4829434ed64e8e
COMPONENT_ANITYA_ID=	144

TPNO=			6149

include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_OPTIONS  += --infodir=$(USRSHAREDIR)/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/info
CONFIGURE_OPTIONS  += PERL="$(PERL)"

REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
