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
# Copyright (c) 2010, 2015, Oracle and/or its affiliates. All rights reserved.
#

include $(WS_MAKE_RULES)/prep-download.mk
include $(WS_MAKE_RULES)/prep-unpack.mk
include $(WS_MAKE_RULES)/prep-patch.mk


# If the recipe author only defined the COMPONENT_SRC_N variables, we can
# still guess many others needed for building and packaging.
# Also we can set proper environments for configuration, build and install of
# such sub-components, similar to what shared-macros.mk define for base vars.
define default-suffixdir-rules
ifdef COMPONENT_SRC$(1)
ifneq ($(strip $$(COMPONENT_SRC$(1))),)

ifdef BUILD_DIR

ifdef MACH32
ifndef BUILD_DIR_32$(1)
BUILD_DIR_32$(1) = $$(BUILD_DIR)/$$(COMPONENT_SRC$(1))-$$(MACH32)
endif
endif

ifdef MACH64
ifndef BUILD_DIR_64$(1)
BUILD_DIR_64$(1) = $$(BUILD_DIR)/$$(COMPONENT_SRC$(1))-$$(MACH64)
endif
endif

endif



ifneq ($(strip $(1)),)

ifdef COMPONENT_VERSION$(1)
PKG_OPTIONS +=  -D COMPONENT_VERSION$(1)="$$(COMPONENT_VERSION$(1))"
endif

ifdef COMPONENT_NAME$(1)
PKG_OPTIONS +=  -D COMPONENT_NAME$(1)="$$(COMPONENT_NAME$(1))"
endif

ifdef COMPONENT_PROJECT_URL$(1)
PKG_OPTIONS +=  -D COMPONENT_PROJECT_URL$(1)="$$(COMPONENT_PROJECT_URL$(1))"
endif

ifdef COMPONENT_ARCHIVE_URL$(1)
PKG_OPTIONS +=  -D COMPONENT_ARCHIVE_URL$(1)="$$(COMPONENT_ARCHIVE_URL$(1))"
endif

ifdef COMPONENT_LICENSE$(1)
PKG_OPTIONS +=  -D COMPONENT_LICENSE$(1)="$$(COMPONENT_LICENSE$(1))"
endif

ifdef COMPONENT_LICENSE_FILE$(1)
PKG_OPTIONS +=  -D COMPONENT_LICENSE_FILE$(1)="$$(COMPONENT_LICENSE_FILE$(1))"
endif

ifdef IPS_COMPONENT_VERSION$(1)
PKG_OPTIONS +=  -D IPS_COMPONENT_VERSION$(1)="$$(IPS_COMPONENT_VERSION$(1))"
endif

ifdef COMPONENT_FMRI$(1)
PKG_OPTIONS +=  -D COMPONENT_FMRI$(1)="$$(COMPONENT_FMRI$(1))"
endif

ifdef COMPONENT_DESCRIPTION$(1)
PKG_OPTIONS +=  -D COMPONENT_DESCRIPTION$(1)="$$(COMPONENT_DESCRIPTION$(1))"
endif

ifdef COMPONENT_SUMMARY$(1)
PKG_OPTIONS +=  -D COMPONENT_SUMMARY$(1)="$$(COMPONENT_SUMMARY$(1))"
endif

ifdef COMPONENT_CLASSIFICATION$(1)
PKG_OPTIONS +=  -D COMPONENT_CLASSIFICATION$(1)="$$(COMPONENT_CLASSIFICATION$(1))"
endif

ifdef BUILD_DIR_32$(1)
BUILD_32 +=		$$(BUILD_DIR_32$(1))/.built
INSTALL_32 +=	$$(BUILD_DIR_32$(1))/.installed
$$(BUILD_DIR_32$(1))/.configured: $$(SOURCE_DIR$(1))/.prep
$$(BUILD_DIR_32$(1))/.configured: BITS=32
$$(BUILD_DIR_32$(1))/.configured: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_32$(1))/.built: $$(BUILD_DIR_32$(1))/.configured
$$(BUILD_DIR_32$(1))/.built: BITS=32
$$(BUILD_DIR_32$(1))/.built: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_32$(1))/.built: BUILD_DIR_32=$$(BUILD_DIR_32$(1))
$$(BUILD_DIR_32$(1))/.installed: $$(BUILD_DIR_32$(1))/.built
$$(BUILD_DIR_32$(1))/.installed: BITS=32
$$(BUILD_DIR_32$(1))/.installed: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_32$(1))/.installed: BUILD_DIR_32=$$(BUILD_DIR_32$(1))

