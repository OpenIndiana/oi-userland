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
# Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		d3
COMPONENT_VERSION=	4.4.4
COMPONENT_PROJECT_URL=	https://d3js.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:b53bd6835c4ac35c245397004e3613a6c649ced019637a4414d762b20cf2a977
COMPONENT_ARCHIVE_URL=	https://github.com/d3/d3/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB= 	javascript/d3
COMPONENT_ANITYA_ID=	13484

TPNO=			33646

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

# By default, the pre-built d3 zip file will just unpack its files into
# the component directory. Change this so that the various other "gmake ..."
# targets work nicely.
UNPACK_ARGS =	-r $(COMPONENT_SRC)

publish:	download prep

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)
