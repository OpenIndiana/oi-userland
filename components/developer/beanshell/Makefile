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
# Copyright 2017 Gary Mills
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		beanshell
COMPONENT_VERSION=	2.0b6
COMPONENT_REVISION=	2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.beanshell.org/
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:dbcd8296a0aa81b5edc80a5421841b968d031332ffcebf3b2c877969669f5cad
COMPONENT_ARCHIVE_URL=	https://github.com/beanshell/beanshell/archive/$(COMPONENT_ARCHIVE)

COMPONENT_BUGDB=	utility/beanshell

IPS_COMPONENT_VERSION=	2.0

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ant.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ARGS =		-Ddist-dir=${PROTO_DIR}
COMPONENT_BUILD_ARGS +=	-Djavadoc-dir=${PROTO_DIR}
COMPONENT_BUILD_TARGETS +=	dist 

# We use the solaris-transform file to pick up files in the prototype area
# that are not found in the directories we install them to on Solaris.
# Doing this obviates the need to add it's location to each line in the
# associated beanshell.p5m file.
PUBLISH_TRANSFORMS += solaris-transform
# Needed to pick up scripts/bsh and bshcommands-bshdoc.xml
PKG_PROTO_DIRS += $(COMPONENT_DIR) 
PKG_PROTO_DIRS += $(BUILD_DIR_32)

# common targets
build:		$(BUILD_32)

install:	build

test:	$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/java/openjdk8
