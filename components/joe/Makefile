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
# Copyright (c) 2013, Louis M. Picciano. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		joe
COMPONENT_VERSION=	3.7
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://joe-editor.sourceforge.net/
COMPONENT_SUMMARY=	Joe's Own Editor
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:cae456e1ad5a8c1d3c94920a3416c2347277739b260e3494d3bc0f2b9b73106f
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/joe-editor/JOE%20sources/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

COMPONENT_BUGDB=	editor/joe

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS	 +=	--sysconfdir=$(ETCDIR)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)
