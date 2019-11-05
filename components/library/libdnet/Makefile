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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libdnet
COMPONENT_VERSION=	1.12
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://code.google.com/p/libdnet/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:b6360659c93fa2e3cde9e0a1fc9c07bc4111f3448c5de856e095eb98315dd424
COMPONENT_ARCHIVE_URL=\
  https://github.com/dugsong/libdnet/archive/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Needed to generate libraries with a .so extension.
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; libtoolize --automake --copy ; \
		aclocal -I config ; \
		autoheader ; \
		automake --add-missing --copy ; \
		autoconf)

# Set -m32 or -m64 correctly for 32 and 64 bit versions.
CC +=	$(CC_BITS)

# Remove Linux specific functionality.
CONFIGURE_OPTIONS += ac_cv_dnet_linux_pf_packet=no

# Uncomment if you have the Check unit testing framework installed.
#CONFIGURE_OPTIONS +=	--with-check=/usr

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Tests for libdnet are not enabled by default as they use the Check unit
# testing framework which is currently not present on Solaris. See:
# http://check.sourceforge.net/ for more details.
# If you do have Check on your system, then uncomment the TEST_32 line.
test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
