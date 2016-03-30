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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tmux
COMPONENT_VERSION=	1.9
COMPONENT_MICRO_VERSION=	a
IPS_COMPONENT_VERSION=	1.9.1
HUMAN_VERSION=		$(COMPONENT_VERSION)$(COMPONENT_MICRO_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_PROJECT_URL=	http://tmux.sourceforge.net
COMPONENT_ARCHIVE_HASH=	\
    sha256:c5e3b22b901cf109b20dab54a4a651f0471abd1f79f6039d79b250d21c2733f5
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/tmux/files/tmux/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TPNO=			20510

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += shell/ksh93
