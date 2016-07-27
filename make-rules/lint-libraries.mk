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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

#
# Rules and Macros for building lint libraries.  This searches for lint
# libraries in the component directory and adds targets to build and install
# them for 32/64 bit.
#
# To use these rules, include $(WS_TOP)/make-rules/lint-libraries.mk in your
# Makefile and add your lint library source in your component directory as
# llib-l{lib}.
#
# Makefile
#    include $(WS_TOP)/make-rules/lint-libraries.mk
#
# llib-l{libname}
#

# Files resolved relative to (or rather IN) the COMPONENT_DIR
LINT_LIBRARIES = $(wildcard llib-*)

LINT_FLAGS = -nsvx -I$(@D) -I$(SOURCE_DIR)/include -I$(SOURCE_DIR)

# Template for lint library rules. new rules will be added automatically
# The directory variables will be resolved at build-time of each instance of
# the recipe

# arg1 = basename of llib-* file located in the COMPONENT_DIR
# arg2 = BUILD_DIR_32 for this sub-component
# arg3 = BUILD_DIR_64 for this sub-component
# arg4 = PROTOUSRLIBDIR for this sub-component
# arg5 = PROTOUSRLIBDIR64 for this sub-component
define lintlib-rule-dir-build-proto
$(2)/$(1).ln:	BITS=32
$(3)/$(1).ln:	BITS=64

$(2)/$(1).ln:	$$(COMPONENT_DIR)/$(1) $(2)/.built
	(cd $$(@D) ; $$(LINT) $$(LINT_FLAGS) -o $$(@F:llib-l%.ln=%) $$<)

$(3)/$(1).ln:	$$(COMPONENT_DIR)/$(1) $(3)/.built
	(cd $$(@D) ; $$(LINT) $$(LINT_FLAGS) -o $$(@F:llib-l%.ln=%) $$<)

$(4)/$(1):	$(1) $(2)/.installed
	$(INSTALL) -c $$< $$@

$(4)/$(1).ln:	$(2)/$(1).ln $(2)/.installed
	$(INSTALL) -c $$< $$@

$(5)/$(1).ln:	$(3)/$(1).ln $(3)/.installed
	$(INSTALL) -c $$< $$@

# Way to get circular deps
#BUILD_32 += $(2)/$(1).ln
#BUILD_64 += $(3)/$(1).ln
INSTALL_32 += $(4)/$(1)
INSTALL_32 += $(4)/$(1).ln
INSTALL_64 += $(5)/$(1).ln
endef

# For this variant arg1, arg2, arg3 are as above;
# use current PROTOUSRLIBDIR and PROTOUSRLIBDIR64
define lintlib-rule-dir-build
$(eval $(call lintlib-rule-dir-build-proto,$(1),$(2),$(3),$$(PROTOUSRLIBDIR),$$(PROTOUSRLIBDIR64)))
endef

# the original call name, only arg1 is user-specified
define lintlib-rule
$(eval $(call lintlib-rule-dir-build-proto,$(1),$$(BUILD_DIR_32),$$(BUILD_DIR_64),$$(PROTOUSRLIBDIR),$$(PROTOUSRLIBDIR64)))
endef

# These are the unique trailing numbers for enabled sub-components (if any)
BUILD_DIR_SUFFIXES = $(sort \
    $(subst BUILD_DIR_32_,, $(filter BUILD_DIR_32_%, $(.VARIABLES))) \
    $(subst BUILD_DIR_64_,, $(filter BUILD_DIR_64_%, $(.VARIABLES))) )

# Generate the lint library rules from the above template, both
# for the base directory and the numbered sub-components (if any)
# NOTE: To avoid same-name conflicts during installation, the Makefile recipe
# and its .p5m manifest(s) should deliver the files with unique names, e.g.
# you can make a $(INSTALL) recipe like above based on the .ln built above
# to produce a filename in protodir with the $(COMPONENT_VERSION) embeded.
$(foreach lintlib,$(LINT_LIBRARIES),$(eval $(call lintlib-rule,$(lintlib))))
$(foreach compnum,$(BUILD_DIR_SUFFIXES),$(eval \
  $(foreach lintlib,$(LINT_LIBRARIES),$(eval $(call lintlib-rule-dir-build,$(lintlib),$(BUILD_DIR_32_$(compnum)),$(BUILD_DIR_64_$(compnum))))) \
))
