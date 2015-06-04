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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

# PHP_TOP_DIR is for everything PHP-related (PHP, third party extensions, and
# one-off build dependencies like uw-imap)
PHP_TOP_DIR = $(WS_COMPONENTS)/php

# Get version numbers. Change this include (and/or implement support for
# multiple versions) when adding a new minor/major version of PHP.
include $(PHP_TOP_DIR)/php56/php56-metadata.mk

# PHP_BUNDLE_DIR is for everything we build from the PHP tarball (bundle).
PHP_BUNDLE_DIR = $(PHP_TOP_DIR)/php$(UL_PHP_SHORT_VERSION)
PHP_COMPONENT_SRC = php-$(UL_PHP_VERSION)
PHP_SOURCE_DIR = $(PHP_BUNDLE_DIR)/$(PHP_COMPONENT_SRC)
PHP_BUILD_DIR = $(PHP_BUNDLE_DIR)/build
PHP_BUILD_DIR_64 = $(PHP_BUILD_DIR)/$(MACH64)
PHP_PROTO_DIR = $(PHP_BUILD_DIR)/prototype/$(MACH)

