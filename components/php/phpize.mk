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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

# This is a collection of Makefile lines needed for building PHP extensions
# outside of the PHP source tree.  It is named for the "phpize" script, which
# is the main deviation from the standard configure-make-install cycle.
# This file should handle everything necessary for an extension whose upstream
# expects the user to run "phpize" in order to create ./configure.

# Extension builds rely on installed versions of the PHP interpreters to
# access phpize and php-config.
# If the interpreters are being revved then look for commented out lines
# below to switch the extension builds to use interpreters in the build tree.

# xdebug is a good example of building an extension.

$(BUILD_DIR)/$(MACH64)-5.6/.configured: UL_PHP_MINOR_VERSION=5.6
$(BUILD_DIR)/$(MACH64)-5.6/.configured: BITS=64
$(BUILD_DIR)/$(MACH64)-7.1/.configured: UL_PHP_MINOR_VERSION=7.1
$(BUILD_DIR)/$(MACH64)-7.1/.configured: BITS=64

$(BUILD_DIR)/$(MACH64)-5.6/.built:      UL_PHP_MINOR_VERSION=5.6
$(BUILD_DIR)/$(MACH64)-5.6/.built:      BITS=64
$(BUILD_DIR)/$(MACH64)-7.1/.built:      UL_PHP_MINOR_VERSION=7.1
$(BUILD_DIR)/$(MACH64)-7.1/.built:      BITS=64

$(BUILD_DIR)/$(MACH64)-5.6/.installed:  UL_PHP_MINOR_VERSION=5.6
$(BUILD_DIR)/$(MACH64)-5.6/.installed:  BITS=64
$(BUILD_DIR)/$(MACH64)-7.1/.installed:  UL_PHP_MINOR_VERSION=7.1
$(BUILD_DIR)/$(MACH64)-7.1/.installed:  BITS=64

$(BUILD_DIR)/$(MACH64)-5.6/.tested:	UL_PHP_MINOR_VERSION=5.6
$(BUILD_DIR)/$(MACH64)-5.6/.tested:	BITS=64
$(BUILD_DIR)/$(MACH64)-7.1/.tested:	UL_PHP_MINOR_VERSION=7.1
$(BUILD_DIR)/$(MACH64)-7.1/.tested:	BITS=64

$(BUILD_DIR)/$(MACH64)-5.6/.tested-and-compared: UL_PHP_MINOR_VERSION=5.6
$(BUILD_DIR)/$(MACH64)-5.6/.tested-and-compared: BITS=64
$(BUILD_DIR)/$(MACH64)-7.1/.tested-and-compared: UL_PHP_MINOR_VERSION=7.1
$(BUILD_DIR)/$(MACH64)-7.1/.tested-and-compared: BITS=64

$(BUILD_DIR)/$(MACH64)-5.6/.system-tested: UL_PHP_MINOR_VERSION=5.6
$(BUILD_DIR)/$(MACH64)-5.6/.system-tested: BITS=64
$(BUILD_DIR)/$(MACH64)-7.1/.system-tested: UL_PHP_MINOR_VERSION=7.1
$(BUILD_DIR)/$(MACH64)-7.1/.system-tested: BITS=64

$(BUILD_DIR)/$(MACH64)-5.6/.system-tested-and-compared: UL_PHP_MINOR_VERSION=5.6
$(BUILD_DIR)/$(MACH64)-5.6/.system-tested-and-compared: BITS=64
$(BUILD_DIR)/$(MACH64)-7.1/.system-tested-and-compared: UL_PHP_MINOR_VERSION=7.1
$(BUILD_DIR)/$(MACH64)-7.1/.system-tested-and-compared: BITS=64

CONFIGURE_64 = $(PHP_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.configured)
BUILD_64     = $(PHP_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
INSTALL_64   = $(PHP_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)

# determine the type of tests we want to run.
ifeq ($(strip $(wildcard $(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
TEST_64      = $(PHP_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested)
else
TEST_64      = $(PHP_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared)
endif

ifeq ($(strip $(wildcard $(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
SYSTEM_TEST_64 = $(PHP_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.system-tested)
else
SYSTEM_TEST_64 = $(PHP_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.system-tested-and-compared)
endif

PHP_VERSION_NODOT = $(subst .,,$(UL_PHP_MINOR_VERSION))
PHP_HOME = $(PHP_TOP_DIR)/php$(PHP_VERSION_NODOT)

# Building extensions with interpreters from the build tree
# is time consuming.
# If revving the php interpreters then temporarily switch to building
# extensions against those.
#PHP_INSTALLED = $(PHP_HOME)/build/$(MACH64)/.installed
#$(CONFIGURE_64): $(PHP_INSTALLED)
#$(BUILD_DIR)/$(MACH64)-5.6/.configured: \
#	$(PHP_TOP_DIR)/php56/build/$(MACH64)/.installed
#
#$(BUILD_DIR)/$(MACH64)-7.1/.configured: \
#	$(PHP_TOP_DIR)/php71/build/$(MACH64)/.installed
#
#$(PHP_TOP_DIR)/php56/build/$(MACH64)/.installed \
#$(PHP_TOP_DIR)/php71/build/$(MACH64)/.installed:
#	cd $(PHP_HOME) ; $(GMAKE) install ;

# If revving php interpreters use those instead for building extensions.
#		< $(PHP_HOME)/proto-scripts/phpize-proto
COMPONENT_PRE_CONFIGURE_ACTION += \
	$(GSED) -e "s|^builddir=.*|builddir=$(@D)|" \
		< /usr/php/$(UL_PHP_MINOR_VERSION)/bin/phpize \
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

# If revving php interpreters use those instead for building extensions.
# Change PHP_EXECUTABLE so that tests can run.
#PROTOUSRPHPVERDIR = $(PHP_HOME)/build/prototype/$(MACH)/$(CONFIGURE_PREFIX)
#COMPONENT_PRE_CONFIGURE_ACTION += \
#	$(GSED) -i -e "s@^PHP_EXECUTABLE=.*@PHP_EXECUTABLE=$(PROTOUSRPHPVERDIR)/bin/php@" \
#		$(CONFIGURE_SCRIPT) ;

# If revving php interpreters use those instead for building extensions.
#		cp $(PHP_HOME)/proto-scripts/php-config-proto $(@D) ;
COMPONENT_PRE_CONFIGURE_ACTION += \
    cp /usr/php/$(UL_PHP_MINOR_VERSION)/bin/php-config $(@D)/php-config-proto ;
CONFIGURE_OPTIONS += --with-php-config=$(@D)/php-config-proto
