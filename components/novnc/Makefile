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
# Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		noVNC
COMPONENT_VERSION=	0.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6d702a628c85384118d85d51225770a78dd62d805229f56e42b92798c87baa31
COMPONENT_ARCHIVE_URL=  https://github.com/kanaka/noVNC/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://kanaka.github.io/noVNC
COMPONENT_BUGDB=	utility/novnc
COMPONENT_ANITYA_ID=	13226

TPNO=			18799

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:          prep

install:	build

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

clean::
	$(RM) -r $(BUILD_DIR)
