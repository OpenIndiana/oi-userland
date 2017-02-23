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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_perl
COMPONENT_VERSION=	2.0.9
COMPONENT_PROJECT_URL=	http://perl.apache.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:0260f26ab771c1c95fadc67544b3400e420bb30b8a77565d2d02ad05498ef52b
COMPONENT_ARCHIVE_URL=	http://www.apache.org/dist/perl/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache
COMPONENT_ANITYA_ID=	1998

TPNO=			23900

BUILD_STYLE= justmake
CONFIGURE_DEFAULT_DIRS= no
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

APACHE_USR_PREFIX=/usr/apache2/2.4

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
COMPONENT_SYSTEM_TEST_TARGETS=	system_test

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:$(USRBINDIR)
else
PATH=$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
endif

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/\[pid [0-9][0-9]*:tid [0-9][0-9]*\] //" ' \
	'-e "/\[.* 20[0-9][0-9]\] \[/s/\[.* 20[0-9][0-9]\]/[date]/" ' \
	'-e "/^server localhost/s/ (.*)//" ' \
	'-e "/base server + [0-9][0-9] vhosts ready to run tests/d" ' \
	'-e "/^Files=/s/, Tests=[0-9][0-9]*,  *[0-9][0-9]* wallclock secs (.*)//" ' \
	'-e "/^waiting .* to start: ok/s/ (waited [0-9][0-9]* secs)//" ' \
	'-e "/^waiting .* to start: \./s/\.\.*//" ' \
	'-e "/^\.\.*$$/d" ' \
	'-e "/^\[warning\] port 8529 still in use\.\.\.$$/d" ' \
	'-e "/^\.*done$$/d" ' \
	'-e "s/ -I.*blib\/arch -I.*blib\/lib//" ' \
	'-e "s/ -I\/usr\/apache2\/2\.[0-9]\/lib\/perl//" ' \
	'-e "s/ -libmodperl .*mod_perl\.so//" ' \
	'-e "s/ make system_test APACHEINSTALLSITELIB=.*/ make test/" ' \
	'-e "s/using Apache\/2.[0-9].[0-9][0-9]* (/using Apache\/2.x.x (/" '

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += library/apr-15
REQUIRED_PACKAGES += library/apr-util-15
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/server/apache-24
