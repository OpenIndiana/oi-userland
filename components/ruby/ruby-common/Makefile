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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ruby-meta
# the latest version of Ruby
COMPONENT_VERSION=	2.6
COMPONENT_PROJECT_URL=	http://www.ruby-lang.org/
COMPONENT_BUGDB=	utility/ruby

include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# This package delivers no files and has no dependencies.
EXTDEPFILES = $(NULLDEPFILE)
LICENSE_TRANSFORMS=

# nothing to download or build; just publish the package
download prep build install test:

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

clobber:	clean
