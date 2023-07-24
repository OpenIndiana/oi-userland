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
# Copyright 2023 Niklas Poslovski
#
BUILD_STYLE = ant
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		beanshell
COMPONENT_VERSION=	2.1.1
COMPONENT_FMRI=		runtime/java/beanshell
COMPONENT_SUMMARY=	beanshell - a small and embeddable Java source interpreter
COMPONENT_DESCRIPTION=	BeanShell is a small, free, embeddable Java source interpreter with object scripting language features, written in Java. BeanShell dynamically executes standard Java syntax and extends it with common scripting conveniences such as loose types, commands, and method closures like those in Perl and JavaScript.
COMPONENT_CLASSIFICATION=Development/Java
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://beanshell.github.io
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7e50fe51c7a36f595ee5c792a75f37a252f6b4b24cd21b97c5bc2634c2c33a77
COMPONENT_ARCHIVE_URL=	https://github.com/beanshell/beanshell/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	LGPLv2.1, SPL

include $(WS_MAKE_RULES)/common.mk

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
PKG_PROTO_DIRS += $(BUILD_DIR_64)

# Manually added dependencies
REQUIRED_PACKAGES += runtime/java/openjdk8

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
