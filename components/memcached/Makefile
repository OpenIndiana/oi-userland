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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		memcached
COMPONENT_VERSION=	1.4.17
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://memcached.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d9173ef6d99ba798c982ea4566cb4f0e64eb23859fdbf9926a89999d8cdc0458
COMPONENT_ARCHIVE_URL=	http://memcached.org/files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	database/memcached

TPNO=			16265

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/perl5/bin

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_TEST_TARGETS=	test

studio_OPT = -xO5

CFLAGS += -D__ATTRIBUTE_DISABLED

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS.64 +=	--with-libevent=/usr/lib/$(MACH64)
# The below works around a bug in configure/configure.ac that sets
# an incorrect runpath.
# Setting ac_cv_libevent bypasses libevent checks in configure,
# including setting the runpath (-R), which is currently ok
# because libevent is in a default library directory.
CONFIGURE_OPTIONS.64 +=	"ac_cv_libevent_dir=/usr/lib/$(MACH64)"
CONFIGURE_OPTIONS +=	--enable-dtrace --disable-docs --disable-coverage
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

# Transforms remove unnecessary text from results
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(failed to listen on TCP port \).*|\1|" ' \
	'-e "s|\(Tests=6851\).*|\1|" '\
	'-e "/\(slab class\).*/d" ' \
	'-e "/\(<\).*/d" ' 

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/network
