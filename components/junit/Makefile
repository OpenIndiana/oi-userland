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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		junit
COMPONENT_VERSION=	4.11
COMPONENT_PROJECT_URL=	https://github.com/junit-team/junit/archive
COMPONENT_SRC=		$(COMPONENT_NAME)-r$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	r$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:3048cb3f2b07fada9d85b2c042bbedb93892ef70c1dcfe0594124850418f9ffb
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1480

TPNO=                   9070

BUILD_STYLE= ant

# Another test is:
# To test after you have installed the resulting package do:
# $ java -cp /usr/share/lib/java/junit.jar:/usr/share/doc/junit/samples/org \
#       junit/samples/money/MoneyTest
# ......................
# Time: 0.003
#
# OK (22 tests)
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_32)
include $(WS_MAKE_RULES)/common.mk

# These ARGS override what is set in build.xml
COMPONENT_BUILD_ARGS 	+= -Ddist=${PROTO_DIR}
COMPONENT_BUILD_ARGS    += -Djavadocdir=${PROTO_DIR}
COMPONENT_BUILD_ARGS    += -Dversion-status=""
COMPONENT_BUILD_ARGS    += -Dadditionalparam="-Xdoclint:none"
COMPONENT_BUILD_TARGETS  = populate-dist

COMPONENT_PRE_BUILD_ACTION =	$(MKDIR) $(@D)/tmp
COMPONENT_BUILD_ENV +=	"_JAVA_OPTIONS=-Djava.io.tmpdir=$(BUILD_DIR_32)/tmp"

# We patched in test-build into build.xml which is a copy of
# dist but without the depends=populate-dist
# because userland infrasture will handle the build and we
# need to build tests which are also part of the overall softare build.
COMPONENT_TEST_ARGS	+= $(COMPONENT_BUILD_ARGS)
COMPONENT_TEST_ENV	+= "_JAVA_OPTIONS=-Djava.io.tmpdir=$(BUILD_DIR_32)/tmp"
COMPONENT_TEST_TARGETS	 = test-build

COMPONENT_SYSTEM_TEST_ARGS	+= -Dsystem-binjar=$(USRSHARELIBDIR)/java/$(COMPONENT_NAME).jar
COMPONENT_SYSTEM_TEST_ENV	+= "_JAVA_OPTIONS=-Djava.io.tmpdir=$(BUILD_DIR_32)/tmp"
COMPONENT_SYSTEM_TEST_TARGETS	 = test

# Test transforms
# 	remove everything upto "test" which is build noise
#	remove time
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/^test/d"' \
	'-e "s/.*[Tt]ime.*$$//"'

REQUIRED_PACKAGES += runtime/java/jre-8
