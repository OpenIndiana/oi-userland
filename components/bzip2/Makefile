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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		bzip2
COMPONENT_VERSION=	1.0.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:3f89f861209ce81a6bab1fd1998c0ef311712002
COMPONENT_ARCHIVE_URL=	http://www.bzip.org/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

LIBNAME=	bz2
LINTOUT=	lint.out
LINTFLAGS=	-nsvx -I. $(BITS32)
LINTFLAGS64=	-nsvx -I. $(BITS64)


CFLAGS += -KPIC -D_FILE_OFFSET_BITS=64
CFLAGS += $(XREGSFLAG)

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_TARGETS += CC="$(CC)"
COMPONENT_BUILD_TARGETS += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_TARGETS += PREFIX=$(PROTOUSRDIR)

COMPONENT_PRE_BUILD_ACTION= \
	(cd $(@D) ; \
	    cp ../../oldapi.c . )

COMPONENT_POST_BUILD_ACTION= \
	(cd $(@D) ; \
	    $(LINT) -o $(LIBNAME) ../../llib-lbz2 > $(LINTOUT) 2>&1)


# common targets
build:		$(BUILD_32) $(BUILD_64)

MAN1FILES= bunzip2.1 bzcat.1 bzdiff.1 bzgrep.1 \
    bzip2.1 bzip2recover.1 bzmore.1
MAN3FILES=libbz2.3

include ../../make-rules/shared-targets.mk

install:	build $(INSTALL_32) $(PROTOMAN3FILES) $(PROTOMAN1FILES)
	$(INSTALL) $(BUILD_DIR_32)/libbz2.so.1 $(PROTOUSRLIBDIR)
	cd $(PROTOUSRLIBDIR); rm -f libbz2.so; ln -s libbz2.so.1 libbz2.so
	$(INSTALL) llib-lbz2 $(PROTOUSRLIBDIR)
	$(INSTALL) $(BUILD_DIR_32)/llib-lbz2.ln $(PROTOUSRLIBDIR)
	$(MKDIR) $(PROTOUSRLIBDIR64)
	$(INSTALL) $(BUILD_DIR_64)/libbz2.so.1 $(PROTOUSRLIBDIR64)
	cd $(PROTOUSRLIBDIR64); rm -f libbz2.so; ln -s libbz2.so.1 libbz2.so
	$(INSTALL) $(BUILD_DIR_64)/llib-lbz2.ln $(PROTOUSRLIBDIR64)

# build does this always
test:  build
	@cd $(BUILD_DIR_32); $(MAKE) check
	@cd $(BUILD_DIR_64); $(MAKE) check


BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
