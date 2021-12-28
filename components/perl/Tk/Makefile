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
# Copyright (c) 2021, Friedrich Kink. All rights reserved.
#


include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Tk
COMPONENT_VERSION=	804.036
IPS_COMPONENT_VERSION=	5.11
COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/tk
COMPONENT_SUMMARY=	Tk - a graphical user interface toolkit for Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Tk
COMPONENT_ARCHIVE_HASH=	sha256:32aa7271a6bdfedc3330119b3825daddd0aa4b5c936f84ad74eabb932a200a5e
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/S/SR/SREZIC/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	various
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/makemaker.mk
include $(WS_TOP)/make-rules/ips.mk

TEST_TARGET=$(NO_TESTS)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxft
