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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cx_Oracle
COMPONENT_VERSION=	5.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=		\
	sha256:c580d5e7fa9748326dbae22f5832401f229ddda5354ec17120d9b28893925bbb
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=  http://cx-oracle.sourceforge.net/
COMPONENT_BUGDB=	python-mod/cx_oracle

TPNO=			23247

# Specifying PYTHON2_VERSIONS so that we don't get the 2.6
# version built as well. It's an oversight in setup.py.mk
# that isn't worth fixing since 2.6 is going away very soon.
PYTHON2_VERSIONS=	2.7
PYTHON_VERSIONS=	2.7 $(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/setup.py.mk

# common targets

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# We do not run automated tests of this package because doing
# requires access to a captive Oracle database instance.
test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += database/oracle/instantclient
REQUIRED_PACKAGES += developer/oracle/instantclient/sdk
REQUIRED_PACKAGES += system/library
