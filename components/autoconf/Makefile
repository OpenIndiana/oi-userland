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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= NO_ARCH
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		autoconf
COMPONENT_VERSION=	2.69
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:64ebcec9f8ac5b2487125a86a7760d2591ac9e1d3dbd59489633f9de62a57684
COMPONENT_ANITYA_ID=	141

TPNO=			22294

SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_NO_ARCH)
include $(WS_MAKE_RULES)/gnu-component.mk

# with ksh93 as the configure shell, all tests pass
CONFIG_SHELL=$(BINDIR)/ksh93

CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += PERL="$(PERL)"
CONFIGURE_OPTIONS += M4="$(GNUBIN)/m4"

# The Makefile has different targets for the equivalent of "gmake test" and
# "gmake system-test".
COMPONENT_TEST_TARGETS =	check-local
COMPONENT_TEST_DIR =		$(@D)/tests
COMPONENT_TEST_ENV +=		F77=/usr/bin/gfortran

COMPONENT_SYSTEM_TEST_TARGETS =	installcheck
COMPONENT_SYSTEM_TEST_DIR =	$(@D)/tests
COMPONENT_SYSTEM_TEST_ENV +=	F77=/usr/bin/gfortran

COMPONENT_TEST_TRANSFORMS += \
        '-e "/check-local/d"' \
        '-e "/ksh93/d"' \
        '-e "/Entering directory/d"' \
        '-e "/Leaving directory/d"' \
        '-e "/^make/d"'

REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
