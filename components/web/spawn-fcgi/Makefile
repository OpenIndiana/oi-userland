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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		spawn-fcgi
COMPONENT_VERSION=	1.6.5
COMPONENT_SUMMARY=	spawn-fcgi is used to spawn FastCGI applications
COMPONENT_PROJECT_URL=	https://www.lighttpd.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a72d7bf7fb6d1a0acda89c93d4f060bf77a2dba97ddcfecd00f11e708f592c40
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			web/fastcgi/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Web Services/Application and Web Servers
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
