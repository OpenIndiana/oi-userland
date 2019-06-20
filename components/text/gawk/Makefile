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
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=          gawk
COMPONENT_VERSION=       5.0.1
COMPONENT_SUMMARY=       GNU awk
COMPONENT_PROJECT_URL=   https://www.gnu.org/software/gawk/
COMPONENT_FMRI=          text/gawk
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=           $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=       $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:8e4e86f04ed789648b66f757329743a0d6dfb5294c3b91b756a474f1ce05a794
COMPONENT_ARCHIVE_URL=   http://ftp.gnu.org/gnu/gawk/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=       GPLv3, FDLv1.3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS+= $(gcc_C99_ENABLE) $(CPP_XPG6MODE)
CFLAGS+= -I$(USRINCDIR)/mpfr -I$(USRINCDIR)/gmp

CONFIGURE_OPTIONS	+=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS	+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS	+=	--with-mpfr=$(LIBDIR.$(BITS))

COMPONENT_TEST_ENV+= LANG=C LC_ALL=C

COMPONENT_TEST_TRANSFORMS += \
	'-e "/\/usr\/gnu\/bin\/make/d" ' \
	'-e "/^make/d" ' \
	'-e "/^Making/d" ' \
	'-e "/^--- _/d" ' \
	'-e "s|\(\*\*\* \\$$(SOURCE_DIR)/test/[^[:space:]]*\).*|\1|g" '

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libsigsegv
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
