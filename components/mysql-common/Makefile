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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mysql-common
COMPONENT_VERSION=	5.11
COMPONENT_PROJECT_URL=	http://dev.mysql.com/
COMPONENT_BUGDB=	database/mysql

include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# ASLR Mode should be set as not applicable
ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# nothing to download or build; just package
download prep build install test:

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

clobber:	clean
