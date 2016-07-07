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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		Python
COMPONENT_VERSION=	2.6.9
COMPONENT_REVISION=	6
COMPONENT_PROJECT_URL=	http://python.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7277b1285d8a82f374ef6ebaac85b003266f7939b3f2a24a3af52f9523ac94db
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)ftp/python/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/python

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# Need to preserve timestamp for Grammar files.  If the pickle files are older, 
# Python will try to rebuild them.  
PKGSEND_PUBLISH_OPTIONS += -T \*Grammar\*.txt
PKGSEND_PUBLISH_OPTIONS += -T \*Grammar\*.pickle

# We patch auto* files, so regenerate headers and configure
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; autoheader ; autoconf)

# This seems horribly wrong, but these defines break the ability to build c99
# compliant modules or with gcc.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D) ; \
	 perl -pi -e 's/(^\#define _POSIX_C_SOURCE.*)/\/* $$1 *\//' pyconfig.h ; \
	 perl -pi -e 's/^(\#define _XOPEN_SOURCE.*)/\/* $$1 *\//' pyconfig.h ; \
	 perl -pi -e 's/^(\#define _XOPEN_SOURCE_EXTENDED.*)/\/* $$1 *\//' \
			pyconfig.h)

CFLAGS += $(XPG6MODE)
CFLAGS += $(gcc_C99_ENABLE)

# we don't want to leak $(CC_BITS) into BASECFLAGS as it causes problems with
# python-config
CC +=	$(CFLAGS)

CPPFLAGS +=	-IPython

# so we find the ncurses headers
CPPFLAGS +=	-I/usr/include/ncurses
# enable large files how they did in JDS
CPPFLAGS +=	-D_LARGEFILE64_SOURCE
# libffi for _ctypes
CPPFLAGS +=	$(shell pkg-config --cflags-only-I libffi)

# Python puts its header files in a special place.
LINT_FLAGS +=	-I$(SOURCE_DIR)/Include

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--with-system-ffi
CONFIGURE_OPTIONS  +=		CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=		CCSHARED="$(CC_PIC)"
CONFIGURE_OPTIONS  +=		DFLAGS="-$(BITS)"
COMPONENT_BUILD_ENV  +=		DFLAGS="-$(BITS)"

# 64 bit shared objects need to go in a 64-bit directory
COMPONENT_INSTALL_ARGS.64 += DESTSHARED=$(CONFIGURE_PREFIX)/lib/python2.6/lib-dynload

# Setup pyconfig.h file to support 32 & 64 bit.
# If the /usr/lib/python2.6/lib2to3/*.pickle files are older than the related
# *.txt files in the same directory, it will rebuild them anytime you try to
# build a Python module.  So here we also touch the pickle files to avoid this.
#
COMPONENT_POST_INSTALL_ACTION= \
            (cd $(PROTOUSRDIR) ;  \
             $(MV) include/python2.6/pyconfig.h include/python2.6/pyconfig-$(BITS).h ; \
             $(TOUCH) lib/python2.6/lib2to3/*.pickle)
                
ASLR_MODE = $(ASLR_ENABLE)

# common targets
$(INSTALL_32):  $(INSTALL_64)
build:		$(BUILD_32_and_64)
install:	$(INSTALL_32_and_64)

# Using "-uall,-network" ensures all tests are run except the network tests.
# The network tests contain many expected failures when run behind a firewall.
# The "-v" ensures verbose mode.  You can set TESTOPTS_PYTHON_TEST to a
# particular test if you want to run just one test.  For example, run gmake with
# "-k" so it continues and does both 32-bit and 64-bit tests, even if there is a
# failure, like this:
# $ TESTOPTS_PYTHON_TEST=test_sys gmake -k test
# Note that when a test succeeds, the builds/*/.tested file gets created.  You
# may need to remove these files, or run "gmake clobber" or "gmake clean"
# between tests.
#
COMPONENT_TEST_ENV = EXTRATESTOPTS="-v -uall,-network $(TESTOPTS_PYTHON_TEST)"
COMPONENT_TEST_TARGETS = test

test:				$(TEST_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
