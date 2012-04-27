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

COMPONENT_NAME=		bzip2
COMPONENT_VERSION=	1.0.6
COMPONENT_PROJECT_URL=	http://www.bzip.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a2848f34fcd5d6cf47def00461fcb528a0484d8edef8208d6d2e2909dc61d9cd
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

LINT_FLAGS +=	-I.

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ARGS += PREFIX=$(PROTOUSRDIR)

COMPONENT_PRE_BUILD_ACTION= \
	(cd $(@D) ; \
	    cp ../../oldapi.c . )

# common targets
build:		$(BUILD_32_and_64)

# override the 64 bit install and have it make a directory for the lint lib
$(INSTALL_64):
	$(MKDIR) $(PROTOUSRLIBDIR64)
	touch $@

install:	build $(INSTALL_32_and_64)
	$(INSTALL) $(BUILD_DIR_32)/libbz2.so.1 $(PROTOUSRLIBDIR)
	cd $(PROTOUSRLIBDIR); rm -f libbz2.so; ln -s libbz2.so.1 libbz2.so
	$(INSTALL) $(BUILD_DIR_64)/libbz2.so.1 $(PROTOUSRLIBDIR64)
	cd $(PROTOUSRLIBDIR64); rm -f libbz2.so; ln -s libbz2.so.1 libbz2.so
	$(INSTALL) $(BUILD_DIR_64)/llib-lbz2.ln $(PROTOUSRLIBDIR64)

# build does this always
test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
