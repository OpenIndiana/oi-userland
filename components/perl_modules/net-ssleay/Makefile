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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Net-SSLeay
COMPONENT_VERSION=	1.52
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	http://search.cpan.org/dist/Net-SSLeay/
COMPONENT_ARCHIVE_HASH=	\
    sha256:48ece32f8f1b4c20acedfcaefd5d66f0ab8818ae6f994ab7c02da7f42e6d77ba
COMPONENT_ARCHIVE_URL=	http://search.cpan.org/CPAN/authors/id/M/MI/MIKEM/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	perl-mod/net-ssleay


include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/makemaker.mk
include $(WS_TOP)/make-rules/ips.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# The component Makefile.PL file will ask some questions on whether we want
# to run external tests, to which we want to answer with "n".
COMPONENT_CONFIGURE_ENV += ; echo "n" |
COMPONENT_TEST_TARGETS = test

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
