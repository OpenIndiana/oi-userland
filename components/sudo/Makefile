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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		sudo
SRC_VERSION=	1.8.18
SRC_PATCH_VERSION=1
ifdef SRC_PATCH_VERSION
COMPONENT_VERSION=	$(SRC_VERSION).$(SRC_PATCH_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(SRC_VERSION)p$(SRC_PATCH_VERSION)
else
COMPONENT_VERSION=	$(SRC_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(SRC_VERSION)
endif
COMPONENT_ARCHIVE_HASH=	\
    sha256:e5a0471c721281a693025bbde33ebd9d3db43245d83ab8516bbfc23980379434
COMPONENT_ARCHIVE_URL=	http://www.sudo.ws/sudo/dist/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.sudo.ws/

TPNO=			32515

include $(WS_MAKE_RULES)/common.mk

# Fix 64-bit linking via compiler.
LDFLAGS += $(CC_BITS)
LDFLAGS += -lldap_r-2.4

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

# Allows zero-sized struct/union declarations and void functions with return
# statements returning a value to work.
CFLAGS += -features=extensions

COMPONENT_PREP_ACTION = ( cd $(@D) ; $(AUTORECONF) -f -I m4 )

CPPFLAGS += -I$(USRINCDIR)/openldap
CONFIGURE_ENV +=	"MAKE=$(GMAKE)"

CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-project
CONFIGURE_OPTIONS +=	--with-rundir=/system/volatile/sudo
CONFIGURE_OPTIONS +=	--with-pam
CONFIGURE_OPTIONS +=	--with-pam-login
CONFIGURE_OPTIONS +=	--with-tty-tickets
CONFIGURE_OPTIONS +=	--without-insults
CONFIGURE_OPTIONS +=	--without-lecture
CONFIGURE_OPTIONS +=	--with-ignore-dot
CONFIGURE_OPTIONS +=	--with-solaris-audit
CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBDIR64)/sudo
CONFIGURE_OPTIONS +=	"sudo_cv_var_nroff_opt_Tascii=no"

COMPONENT_INSTALL_TARGETS = install

# Avoid calling "chown 0" on installed files
COMPONENT_INSTALL_ARGS += INSTALL_OWNER=

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
COMPONENT_TEST_TRANSFORMS += '-e "/^parse_gids_test\|^strsplit_test\|^atofoo_test\|^hltq_test\|^sudo_conf\|^sudo_parseln\|^check_addr\|^check_base64\|^check_fill\|^iolog_path\|^check_symbols\|^sudoers\|^testsudoers\|^visudo\|^check_ttyname/!d"'
COMPONENT_TEST_TRANSFORMS += '-e "s/\(\/dev\/pts\/\)[0-9][0-9]*/\1\#/"'

VISUDO=$(BUILD_DIR_64)/plugins/sudoers/visudo

$(SOLARIS_11_ONLY)REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/security/crypto
REQUIRED_PACKAGES += system/network/ldap/openldap
REQUIRED_PACKAGES += text/groff/groff-core
