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
# Copyright (c) 2013, Alexander Pyhalov. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	DBI-PostgreSQL
COMPONENT_VERSION=	2.19.3
COMPONENT_SUMMARY= 	The DBI PostgreSQL Interface for Perl
COMPONENT_SRC=		DBD-Pg-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:37350d134b7fa88fb3b9432d92991e0a73f405bf5b3a4ee53430439280b8262a
COMPONENT_ARCHIVE_URL= \
  http://search.cpan.org/CPAN/authors/id/T/TU/TURNSTEP/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://search.cpan.org/dist/DBD-Pg/Pg.pm

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.32):/usr/sbin:/usr/bin:/usr/perl5/bin

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/makemaker.mk
include $(WS_TOP)/make-rules/ips.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
