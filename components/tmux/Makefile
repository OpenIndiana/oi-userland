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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tmux
COMPONENT_VERSION=	1.9
COMPONENT_MICRO_VERSION=	a
IPS_COMPONENT_VERSION=	1.9.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)$(COMPONENT_MICRO_VERSION)
COMPONENT_PROJECT_URL=	http://tmux.sourceforge.net
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c5e3b22b901cf109b20dab54a4a651f0471abd1f79f6039d79b250d21c2733f5
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/tmux/files/tmux/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/tmux

TPNO=			20510

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=	CXXFLAGS="$(CXXFLAGS)"

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
