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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openstack
COMPONENT_VERSION=	2016.1.1
COMPONENT_SRC=
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/nova
IPS_COMPONENT_VERSION=	0.2016.1

include $(WS_MAKE_RULES)/prep.mk
# OpenStack Mitaka requires OVS and RAD changes not present in 11.3
BUILD_BITS=NO_ARCH
include $(WS_MAKE_RULES)/no-evaluation.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Used for placement of openstack_common.py
PYTHON_VERSIONS=	2.7

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)
PKG_MACROS +=		PYV=$(shell echo $(PYTHON_VERSIONS) | tr -d .)

build:		FRC
ifneq ($(BUILD_TYPE), evaluation)
	@/bin/true
endif

install:	FRC
ifneq ($(BUILD_TYPE), evaluation)
	($(MKDIR) $(PROTO_DIR)$(PYTHON_LIB); \
	 $(CP) files/openstack_common.py $(PROTO_DIR)$(PYTHON_LIB); \
	 $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES))
endif

download::
	@echo 'No downloads for this component'

clobber::	clean

clean::
	$(RM) -r $(SOURCE_DIR)/build

test:		$(NO_TESTS)

system-test:	$(NO_TESTS)
