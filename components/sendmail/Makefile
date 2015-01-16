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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		sendmail
COMPONENT_VERSION=	8.14.9
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	ftp://ftp.sendmail.org/pub/sendmail/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME).$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f5a497151abd8f341cca0736c3f9bd703d574d93146b2989689dff6d7a445d75
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig
COMPONENT_BUGDB=	utility/sendmail

TPNO=			7435

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

PKG_PROTO_DIRS += $(BUILD_DIR_32)
PKG_PROTO_DIRS += $(BUILD_DIR_32)/obj.SunOS.$(OS_VERSION).$(ARCH)
PKG_PROTO_DIRS += $(COMPONENT_DIR)/files
PKG_PROTO_DIRS += $(COMPONENT_DIR)/files/man

# Userland default includes -mt which links with libthread which we don't need.
studio_MT =

# We set ARCH to match sendmail's configure-like script: on x86, it simply
# uses 'uname -m', but on sparc it shortens "sun4*" into "sun4".
ARCH	:=	$(shell uname -m)
ifeq ($(findstring sun4,$(ARCH)),sun4)
ARCH	=	sun4
endif
FILE_DIR=$(COMPONENT_DIR)/files
M4_ARG=-DSUN_HIDE_INTERNAL_DETAILS
SM_BUILD_SUB_DIR=obj.SunOS.$(OS_VERSION).$(ARCH)
SM_BUILD_DIR=$(@D)/$(SM_BUILD_SUB_DIR)

CLEAN_PATHS += $(FILE_DIR)/aux/mailq

# This appends "+Sun" to the version string, which we do for historical
# reasons.  If we did this via patch, then we would have to revise the patch
# with every new release, since the version string changes every time.
COMPONENT_PREP_ACTION =	$(GSED) -i -e 's/\(Version\[\] = "8\.[^"]*\)/\1+Sun/' \
    $(COMPONENT_SRC)/sendmail/version.c

# libmilter and sendmail must come before include, so appending to the default
# value of LINT_FLAGS will not work; we must redefine it here.
SM_DEFS=	-DSOLARIS=21200
SM_INCLUDES=	-I$(SM_BUILD_DIR)/libmilter -I$(SOURCE_DIR)/sendmail \
    -I$(SOURCE_DIR)/include -I$(SOURCE_DIR) -I.
LINT_FLAGS =	-nsvx $(SM_DEFS) $(SM_INCLUDES)
CCOPTS =	-erroff=E_STATEMENT_NOT_REACHED $(CC_BITS)

COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CCOPTS="$(CCOPTS)"
COMPONENT_BUILD_ARGS += CCLINK="$(LD)"
COMPONENT_BUILD_ARGS += LDOPTS="$(CC_BITS)"

COMPONENT_POST_BUILD_ACTION = cd $(FILE_DIR)/aux ; $(GMAKE) build

COMPONENT_POST_INSTALL_ACTION += cd $(FILE_DIR)/aux ; $(GMAKE) install ;
COMPONENT_POST_INSTALL_ACTION += \
    $(CP) $(FILE_DIR)/cf/domain/solaris-generic.m4 $(@D)/cf/domain/ ;
COMPONENT_POST_INSTALL_ACTION += \
    $(CP) $(FILE_DIR)/cf/cf/sendmail.mc $(@D)/cf/cf/ ;
COMPONENT_POST_INSTALL_ACTION += \
    cd $(@D)/cf/cf ; \
    $(RM) submit.cf ; \
    m4 $(M4_ARG) ../m4/cf.m4 submit.mc > submit.cf ; \
    m4 $(M4_ARG) ../m4/cf.m4 sendmail.mc > sendmail.cf

COMPONENT_TEST_ARGS += CC="$(CC)"
COMPONENT_TEST_ARGS += CCOPTS="$(CCOPTS)"
COMPONENT_TEST_ARGS += CCLINK="$(LD)"
COMPONENT_TEST_ARGS += LDOPTS="$(CC_BITS)"

COMPONENT_TEST_ENV +=	PATH=/usr/gnu/bin:/usr/bin

COMPONENT_TEST_TRANSFORMS += \
    '-e "s|$(SM_BUILD_SUB_DIR)|\\$$(SM_BUILD_SUB_DIR)|g" ' \
    '-e "s|$(OS_VERSION)|\\$$(OS_VERSION)|g" ' \
    '-e "s|$(ARCH)|\\$$(ARCH)|g" ' \
    '-e "s|$(CC)|\\$$(CC)|g" '

ASLR_MODE = $(ASLR_ENABLE)

INSTALL_32=

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
