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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2017, Aurelien Larcher
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2020, Nona Hansel
#

BUILD_BITS=				64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			gawk
COMPONENT_VERSION=		5.2.2
COMPONENT_SUMMARY=		GNU awk
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/gawk/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:3c1fce1446b4cbee1cd273bd7ec64bc87d89f61537471cd3e05e33a965a250e9
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/gawk/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			text/gawk
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=		GPLv3, FDLv1.3

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(gcc_C99_ENABLE) $(CPP_XPG6MODE)

CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --with-mpfr=$(LIBDIR.$(BITS))

COMPONENT_TEST_ENV += LANG=C LC_ALL=C

COMPONENT_TEST_TRANSFORMS += \
	'-e "/\/usr\/gnu\/bin\/make/d" ' \
	'-e "/\/usr\/gcc/d" ' \
	'-e "/^make/d" ' \
	'-e "/^Making/d" ' \
	'-e "/^--- _/d" ' \
	'-e "s|\(\*\*\* \\$$(SOURCE_DIR)/test/[^[:space:]]*\).*|\1|g" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libsigsegv
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
