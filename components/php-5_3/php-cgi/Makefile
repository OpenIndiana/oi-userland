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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		php
COMPONENT_VERSION=	5.3.29
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:c4e1cf6972b2a9c7f2777a18497d83bf713cdbecabb65d3ff62ba441aebb0091
COMPONENT_ARCHIVE_URL=	http://us.php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror

PATCH_DIR = ../php-sapi/patches

include ../php-sapi/php.mk

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

include ../common.mk

CONFIGURE_OPTIONS  += \
	--disable-all \
	$(COMMON_CONFIG_OPTIONS) \
	--with-config-file-path=$(NSAPI_CONF_DIR) \
	--with-config-file-scan-dir=$(MODULES_CONF_DIR) \
	--disable-discard-path \
	--enable-cgi \
	--enable-fastcgi \
	--enable-force-cgi-redirect

CONFIGURE_ENV += $(CONF_ENVLINE)

COMPONENT_INSTALL_TARGETS = install-sapi

# Test results not quite stable but good enough for human eyes
$(SKIP_TEST_AT_TOP_LEVEL)

configure:	$(CONFIGURE_32)

build:		$(BUILD_32)

install:	$(INSTALL_32)

# These test and compare results are not quite stable enough
# to use in automated testing but good enough to eye
# ball and get a sense that php is working correctly.
# Individual tests can be run afterwards.
# Several random tests may PASS/FAIL on each run thus invalidating
# test and compare results.
# To use the master test result file do:
# $ gmake build
# $ gmake -i -k test
# because very likely the comparison phase will fail.

# test failures; keep going
COMPONENT_TEST_ARGS += -k -i

# different results for different architectures
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH$(BITS)).master

test:		$(TEST_32)

system-test:	$(SYSTEM_TEST_NOT_IMPLEMENTED)

# php-sapi does the publish
publish:	install
