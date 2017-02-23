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
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		lua
COMPONENT_VERSION=	5.2.1
COMPONENT_PROJECT_URL=	http://www.lua.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:64304da87976133196f9e4c15250b70f444467b6ed80d7cfd7b3b982b5177be5
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)ftp/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1847

LUA_TESTS=		lua-5.2.1-tests
COMPONENT_ARCHIVE_1=	$(LUA_TESTS).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:2346d635ee392c8d8024b07beaa10b7b66a3f861c41d575753d03155751cf114
COMPONENT_ARCHIVE_URL_1= $(COMPONENT_PROJECT_URL)/tests/5.2/$(COMPONENT_ARCHIVE_1)

TPNO=			5814

BUILD_STYLE= justmake
INSTALL_32_and_64 += $(BUILD_DIR)/lua-64.pc
SYSTEM_TEST_TARGET= $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL= 0

# This is because lua uses $(CC) to build its shared libraries.
CC +=		$(CC_BITS)

CFLAGS +=	$(CC_PIC) $(CPP_LARGEFILES)

COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += USRCFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ARGS += INSTALL=$(INSTALL)
COMPONENT_INSTALL_ARGS += INSTALL_TOP=$(PROTOUSRDIR)
$(INSTALL_32):	COMPONENT_INSTALL_ARGS += INSTALL_BIN=$(PROTOUSRBINDIR)/$(MACH32)
$(INSTALL_64):	COMPONENT_INSTALL_ARGS += INSTALL_LIB=$(PROTOUSRLIBDIR64)

$(BUILD_DIR)/lua-64.pc:		files/lua-64.pc
	$(GSED) -e "s#MACH64#$(MACH64)#g" < $< > $@

CLEAN_PATHS +=	$(LUA_TESTS)

LUA_EXE_32 =	$(BUILD_DIR)/$(MACH32)/src/$(COMPONENT_NAME)
LUA_EXE_64 =	$(BUILD_DIR)/$(MACH64)/src/$(COMPONENT_NAME)
LUA_EXE =	$(LUA_EXE_$(BITS))

# Unpack and patch the tests once, and work around CR #19661394, which is
# causing the lua self-tests to fail.
COMPONENT_PRE_TEST_ACTION = \
	(if ! test -d $(LUA_TESTS) ; then \
		$(UNPACK) $(UNPACK_ARGS) $(LUA_TESTS).tar.gz ; \
		(cd $(LUA_TESTS); $(GPATCH) $(GPATCH_FLAGS) \
			<$(COMPONENT_DIR)/files/fix-tests.patch) ; \
	fi)

COMPONENT_TEST_DIR =		$(LUA_TESTS)
COMPONENT_TEST_CMD =		$(LUA_EXE)
COMPONENT_TEST_ARGS =		-e"_U=true"
COMPONENT_TEST_TARGETS =	all.lua

# Master test results are the same for both 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The additional lua specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "/---- total memory:/d" ' \
	'-e "s|elements in .\... sec|elements in x.xx sec|g" ' \
	'-e "s|\(total time:\).*|\1|" ' \
	'-e "s|\(test done on\).*|\1|" '

# Unpack and patch the tests once, and work around CR #19661394, which is
# causing the lua self-tests to fail.
COMPONENT_PRE_SYSTEM_TEST_ACTION = \
	(if ! test -d $(LUA_TESTS) ; then \
		$(UNPACK) $(UNPACK_ARGS) $(LUA_TESTS).tar.gz ; \
		(cd $(LUA_TESTS); $(GPATCH) $(GPATCH_FLAGS) \
			<$(COMPONENT_DIR)/files/fix-tests.patch) ; \
	fi)

COMPONENT_SYSTEM_TEST_DIR =	$(LUA_TESTS)
COMPONENT_SYSTEM_TEST_CMD =	$(USRBINDIR)/lua
COMPONENT_SYSTEM_TEST_ARGS =	-e"_U=true"
COMPONENT_SYSTEM_TEST_TARGETS =	all.lua

REQUIRED_PACKAGES += system/library/math