ifeq ($(strip $(wildcard $$(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
TEST_32 +=		$$(BUILD_DIR_32$(1))/.tested
$$(BUILD_DIR_32$(1))/.tested: $$(BUILD_DIR_32$(1))/.installed
$$(BUILD_DIR_32$(1))/.tested: BITS=32
$$(BUILD_DIR_32$(1))/.tested: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_32$(1))/.tested: BUILD_DIR_32=$$(BUILD_DIR_32$(1))
else
TEST_32 +=		$$(BUILD_DIR_32$(1))/.tested-and-compared
$$(BUILD_DIR_32$(1))/.tested-and-compared: $$(BUILD_DIR_32$(1))/.installed
$$(BUILD_DIR_32$(1))/.tested-and-compared: BITS=32
$$(BUILD_DIR_32$(1))/.tested-and-compared: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_32$(1))/.tested-and-compared: BUILD_DIR_32=$$(BUILD_DIR_32$(1))
endif

endif

ifdef BUILD_DIR_64$(1)
BUILD_64 +=		$$(BUILD_DIR_64$(1))/.built
INSTALL_64 +=	$$(BUILD_DIR_64$(1))/.installed
$$(BUILD_DIR_64$(1))/.configured: $$(SOURCE_DIR$(1))/.prep
$$(BUILD_DIR_64$(1))/.configured: BITS=64
$$(BUILD_DIR_64$(1))/.configured: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_64$(1))/.built: $$(BUILD_DIR_64$(1))/.configured
$$(BUILD_DIR_64$(1))/.built: BITS=64
$$(BUILD_DIR_64$(1))/.built: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_64$(1))/.built: BUILD_DIR_64=$$(BUILD_DIR_64$(1))
$$(BUILD_DIR_64$(1))/.installed: $$(BUILD_DIR_64$(1))/.built
$$(BUILD_DIR_64$(1))/.installed: BITS=64
$$(BUILD_DIR_64$(1))/.installed: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_64$(1))/.installed: BUILD_DIR_64=$$(BUILD_DIR_64$(1))

