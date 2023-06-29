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
# Copyright (c) 2020, Michal Nowak
# Copyright (c) 2020-2022 Nona Hansel
#

BUILD_BITS=		64
USE_OPENSSL11=	yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sudo
SRC_VERSION=		1.9.14
SRC_PATCH_VERSION=	0
SRC_DOT_PATCH_VERSION=	$(shell [ $(SRC_PATCH_VERSION) -gt 0 ] && echo .$(SRC_PATCH_VERSION))
SRC_P_PATCH_VERSION=	$(shell [ $(SRC_PATCH_VERSION) -gt 0 ] && echo p$(SRC_PATCH_VERSION))
HUMAN_VERSION=		$(SRC_VERSION)$(SRC_P_PATCH_VERSION)
COMPONENT_VERSION=	$(SRC_VERSION)$(SRC_DOT_PATCH_VERSION)
COMPONENT_SUMMARY=	sudo - tool to allow certain tasks to be run as root by ordinary users
COMPONENT_SRC=		$(COMPONENT_NAME)-$(SRC_VERSION)$(SRC_P_PATCH_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7bb70e4529ab2ada47ded970cdf2fe7be3084912861ddbac239eebdc92935a29
COMPONENT_ARCHIVE_URL=	https://www.sudo.ws/sudo/dist/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig	
COMPONENT_PROJECT_URL=  https://www.sudo.ws/
COMPONENT_FMRI=		security/sudo
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	ISC-like, BSD, zlib license
COMPONENT_LICENSE_FILE=	LICENSE.md

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV +=	MAKE=$(GMAKE)

COMPONENT_PREP_ACTION = ( cd $(@D)  && autoreconf -vif )

#CONFIGURE_OPTIONS +=	--disable-hardening
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-project
CONFIGURE_OPTIONS +=	--with-rundir=/var/run/sudo
CONFIGURE_OPTIONS +=	--with-pam 
CONFIGURE_OPTIONS +=	--with-pam-login
CONFIGURE_OPTIONS +=	--disable-pam-session
CONFIGURE_OPTIONS +=	--with-tty-tickets
CONFIGURE_OPTIONS +=	--without-insults
CONFIGURE_OPTIONS +=	--without-lecture
CONFIGURE_OPTIONS +=	--with-ignore-dot
CONFIGURE_OPTIONS +=	--with-bsm-audit
CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBDIR64)
#CONFIGURE_OPTIONS +=	"sudo_cv_var_nroff_opt_Tascii=no"

COMPONENT_BUILD_ENV +=	CC="$(CC)"
COMPONENT_BUILD_ENV +=	CXX="$(CXX)"
COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_TARGETS = install

COMPONENT_TEST_TRANSFORMS += '-ne "/OK/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/FAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/errors/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/failed/p" '

# Avoid calling "chown 0" on installed files
COMPONENT_INSTALL_ARGS += INSTALL_OWNER=

# Enable aslr for this component
ASLR_MODE = $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
