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

COMPONENT_NAME=		sudo
SRC_VERSION=	1.8.9
SRC_PATCH_VERSION=	5
COMPONENT_VERSION=	$(SRC_VERSION).$(SRC_PATCH_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(SRC_VERSION)p$(SRC_PATCH_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bc9d5c96de5f8b4d2b014f87a37870aef60d2891c869202454069150a21a5c21
COMPONENT_ARCHIVE_URL=	http://www.sudo.ws/sudo/dist/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.sudo.ws/
COMPONENT_BUGDB=	utility/sudo

TPNO=			16733

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D) ; $(AUTORECONF) -f -I m4 )

CONFIGURE_ENV +=	"CC=$(CC)"
CONFIGURE_ENV +=	"CFLAGS=$(CFLAGS)"
CONFIGURE_ENV +=	"CXX=$(CXX)"
CONFIGURE_ENV +=	"MAKE=$(GMAKE)"
CONFIGURE_ENV +=	"CPPFLAGS=$(CPPFLAGS) -I/usr/include/openldap"
CONFIGURE_ENV +=	"LDFLAGS=$(LDFLAGS) -m64 -lldap_r-2.4"

CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-project
CONFIGURE_OPTIONS +=	--with-timedir=/system/volatile/sudo
CONFIGURE_OPTIONS +=	--with-pam
CONFIGURE_OPTIONS +=	--with-pam-login
CONFIGURE_OPTIONS +=	--disable-pam-session
CONFIGURE_OPTIONS +=	--with-tty-tickets
CONFIGURE_OPTIONS +=	--without-insults
CONFIGURE_OPTIONS +=	--without-lecture
CONFIGURE_OPTIONS +=	--with-ignore-dot
CONFIGURE_OPTIONS +=	--with-solaris-audit
CONFIGURE_OPTIONS +=	--libexecdir=/usr/lib/sudo
CONFIGURE_OPTIONS +=	"sudo_cv_var_nroff_opt_Tascii=no"

COMPONENT_BUILD_ENV +=	CC=$(CC) CXX=$(CXX)
COMPONENT_BUILD_ENV +=	"CFLAGS=$(CFLAGS)"

COMPONENT_INSTALL_TARGETS = install
COMPONENT_INSTALL_ARGS += bindir=$(USRBINDIR)
COMPONENT_INSTALL_ARGS += sbindir=$(USRSBINDIR)

# Make sure that sudo is NOT built with its internal sha2 implementation
# http://www.sudo.ws/bugs/show_bug.cgi?id=641
COMPONENT_TEST_ENV_CMD =
COMPONENT_TEST_CMD = \
	if [[ -n $$( elfdump -s "$(VISUDO)" | grep SHA256Init | grep -v UNDEF ) ]]; then \
		echo "SHA256Init is not an undefined symbol in $(VISUDO)"; \
		exit 1; \
	fi; \
	$(GMAKE)

# Tests may output some compilation lines, so just pull out the relevant test
# output lines for the test results comparison
COMPONENT_TEST_TRANSFORMS += '-e "/^sudo_conf\|^sudo_parseln\|^check_addr\|^check_base64\|^check_fill\|^iolog_path\|^check_symbols\|^sudoers\|^testsudoers\|^visudo\|^check_ttyname/!d"'
COMPONENT_TEST_TRANSFORMS += '-e "s/\(\/dev\/pts\/\)[0-9][0-9]*/\1\#/"'

# Enable aslr for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

VISUDO=$(BUILD_DIR_64)/plugins/sudoers/visudo
test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/crypto
REQUIRED_PACKAGES += text/groff/groff-core
