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

COMPONENT_NAME= 	DBI-MySQL
COMPONENT_VERSION=	4.0.41
COMPONENT_REVISION=	2
COMPONENT_SUMMARY= 	The DBI MySQL Interface for Perl
COMPONENT_SRC=		DBD-mysql-4.041
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:4777de11c464b515db9da95c08c225900d0594b65ba3256982dc21f9f9379040
COMPONENT_ARCHIVE_URL= \
  https://cpan.metacpan.org/authors/id/M/MI/MICHIELB/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://search.cpan.org/dist/DBD-mysql/lib/DBD/mysql.pm

# Don't depend on host default MySQL
PATH=$(MYSQL_BINDIR):/usr/sbin:/usr/bin:/usr/perl5/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/makemaker.mk
include $(WS_MAKE_RULES)/ips.mk

LD_OPTIONS += -L$(MYSQL_LIBDIR) -R$(MYSQL_LIBDIR)

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += database/mariadb-101/library
REQUIRED_PACKAGES += library/perl-5/database
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
