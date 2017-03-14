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

COMPONENT_NAME=		raphael
COMPONENT_VERSION=	2.2.7
COMPONENT_PROJECT_URL=	http://dmitrybaranovskiy.github.io/raphael/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3ea7f37675e28269a7a401d88c626cf387b2b2295bcce46286b17a4dfefe6bf5
COMPONENT_ARCHIVE_URL=	https://github.com/DmitryBaranovskiy/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB= 	javascript/raphael
COMPONENT_ANITYA_ID=	13485

TPNO=			33645

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

publish: download prep

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)
