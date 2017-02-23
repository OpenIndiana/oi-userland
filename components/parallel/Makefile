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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		parallel
COMPONENT_VERSION=	20160222
# A leading "0." is included to make it easier to upgrade the package, should
# the maintainers decide to go to a more standard version numbering system.
IPS_COMPONENT_VERSION=  0.2016.2.22
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:8dfbe539036a6ff02f9f542751e8621f42d285b3c9a7d9245042a6cc6ddc55ea
COMPONENT_ANITYA_ID=	5448

TPNO=			27217

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/gnu-component.mk

# Set PATH to find the correct pod2man, so that the man pages can be
# automatically generated
COMPONENT_BUILD_ENV += \
	PATH="$(USRBINDIR):$(GNUBIN):$(USRDIR)/perl5/$(PERL_VERSION)/bin"

# Adjust '#!/usr/bin/perl'
PERL_SCRIPTS = \
	$(PROTOUSRBINDIR)/niceload \
	$(PROTOUSRBINDIR)/parallel \
	$(PROTOUSRBINDIR)/sql

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/which
REQUIRED_PACKAGES += system/core-os
