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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=             32_and_64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		startup-notification
COMPONENT_VERSION=	0.12
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/startup-notification/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
   sha256:3c391f7e930c583095045cd2d10eb73a64f085c7fde9d260f2652c7cb3cfbe4a
COMPONENT_ARCHIVE_URL=	http://www.freedesktop.org/software/$(COMPONENT_NAME)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/libraries

TPNO=			24899

# gmake check works but produces no useful output
TEST_TARGET = $(SKIP_TEST)

# May build on S11 but will conflict with gnome-libs
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --with-x

REQUIRED_PACKAGES += developer/build/automake
REQUIRED_PACKAGES += developer/build/gnu-make
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/xcb-util
