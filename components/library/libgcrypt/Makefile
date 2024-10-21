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
# Copyright 2013 Colin Ellis. All rights reserved.
# Copyright 2011 Audioboo Ltd. All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgcrypt
COMPONENT_VERSION=	1.11.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	GnuPG libgcrypt library
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libgcrypt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:09120c9867ce7f2081d6aaa1775386b98c2f2f246135761aae47d81f58685b9c
COMPONENT_ARCHIVE_URL=	https://gnupg.org/ftp/gcrypt/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/library/security/libgcrypt
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_LICENSE=	GPL-2.0-only AND LGPL-2.1-only AND BSD-3-Clause

include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		printf -- '--- LICENSES --------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/LICENSES ; \
		printf '\n--- COPYING ---------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING ; \
		printf '\n--- COPYING.LIB -----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.LIB \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# We do not want the info index file
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Some tests are using mlock(3c) and expects it pass.  Since mlock() is
# restricted function in illumos we need to make sure the additional privileges
# are granted.
COMPONENT_PRE_TEST_ACTION += \
	/usr/bin/ppriv $$$$ | $(GNU_GREP) -q 'E:.*proc_lock_memory' || ( \
		/usr/bin/printf "\nERROR: The proc_lock_memory privilege is needed!!!\n\n" ; \
		/usr/bin/printf "Use\n\n\tusermod -K defaultpriv=basic,proc_lock_memory USERNAME\n" ; \
		/usr/bin/printf "\nto grant the required privileges.\n\n" ; \
		exit 1 ) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
