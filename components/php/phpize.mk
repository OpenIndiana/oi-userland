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

# This is a collection of Makefile lines needed for building PHP extensions
# outside of the PHP source tree.  It is named for the "phpize" script, which
# is the main deviation from the standard configure-make-install cycle.
# This file should handle everything necessary for an extension whose upstream
# expects the user to run "phpize" in order to create ./configure.

# It relies on the Userland makefile for PHP creating modified versions of
# phpize and php-config for use during Userland builds, and placing them under
# $(PHP_BUNDLE_DIR)/proto-scripts. Therefore, it depends on gmake install of PHP

# Usage:
# include ../../../make-rules/shared-macros.mk [appropriate path]
# include $(WS_COMPONENTS)/php/php-metadata.mk
# [COMPONENT_* lines]
# include $(WS_MAKE_RULES)/prep.mk
# include $(WS_MAKE_RULES)/configure.mk
# include $(PHP_TOP_DIR)/phpize.mk

# Depends on having a built and intalled (prototype) version of PHP available
$(BUILD_DIR_64)/.configured: $(PHP_BUILD_DIR_64)/.installed
$(PHP_BUILD_DIR_64)/.installed:
	cd $(PHP_BUNDLE_DIR) ; $(GMAKE) install ;

include $(PHP_TOP_DIR)/php.mk

COMPONENT_PRE_CONFIGURE_ACTION += \
	$(GSED) -e "s|^builddir=.*|builddir=$(@D)|" \
		< $(PHP_BUNDLE_DIR)/proto-scripts/phpize-proto \
		> $(@D)/phpize-proto; \
	chmod +x $(@D)/phpize-proto;

# .tgz files from pecl contain this file
CLEAN_PATHS += package.xml

# The phpize script tries to copy some files into here, failing if the directory
# doesn't exist.
COMPONENT_PRE_CONFIGURE_ACTION += mkdir $(@D)/build;

# phpize generates configure where it is run.
COMPONENT_PRE_CONFIGURE_ACTION += $(CLONEY) $(SOURCE_DIR) $(@D) ;
CONFIGURE_SCRIPT = $(@D)/configure
COMPONENT_PRE_CONFIGURE_ACTION += cd $(@D) ; $(@D)/phpize-proto;

# Change PHP_EXECUTABLE so that tests can run.
PROTOUSRPHPVERDIR = $(PHP_PROTO_DIR)/$(CONFIGURE_PREFIX)
COMPONENT_PRE_CONFIGURE_ACTION += \
	$(GSED) -i -e "s@^PHP_EXECUTABLE=.*@PHP_EXECUTABLE=$(PROTOUSRPHPVERDIR)/bin/php@" \
		$(CONFIGURE_SCRIPT) ;

COMPONENT_PRE_CONFIGURE_ACTION += \
		cp $(PHP_BUNDLE_DIR)/proto-scripts/php-config-proto $(@D) ;
CONFIGURE_OPTIONS += --with-php-config=$(@D)/php-config-proto

