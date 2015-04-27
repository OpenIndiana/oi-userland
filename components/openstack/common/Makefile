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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openstack
COMPONENT_VERSION=	2014.2.2
COMPONENT_PROJECT_URL=	http://www.openstack.org/
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Do not apply the standard license transforms for this component.
LICENSE_TRANSFORMS =

build:		FRC
	@/bin/true

install:	FRC
	@/bin/true

download::
	@echo 'No downloads for this component'

clobber::	clean

clean::
	$(RM) -r $(SOURCE_DIR)/build

test:		$(NO_TESTS)
