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
# Copyright (c) 2013  Erol Zavidic. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmemcached
COMPONENT_VERSION=	1.0.17
COMPONENT_REVISION=     1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7bb27b2589400f918df1cf5002cb01ef7ccac6e23f818604e2386de62c80bba5
COMPONENT_ARCHIVE_URL=  https://launchpad.net/libmemcached/1.0/1.0.17/+download/${COMPONENT_ARCHIVE}
COMPONENT_PROJECT_URL=  http://libmemcached.org/libMemcached.html
COMPONENT_BUGDB=	database/memcached

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS  += -std=c99 $(CPP_XPG6MODE)
CXXFLAGS+= -std=c++98 $(CPP_XPG6MODE)
LDFLAGS += $(CPP_XPG6MODE) -lsocket -lnsl

CONFIGURE_ENV +=	MAKE=$(GMAKE)

CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEDIR)

CONFIGURE_OPTIONS +=    --disable-static
CONFIGURE_OPTIONS +=    --without-mysql
CONFIGURE_OPTIONS +=    --without-gearmand
CONFIGURE_OPTIONS +=    --without-memcached

COMPONENT_PREP_ACTION =  ( cd $(@D) && autoreconf -vif )

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
COMPONENT_BUILD_ARGS +=	CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ARGS +=	LDFLAGS="$(LDFLAGS)"

# Similarly, set pkglibdir in the arguments to gmake; otherwise
# the Makefile sets runpath to a non-existent /usr/lib/libmemcached directory.
COMPONENT_BUILD_ARGS +=	pkglibdir=/usr/lib

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_INSTALL_ENV +=	DESTDIR=$(PROTO_DIR)

COMPONENT_TEST_TARGETS =	test

# common targets

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Some tests fail because memcached is not running.
test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
