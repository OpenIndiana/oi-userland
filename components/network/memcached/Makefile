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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		memcached
COMPONENT_VERSION=	1.4.37
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://memcached.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2f335ab9110ce39036c5271ef39a582a852e424bc9659e421844073cfdf8606b
COMPONENT_ARCHIVE_URL=	http://www.memcached.org/files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	database/memcached

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

gcc_OPT=-O0

COMPONENT_PREP_ACTION = \
    (cd $(@D) && \
	$(TOUCH) README &&\
	libtoolize --copy --force &&\
	aclocal -I m4 &&\
	automake -c -f -a &&\
	autoconf )

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_TEST_TARGETS=	test

CFLAGS += -D__ATTRIBUTE_DISABLED

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS.64 +=	--with-libevent=/usr/lib/${MACH64}
CONFIGURE_OPTIONS +=	--enable-dtrace
CONFIGURE_OPTIONS +=	--disable-docs
CONFIGURE_OPTIONS +=	--disable-coverage
CONFIGURE_OPTIONS +=	--localstatedir=/var

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
