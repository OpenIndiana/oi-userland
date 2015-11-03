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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmemcached
COMPONENT_VERSION=	0.16
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d4fb3a64dc592c104caa4e98bc11f209fcb97eecdeb7f506797320dea75b9459
COMPONENT_ARCHIVE_URL= http://launchpadlibrarian.net/33299595/${COMPONENT_ARCHIVE}
COMPONENT_PROJECT_URL=  http://libmemcached.org/libMemcached.html
COMPONENT_BUGDB=	database/memcached

TPNO=			5582

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += -xstrconst
LDFLAGS += -lsocket -lnsl

CONFIGURE_ENV +=	MAKE=$(GMAKE)

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS +=    --bindir=$(USRBINDIR) 
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
COMPONENT_BUILD_ARGS +=	pkglibdir=/usr/lib

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_INSTALL_ENV +=	DESTDIR=$(PROTO_DIR)

COMPONENT_TEST_ARGS +=		-k -i
COMPONENT_TEST_DIR =		$(@D)/tests
COMPONENT_TEST_TARGETS =	test
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(bash: line 1:\).*|\1|" ' \
	'-e "s|\(Testing \)\(.*\)\([0-9].[0-9][0-9][0-9]\)\(.*$$\)|\1\2\4|" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Tests fail, probably because memcached is not running.
test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += system/library
