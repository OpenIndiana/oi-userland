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
COMPONENT_VERSION=	3.7.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	The DBI PostgreSQL Interface for Perl
COMPONENT_SRC=		DBD-Pg-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:e36e0459c9cf0f12edafb74f4cef685876d0460dbe6b411e7109070c67e56459
COMPONENT_ARCHIVE_URL= \
  http://search.cpan.org/CPAN/authors/id/T/TU/TURNSTEP/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://search.cpan.org/dist/DBD-Pg/Pg.pm

# Don't depend on host default pg_config
PATH=$(PG_BINDIR):/usr/sbin:/usr/bin:/usr/perl5/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/makemaker.mk
include $(WS_MAKE_RULES)/ips.mk

LD_OPTIONS += -L$(PG_LIBDIR) -R$(PG_LIBDIR)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += database/postgres-94/library
REQUIRED_PACKAGES += library/perl-5/database
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
