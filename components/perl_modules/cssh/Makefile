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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		App-ClusterSSH
COMPONENT_VERSION=	4.2.1
HUMAN_VERSION=		4.02_01
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4f1c1fc151f4dc38d3f5e5803fb39a2eee15b797650ca94cd6f673a670cdaad5
# This project is registered on SourceForge and CPAN
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/clusterssh/
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/clusterssh/2.%20ClusterSSH%20Series%204/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/cssh

TPNO=			13257

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/makemaker.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

# There are tests but:
#   Can't locate Test/Trap.pm
# they just fail.
test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += library/perl-5/perl-x11-protocol-522
REQUIRED_PACKAGES += library/perl-5/perl-tk-522
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
