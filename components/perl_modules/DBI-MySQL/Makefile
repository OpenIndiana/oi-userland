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
COMPONENT_VERSION=	4.0.24
COMPONENT_SUMMARY= 	The DBI MySQL Interface for Perl
COMPONENT_SRC=		DBD-mysql-4.024
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:fc65bb07ab86f71ff5d7ac4197d04e5c5dc54d9b3c4732f39330ec78e87682d4
COMPONENT_ARCHIVE_URL= \
  http://search.cpan.org/CPAN/authors/id/C/CA/CAPTTOFU/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://search.cpan.org/dist/DBD-mysql/lib/DBD/mysql.pm

# Don't depend on host default MySQL
PATH=/usr/mariadb/5.5/bin:/usr/sbin:/usr/bin:/usr/perl5/bin

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/makemaker.mk
include $(WS_TOP)/make-rules/ips.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# Workaround strange issue: 
# for Perl 5.10 some *.pm files are not installed
COMPONENT_POST_BUILD_ACTION += \
	(rm $(BUILD_DIR)/$(MACH32)-5.10.0/pm_to_blib && \
              $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) -C $(BUILD_DIR)/$(MACH32)-5.10.0/ pm_to_blib)

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
