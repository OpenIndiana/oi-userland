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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018 Norm Jacobs
# Copyright (c) 2018 Ken Mays
# Copyright (c) 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		binutils
COMPONENT_VERSION=	2.32
COMPONENT_SUMMARY=	GNU collection of binary tools like ld, as
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/binutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
	sha256:0ab6c55dd86a92ed561972ba15b9b70a8b9f75557f896446c82e8b36e473ee04
COMPONENT_FMRI=		developer/gnu-binutils
COMPONENT_CLASSIFICATION=Development/GNU

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_PREFIX =	/usr/gnu

CONFIGURE_OPTIONS +=	--mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	--enable-64-bit-bfd
CONFIGURE_OPTIONS +=    --enable-gold=no
CONFIGURE_OPTIONS +=    --enable-plugins=no
CONFIGURE_OPTIONS +=    --enable-nls
CONFIGURE_OPTIONS +=    --disable-libtool-lock
CONFIGURE_OPTIONS +=    --enable-largefile=yes
CONFIGURE_OPTIONS +=	--with-system-zlib
CONFIGURE_OPTIONS +=    --target=$(GNU_TRIPLET)

COMPONENT_TEST_ARGS += -k

# Keep only the test results.  Details are always in the build directory
COMPONENT_TEST_TRANSFORMS += \
	'-n '\
	'-e "/^\# of/p" '\
	'-e "/Summary =/p" '

$(INSTALL_32):	$(INSTALL_64)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
