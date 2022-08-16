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
# Copyright (c), 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2017, Wiselabs Software Ltda - http://www.wiselabs.com.br. All rights reserved.
#

BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ant
COMPONENT_VERSION=	1.10.12
COMPONENT_SUMMARY=	Apache Ant is a Java-based build tool
COMPONENT_PROJECT_URL=	https://ant.apache.org/
COMPONENT_SRC_NAME=	apache-ant
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:044e2c0a66c90112d67789d267f049ae947fde384e29b1f8c14ada9bead0fe44
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/ant/source/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/ant
COMPONENT_FMRI=		developer/build/ant
COMPONENT_CLASSIFICATION=	Development/Distribution Tools
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_TOP)/make-rules/common.mk

PYTHON_VERSION= 3.9

$(BUILD_$(MK_BITS)):	GMAKE=./build.sh
$(INSTALL_$(MK_BITS)):	GMAKE=./build.sh
$(TEST_$(MK_BITS)):	GMAKE=./build.sh

ANT_ENV+=JAVA_HOME=$(JAVA_HOME)

ANT_DIST_DIRS+=-Ddist.dir=$(PROTO_DIR)
ANT_DIST_DIRS+=-Ddist.bin=$(PROTO_DIR)/usr/bin
ANT_DIST_DIRS+=-Ddist.etc=$(PROTO_DIR)/usr/share/lib/ant
ANT_DIST_DIRS+=-Ddist.docs=$(PROTO_DIR)/usr/share/doc/ant
ANT_DIST_DIRS+=-Ddist.manual=$(PROTO_DIR)/usr/share/doc/ant/manual
ANT_DIST_DIRS+=-Ddist.javadocs=$(PROTO_DIR)/usr/share/doc/ant/manual/api
ANT_DIST_DIRS+=-Ddist.lib=$(PROTO_DIR)/usr/share/lib/ant

OPTIONAL_LIBS+=/usr/share/lib/java/junit.jar
OPTIONAL_LIBS+=/usr/share/lib/java/bsf.jar
OPTIONAL_LIBS+=/usr/share/antlr-2.7.7/antlr.jar

COMPONENT_PRE_BUILD_ACTION = $(CP) $(OPTIONAL_LIBS) $(@D)/lib/optional

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/python' so turn it into '#!/usr/bin/python$(PYTHON_VERSION)'
#
COMPONENT_POST_INSTALL_ACTION += \
    $(GSED) -i -e 's?\/usr\/bin\/python?\/usr\/bin\/python$(PYTHON_VERSION)?' \
    $(PROTOUSRBINDIR)/runant.py;

COMPONENT_BUILD_ARGS =
COMPONENT_BUILD_TARGETS =	build
COMPONENT_BUILD_ENV +=		$(ANT_ENV)

COMPONENT_INSTALL_ARGS =	$(ANT_DIST_DIRS)
COMPONENT_INSTALL_TARGETS =	dist
COMPONENT_INSTALL_ENV +=	$(ANT_ENV)

COMPONENT_TEST_TARGETS =	test
COMPONENT_TEST_ENV +=		$(ANT_ENV)
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
    '-e "s/[0-9]*\.*[0-9]* sec//" ' \
    '-e "s/[0-9]*ms//" ' \
    '-e "s/[0-9]* minutes//" ' \
    '-e "s/[0-9]* seconds//" ' \
	'-e "/BUILD/p" ' \
	'-e "/Testsuite/p" ' \
	'-e "/Testcase/p" ' \
	'-e "/Tests run/p" '

# Build dependencies
REQUIRED_PACKAGES += developer/java/openjdk8
REQUIRED_PACKAGES += developer/parser/antlr-2
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += library/java/commons-bsf

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += shell/ksh93
