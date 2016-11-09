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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
COMPILER=gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmemcached
COMPONENT_VERSION=	1.0.18
COMPONENT_ARCHIVE_HASH=	\
    sha256:e22c0bb032fde08f53de9ffbc5a128233041d9f33b5de022c0978a2149885f82 
COMPONENT_ARCHIVE_URL= https://launchpad.net/libmemcached/1.0/${COMPONENT_VERSION}/+download/libmemcached-${COMPONENT_VERSION}.tar.gz 
COMPONENT_PROJECT_URL=  http://libmemcached.org/libMemcached.html
COMPONENT_BUGDB=	database/memcached

TPNO=			31699

include $(WS_MAKE_RULES)/common.mk

ifeq ($(OS_VERSION),5.11)
LDFLAGS += -lsocket -lnsl
CONFIGURE_OPTIONS += ax_cv_check_cflags__Werror__fPIE=no
CONFIGURE_OPTIONS += ax_cv_check_cflags__Werror__pie=no
CONFIGURE_OPTIONS += ax_cv_check_cxxflags__Werror__fPIE=no
CONFIGURE_OPTIONS += ax_cv_check_cxxflags__Werror__pie=no
endif

# Include _SOLARIS_ flag for byteorder.h.patch's ifdef to work
CFLAGS+= -D_SOLARIS_
CXXFLAGS+= -D_SOLARIS_

CONFIGURE_ENV +=	MAKE=$(GMAKE)

CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEDIR)

# need some files in $(SOURCE_DIR)/docs during build
COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

# need /usr/perl5/bin on path to access pod2man perl script, used by 
# the build to create docs
COMPONENT_BUILD_ENV +=	PATH=/usr/perl5/bin:$(PATH)

COMPONENT_BUILD_ENV +=	MAKE="$(GMAKE)"	

# Libmemcached's configure script sets an incorrect CFLAGS in the Makefiles
# it generates.  Make sure we use the correct one by passing CFLAGS in 
# as a build argument (CFLAGS in the environment won't take precedence
# over the Makefile one).
COMPONENT_BUILD_ARGS +=	CFLAGS="$(CFLAGS)"

# Similarly, set pkglibdir in the arguments to gmake; otherwise
# the Makefile sets runpath to a non-existent /usr/lib/libmemcached directory.
COMPONENT_BUILD_ARGS +=	pkglibdir=$(USRLIBDIR)

COMPONENT_INSTALL_ENV +=	DESTDIR=$(PROTO_DIR)

COMPONENT_TEST_ARGS +=		-k -i
COMPONENT_TEST_TARGETS =	test
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/SKIP/p" ' \
        '-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" ' \
	'-e "/TOTAL/p" '

# Master test results are the same for both 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# To prevent "libtool_install_magic: unbound variable"
unexport SHELLOPTS

# Tests fail, probably because memcached is not running.
# XFAILS are due to servers or arguments not being provided. 

REQUIRED_PACKAGES += developer/gcc
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libsasl2
