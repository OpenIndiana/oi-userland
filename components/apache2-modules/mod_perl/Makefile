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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_perl
COMPONENT_VERSION=	2.0.4
COMPONENT_PROJECT_URL=	http://perl.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7da2046aa65dbef64ff5b71400bed4b6b82441e6313c8ca4becb85fb4a89a0f0
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)dist/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

TPNO=			8896

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

APACHE_USR_PREFIX=/usr/apache2/2.2
AP_PERL5LIB=$(APACHE_USR_PREFIX)/lib/perl
AP_PERL5BIN=$(APACHE_USR_PREFIX)/bin
PERLMAN=$(APACHE_USR_PREFIX)/man

COMPONENT_PRE_BUILD_ACTION= ( \
	cd $(@D); $(PERL) Makefile.PL \
	INSTALLDIRS=perl \
	INSTALLSITELIB=$(AP_PERL5LIB) \
	INSTALLARCHLIB=$(AP_PERL5LIB) \
	INSTALLSITEARCH=$(AP_PERL5LIB) \
	INSTALLPRIVLIB=$(AP_PERL5LIB) \
	SITEARCHEXP=$(AP_PERL5LIB) \
	SITELIBEXP=$(AP_PERL5LIB) \
	INSTALLMAN1DIR=$(PERLMAN)/man1 \
	INSTALLMAN3DIR=$(PERLMAN)/man3 \
	INSTALLSCRIPT=$(AP_PERL5BIN) \
	MP_APXS=$(APACHE_USR_PREFIX)/bin/apxs)

COMPONENT_TEST_TARGETS=	test

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:/usr/bin
endif

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += library/apr-15
REQUIRED_PACKAGES += library/apr-util-15
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/linker
REQUIRED_PACKAGES += web/server/apache-22
