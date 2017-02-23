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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Authen-PAM
COMPONENT_VERSION=	0.16
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0e949bd9a2a9df0f829971030fe9169cbaf6cec78b92faf22f547ff6c6155c9b
COMPONENT_ARCHIVE_URL=	\
    http://www.cpan.org/modules/by-module/Authen/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://search.cpan.org/~nikip/
COMPONENT_BUGDB=	perl-mod/authen-pam
COMPONENT_ANITYA_ID=	6628

TPNO=			9303

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/makemaker.mk

# Pick up the patch to configure.ac in the 01-solaris.patch file
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# man pages go in the common area
COMPONENT_INSTALL_ENV += INSTALLVENDORMAN3DIR=$(USRSHAREMAN3DIR)

# This does not have a master test file because the test must be run manually.
COMPONENT_TEST_TARGETS = test

build:		$(BUILD_64)

install:	$(INSTALL_64)

COMPONENT_POST_TEST_ACTION= \
    PERL5LIB=$(@D)/blib/lib:$(@D)/blib/arch $(PERL) test/PAM_NO_AUTHTOK_CHECK.pl

# Must have xml-parser installed for these tests to pass.
test:		
		if tty -s; then  $(MAKE) realtest; else echo 'Skipping tests'; fi

realtest:	$(TEST_64)

system-test:	$(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += system/library
