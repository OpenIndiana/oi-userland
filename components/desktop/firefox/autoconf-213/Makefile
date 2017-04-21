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
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		autoconf
COMPONENT_VERSION=	2.13
COMPONENT_ARCHIVE_HASH=	\
    sha256:35eb09ad59d78726349bfda05922f892453a2cbc6ec7fe54eb18615fb0c09fd5

TPNO=			34462

CONFIGURE_PREFIX=$(PROTO_DIR)

include $(WS_MAKE_RULES)/gnu-component.mk

# with ksh93 as the configure shell, all tests pass
CONFIG_SHELL=$(BINDIR)/ksh93


REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
