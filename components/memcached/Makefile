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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		memcached
COMPONENT_VERSION=	1.4.33
COMPONENT_PROJECT_URL=	http://memcached.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:83726c8d68258c56712373072abb25a449c257398075a39ec0867fd8ba69771d
COMPONENT_ARCHIVE_URL=	http://memcached.org/files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	database/memcached

TPNO=			32788

include $(WS_MAKE_RULES)/common.mk

PATH=$(USRBINDIR):$(GNUBIN):$(USRDIR)/perl5/bin

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

studio_OPT = -xO5

CFLAGS += -D__ATTRIBUTE_DISABLED

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS.64 +=	--with-libevent=$(USRLIBDIR64)
# The below works around a bug in configure/configure.ac that sets
# an incorrect runpath.
# Setting ac_cv_libevent bypasses libevent checks in configure,
# including setting the runpath (-R), which is currently ok
# because libevent is in a default library directory.
CONFIGURE_OPTIONS.64 +=	"ac_cv_libevent_dir=/usr/lib/$(MACH64)"
CONFIGURE_OPTIONS +=	--enable-dtrace --disable-docs --disable-coverage
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)

# lru-maintainer.t is inconsistent and usually fails.

COMPONENT_TEST_TARGETS=	test

# Just retain test result output that's useful.
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^ok/p" ' \
	'-e "/ ok/p" ' \
	'-e "/^not ok/p" ' \
	'-e "/^All tests/p" ' \
	'-e "/^Result/p" '

REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
