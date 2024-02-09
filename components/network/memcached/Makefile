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
# Copyright (c) 2023, Friedrich Kink. All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		memcached
COMPONENT_VERSION=	1.6.23
COMPONENT_SUMMARY=	The memcached memory object cache
COMPONENT_DESCRIPTION=	Memcached is a high performance multithreaded event-based \
			key/value cache store intended to be used in a distributed system.
COMPONENT_FMRI=		service/memcached
COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://memcached.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:85b0334904f440296a685ccfda75f0f4517bf8922ab8efa6d0c4b3c92c354d4c
COMPONENT_ARCHIVE_URL=	https://www.memcached.org/files/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	(cd $(SOURCE_DIR); aclocal; autoconf; $(CLONEY) $(SOURCE_DIR) $(@D))

# otherwise the link with ssl library does not work
# standard linker path does not make sense anyway
COMPONENT_POST_CONFIGURE_ACTION = \
	($(GSED) -i -e 's:-L/usr/lib/amd64::' $(@D)/config.status)

COMPONENT_TEST_TARGETS=	test

CFLAGS += -I/usr/include/libevent2

CONFIGURE_OPTIONS +=	--with-libevent=$(USRLIBDIR64)
CONFIGURE_OPTIONS +=	--enable-dtrace
CONFIGURE_OPTIONS +=	--disable-sasl
CONFIGURE_OPTIONS +=	--enable-werror
CONFIGURE_OPTIONS +=	--enable-64bit
CONFIGURE_OPTIONS +=	--enable-large-client-flags
CONFIGURE_OPTIONS +=	--enable-tls
CONFIGURE_OPTIONS +=	--disable-docs
CONFIGURE_OPTIONS +=	--disable-coverage
CONFIGURE_OPTIONS +=	--localstatedir=/var

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_TEST_ARGS +=  -k -i
# Just retain test result output that's useful.
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^ok/p" ' \
	'-e "/^All tests/p" ' \
	'-e "/^Result/p" '

# Manually added test dependency
TEST_REQUIRED_PACKAGES += library/perl-5/io-socket-ssl-538

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
