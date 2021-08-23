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
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcsh
COMPONENT_VERSION=	6.22.04
IPS_COMPONENT_VERSION=	6.22.4
COMPONENT_FMRI=		shell/tcsh
COMPONENT_CLASSIFICATION= System/Shells
COMPONENT_PROJECT_URL=	https://github.com/tcsh-org/tcsh
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:eb16356243218c32f39e07258d72bf8b21e62ce94bb0e8a95e318b151397e231
COMPONENT_ARCHIVE_URL=	ftp://ftp.astron.com/pub/tcsh/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	Copyright

include $(WS_MAKE_RULES)/common.mk

# Default GCC opt -O3 fails on GCC 6 & 7: https://bugs.astron.com/view.php?id=80
gcc_OPT = -O2

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Strip compilation lines from test output
COMPONENT_TEST_TRANSFORMS = \
	' -n "/^\s*[0-9]/p" '

# configure needs gencat
REQUIRED_PACKAGES += text/locale
# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