ifeq ($(strip $(wildcard $$(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
TEST_64 +=		$$(BUILD_DIR_64$(1))/.tested
$$(BUILD_DIR_64$(1))/.tested: $$(BUILD_DIR_64$(1))/.installed
$$(BUILD_DIR_64$(1))/.tested: BITS=64
$$(BUILD_DIR_64$(1))/.tested: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_64$(1))/.tested: BUILD_DIR_64=$$(BUILD_DIR_64$(1))
else
TEST_64 +=		$$(BUILD_DIR_64$(1))/.tested-and-compared
$$(BUILD_DIR_64$(1))/.tested-and-compared: $$(BUILD_DIR_64$(1))/.installed
$$(BUILD_DIR_64$(1))/.tested-and-compared: BITS=64
$$(BUILD_DIR_64$(1))/.tested-and-compared: SOURCE_DIR=$$(SOURCE_DIR$(1))
$$(BUILD_DIR_64$(1))/.tested-and-compared: BUILD_DIR_64=$$(BUILD_DIR_64$(1))
endif

endif


endif

endif
endif
endef


# Define fallbacks if the recipe provides only suffixed variables, but not
# the base variables (e.g. "COMPONENT_SRC" not defined) - in this case, use
# the *_1 variables as base ones, since the values are needed for other rules.
define default-basedir-rules
ifndef COMPONENT_SRC
ifdef COMPONENT_SRC_1
COMPONENT_SRC = $$(COMPONENT_SRC_1)

ifdef SOURCE_DIR_1
SOURCE_DIR = $$(SOURCE_DIR_1)
endif

ifdef BUILD_DIR_32_1
BUILD_DIR_32 = $$(BUILD_DIR_32_1)
endif

ifdef BUILD_DIR_64_1
BUILD_DIR_64 = $$(BUILD_DIR_64_1)
endif

ifndef COMPONENT_FMRI
ifdef COMPONENT_FMRI_1
COMPONENT_FMRI = $$(COMPONENT_FMRI_1)
endif
endif

ifndef COMPONENT_VERSION
ifdef COMPONENT_VERSION_1
COMPONENT_VERSION = $$(COMPONENT_VERSION_1)
endif
endif

ifndef IPS_COMPONENT_VERSION
ifdef IPS_COMPONENT_VERSION_1
IPS_COMPONENT_VERSION = $$(IPS_COMPONENT_VERSION_1)
endif
endif

ifndef COMPONENT_LICENSE_FILE
ifdef COMPONENT_LICENSE_FILE_1
COMPONENT_LICENSE_FILE = $$(COMPONENT_LICENSE_FILE_1)
endif
endif

ifndef COMPONENT_LICENSE
ifdef COMPONENT_LICENSE_1
COMPONENT_LICENSE = $$(COMPONENT_LICENSE_1)
endif
endif

ifndef COMPONENT_NAME
ifdef COMPONENT_NAME_1
COMPONENT_NAME = $$(COMPONENT_NAME_1)
endif
endif

ifndef COMPONENT_ARCHIVE_URL
ifdef COMPONENT_ARCHIVE_URL_1
COMPONENT_ARCHIVE_URL = $$(COMPONENT_ARCHIVE_URL_1)
endif
endif

ifndef COMPONENT_PROJECT_URL
ifdef COMPONENT_PROJECT_URL_1
COMPONENT_PROJECT_URL = $$(COMPONENT_PROJECT_URL_1)
endif
endif

ifndef COMPONENT_SUMMARY
ifdef COMPONENT_SUMMARY_1
COMPONENT_SUMMARY = $$(COMPONENT_SUMMARY_1)
endif
endif

ifndef COMPONENT_DESCRIPTION
ifdef COMPONENT_DESCRIPTION_1
COMPONENT_DESCRIPTION = $$(COMPONENT_DESCRIPTION_1)
endif
endif

ifndef COMPONENT_CLASSIFICATION
ifdef COMPONENT_CLASSIFICATION_1
COMPONENT_CLASSIFICATION = $$(COMPONENT_CLASSIFICATION_1)
endif
endif

endif
endif
endef

# Define how each sub-component source directory should be prepped
# Note: the IFEQ directives can not be used in functions, but the
# $(if "string",then,else") functions can. The string is automatically
# stripped of surrounding whitespace and then not-empty == true.
# The clause below uses the custom $(COMPONENT_PREP_ACTION$(1))
# if both $(1) and the custom variable are not empty; otherwise it
# falls back to whateve value of common $(COMPONENT_PREP_ACTION).
#	@echo "=== 1 = '$(1)'; SOURCE_DIR$(1) = '$$(SOURCE_DIR$(1))'; COMPONENT_SRC$(1) = '$$(COMPONENT_SRC$(1))'; BUILD_DIR_32$(1) = '$$(BUILD_DIR_32$(1))'; BUILD_DIR_64$(1) = '$$(BUILD_DIR_64$(1))'; COMPONENT_PREP_ACTION$(1) = '$$(COMPONENT_PREP_ACTION$(1))'"
#	@echo "=== base vars:  SOURCE_DIR = '$$(SOURCE_DIR)'; COMPONENT_SRC = '$$(COMPONENT_SRC)'; BUILD_DIR_32 = '$$(BUILD_DIR_32)'; BUILD_DIR_64 = '$$(BUILD_DIR_64)'; COMPONENT_PREP_ACTION = '$$(COMPONENT_PREP_ACTION)'"
COMPONENT_PREP_ACTION ?= (true)

define prep-rules
ifdef SOURCE_DIR$(1)

ifndef COMPONENT_PREP_ACTION$(1)
$(if $(1),COMPONENT_PREP_ACTION$(1) ?= $$(COMPONENT_PREP_ACTION))
endif

$$(SOURCE_DIR$(1))/.prep:	download unpack patch
	$$(COMPONENT_PREP_ACTION$(1))
	$(TOUCH) $$@

prep::	$$(SOURCE_DIR$(1))/.prep

endif
endef


### Actual rules (explicit and template-calls) follow here
# PCK_SUFFIXES are defined by prep-unpack.mk based on COMPONENT_ARCHIVE_[0-9]+
# make-variable names defined before including this file into a recipe

download::

unpack::	download

patch::		unpack

$(eval $(call default-suffixdir-rules,))
$(foreach suffix, $(PCK_SUFFIXES), $(eval $(call default-suffixdir-rules,_$(suffix))))

$(eval $(call default-basedir-rules,))

$(eval $(call prep-rules,))
$(foreach suffix, $(PCK_SUFFIXES), $(eval $(call prep-rules,_$(suffix))))

clean::
	$(PRE_CLEAN_ACTION)
	$(RM) -r $(CLEAN_PATHS)

clobber::	clean
	$(RM) -r $(CLOBBER_PATHS)

