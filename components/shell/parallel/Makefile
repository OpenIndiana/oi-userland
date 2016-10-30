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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		parallel
COMPONENT_VERSION=	20160222
# A leading "0." is included to make it easier to upgrade the package, should
# the maintainers decide to go to a more standard version numbering system.
IPS_COMPONENT_VERSION=  0.2016.2.22
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/parallel/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:8dfbe539036a6ff02f9f542751e8621f42d285b3c9a7d9245042a6cc6ddc55ea
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	GNU parallel is a shell tool for executing jobs in parallel using one or more computers.
COMPONENT_FMRI=		shell/parallel
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv3
COMPONENT_CLASSIFICATION=	System/Shells

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Set PATH to find /usr/perl5/bin/pod2man, so that the man pages can be
# automatically generated
COMPONENT_BUILD_ENV +=    PATH="/usr/bin:/usr/gnu/bin:/usr/perl5/bin"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

include $(WS_MAKE_RULES)/depend.mk

REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += shell/which
