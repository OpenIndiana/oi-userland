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
# Copyright (c) 2013, Colin Ellis. All rights reserved.
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libksba
COMPONENT_VERSION=      1.8.0
COMPONENT_SUMMARY=      GnuPG X.509 certificate library
COMPONENT_PROJECT_URL=  https://www.gnupg.org/related_software/$(COMPONENT_NAME)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:296b9db9095749f2aa104202d7ab7fd09ad10710e00780a709c9754b1a1d9292
COMPONENT_ARCHIVE_URL=  https://gnupg.org/ftp/gcrypt/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/security/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE=	COPYING.GPLv3

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += INSTALL="$(INSTALL)"

#CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-gpg-error-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-pic

COMPONENT_TEST_TRANSFORMS += \
	'-e "/All/p"' \
	'-e "/====/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
