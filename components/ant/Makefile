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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		apache-ant
COMPONENT_VERSION=	1.7.1
COMPONENT_PROJECT_URL=	http://ant.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:4dc49a7260ef90a6dc6611b7e96b9f047d507589736d4a2ad6efbe3edfc6fba6
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/ant/source/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

GMAKE=./build.sh

ANT_ENV+=JAVA_HOME=$(JAVA_HOME)
ANT_ENV+=CLASSPATH=/usr/share/lib/java/junit.jar:/usr/share/antlr-2.7.7/antlr.jar

ANT_DIST_DIRS+=-Ddist.dir=$(PROTO_DIR)
ANT_DIST_DIRS+=-Ddist.bin=$(PROTO_DIR)/usr/bin
ANT_DIST_DIRS+=-Ddist.etc=$(PROTO_DIR)/usr/share/lib/ant
ANT_DIST_DIRS+=-Ddist.docs=$(PROTO_DIR)/usr/share/doc/ant
ANT_DIST_DIRS+=-Ddist.javadocs=$(PROTO_DIR)/usr/share/doc/ant/manual/api
ANT_DIST_DIRS+=-Ddist.lib=$(PROTO_DIR)/usr/share/lib/ant

COMPONENT_BUILD_TARGETS =	build
COMPONENT_BUILD_ENV +=		$(ANT_ENV)

COMPONENT_INSTALL_ARGS =	$(ANT_DIST_DIRS)
COMPONENT_INSTALL_TARGETS =	dist
COMPONENT_INSTALL_ENV +=	$(ANT_ENV)

COMPONENT_TEST_TARGETS =	test
COMPONENT_TEST_ENV +=		$(ANT_ENV)

build:	$(BUILD_32)

install: $(INSTALL_32)

test:  $(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
