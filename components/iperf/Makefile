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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		iperf
COMPONENT_VERSION=	2.0.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/iperf/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:636b4eff0431cea80667ea85a67ce4c68698760a9837e1e9d13096d20362265b
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/iperf/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/iperf

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=	PTHREAD_CFLAGS=-pthreads

# these default to unnecessary gcc options, which
# are all that prevents us from using studio. so null them.
COMPONENT_BUILD_ARGS  +=	AM_CXXFLAGS=""
COMPONENT_BUILD_ARGS  +=	AM_CFLAGS=""

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
