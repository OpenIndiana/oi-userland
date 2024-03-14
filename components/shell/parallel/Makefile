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
# Copyright 2019, Michal Nowak
# Copyright 2020, Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		parallel
HUMAN_VERSION =		20230422
# A leading "0." is included to make it easier to upgrade the package, should
# the maintainers decide to go to a more standard version numbering system.
COMPONENT_VERSION =	2023.4.22
COMPONENT_SUMMARY=	GNU parallel is a shell tool for executing jobs in parallel using one or more computers.
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/parallel/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:9106593d09dc4de0e094b7b14390a309d8fcb1d27104a53814d16937dcbae3c2
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		shell/parallel
COMPONENT_CLASSIFICATION=	System/Shells
COMPONENT_LICENSE=	GPLv3,GFDL-1.3,CC-BY-SA-4.0

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/which
