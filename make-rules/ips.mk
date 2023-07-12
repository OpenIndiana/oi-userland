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
# Copyright (c) 2010, 2014, Oracle and/or its affiliates. All rights reserved.
# Copyright 2014 Andrzej Szeszo. All rights reserved.
#

#
# Rules and Macros for generating an IPS package manifest and publishing an
# IPS package to a pkg depot.
#
# To use these rules, include ../make-rules/ips.mk in your Makefile
# and define an "install" target appropriate to building your component.
# Ex:
#
#	install:	$(BUILD_DIR)/build/$(MACH32)/.installed \
#	 		$(BUILD_DIR)/build/$(MACH64)/.installed
#
# This set of rules makes the "publish" target the default target for make(1)
#
.NOTPARALLEL:

PKGDEPEND =	/usr/bin/pkgdepend
PKGFMT =	/usr/bin/pkgfmt
PKGMOGRIFY =	/usr/bin/pkgmogrify
PKGSEND =	/usr/bin/pkgsend
ifeq   ($(strip $(PKGLINT_COMPONENT)),)
PKGLINT =	/usr/bin/python /usr/bin/pkglint
else
PKGLINT =	${WS_TOOLS}/pkglint
endif
PKGMANGLE =	$(WS_TOOLS)/userland-mangler

WS_TRANSFORMS =    $(WS_TOP)/transforms

GENERATE_HISTORY= $(WS_TOOLS)/generate-history
HISTORY=	history

# Package headers should all pretty much follow the same format
METADATA_TEMPLATE =		$(WS_TOP)/transforms/manifest-metadata-template
COPYRIGHT_TEMPLATE =		$(WS_TOP)/transforms/copyright-template

# order is important
GENERATE_TRANSFORMS +=		$(WS_TOP)/transforms/generate-cleanup
ifeq	($(strip $(DROP_STATIC_LIBRARIES)),yes)
GENERATE_TRANSFORMS +=		$(WS_TOP)/transforms/archive-libraries-drop
endif

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/ignore-libs
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/ignore-gcc-usr-lib

LICENSE_TRANSFORMS =		$(WS_TOP)/transforms/license-changes

# order is important
PUBLISH_TRANSFORMS +=	$(LICENSE_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/variant-cleanup
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/autopyc
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/python
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/perl
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/defaults
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/actuators
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/devel
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/docs
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/locale
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/python-3-soabi
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/python-3-no-32bit
PUBLISH_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/publish-cleanup

FINAL_TRANSFORMS += 	$(WS_TOP)/transforms/final-cleanup

define add-limiting-variable
PKG_VARS += $(1)
MANIFEST_LIMITING_VARS += -D $(1)="$(subst #,\#,$($(1)))"
endef

# Make all the limiting variables available to manifest processing
$(foreach var, $(filter PY3_%_NAMING,$(.VARIABLES)), \
    $(eval $(call add-limiting-variable,$(var))))


ifeq   ($(strip $(COMPONENT_AUTOGEN_MANIFEST)),yes)
AUTOGEN_MANIFEST_TRANSFORMS +=		$(WS_TOP)/transforms/generate-cleanup
else
AUTOGEN_MANIFEST_TRANSFORMS +=		$(WS_TOP)/transforms/drop-all
endif

# For items defined as variables or that may contain whitespace, add
# them to a list to be expanded into PKG_OPTIONS later.
PKG_VARS += ARC_CASE TPNO
PKG_VARS += MACH MACH32 MACH64
PKG_VARS += BUILD_VERSION OS_VERSION PKG_SOLARIS_VERSION
PKG_VARS += GNU_TRIPLET
PKG_VARS += GCC_GNU_TRIPLET
PKG_VARS += CONSOLIDATION
PKG_VARS += COMPONENT_VERSION IPS_COMPONENT_VERSION HUMAN_VERSION
PKG_VARS += COMPONENT_ARCHIVE_URL COMPONENT_PROJECT_URL COMPONENT_NAME
PKG_VARS += COMPONENT_FMRI COMPONENT_LICENSE_FILE
PKG_VARS += COMPONENT_SUMMARY COMPONENT_DESCRIPTION COMPONENT_LICENSE
PKG_VARS += HG_REPO HG_REV HG_URL COMPONENT_HG_URL COMPONENT_HG_REV
PKG_VARS += GIT_COMMIT_ID GIT_REPO GIT_TAG
PKG_VARS += PUBLISHER PUBLISHER_LOCALIZABLE
PKG_VARS += USERLAND_GIT_REMOTE USERLAND_GIT_BRANCH USERLAND_GIT_REV

# For items that need special definition, add them to PKG_MACROS.
# IPS_COMPONENT_VERSION suitable for use in regular expressions.
PKG_MACROS += IPS_COMPONENT_RE_VERSION=$(subst .,\\.,$(IPS_COMPONENT_VERSION))
# COMPONENT_VERSION suitable for use in regular expressions.
PKG_MACROS += COMPONENT_RE_VERSION=$(subst .,\\.,$(COMPONENT_VERSION))

PKG_OPTIONS +=		$(PKG_MACROS:%=-D %) \
					-D COMPONENT_CLASSIFICATION="org.opensolaris.category.2008:$(strip $(COMPONENT_CLASSIFICATION))"

define mach-list-generate-macros
ifeq ($(MACH),$(1))
PKG_MACROS +=           $(1)_ONLY=
PKG_MACROS +=           $(1)_EXCL=\#
else
PKG_MACROS +=           $(1)_ONLY=\#
PKG_MACROS +=           $(1)_EXCL=
endif
endef
$(foreach isa,$(MACH_LIST),$(eval $(call mach-list-generate-macros,$(isa))))

define python-generate-macros
PKG_MACROS +=           PYTHON_$(1)_ONLY=\#
PKG_MACROS +=           PYTHON_$(1)_EXCL=
endef
$(foreach ver,$(PYTHON_VERSIONS),$(eval $(call python-generate-macros,$(ver))))

PKG_MACROS +=           PYTHON_32_ONLY=

MANGLED_DIR =	$(PROTO_DIR)/mangled

PKG_PROTO_DIRS += $(MANGLED_DIR) $(PROTO_DIR) $(@D) $(COMPONENT_DIR) $(COMPONENT_SRC)

MANIFEST_BASE =		$(BUILD_DIR)/manifest-$(MACH)

SAMPLE_MANIFEST_DIR = 	$(COMPONENT_DIR)/manifests
SAMPLE_MANIFEST_FILE =	$(SAMPLE_MANIFEST_DIR)/sample-manifest.p5m
GENERIC_MANIFEST_FILE =	$(SAMPLE_MANIFEST_DIR)/generic-manifest.p5m

CANONICAL_MANIFESTS =	$(wildcard *.p5m)
ifneq ($(wildcard $(HISTORY)),)
HISTORICAL_MANIFESTS = $(shell $(NAWK) -v FUNCTION=name -f $(GENERATE_HISTORY) < $(HISTORY))
endif

define ips-print-depend-require-rule
$(shell cat $(1) $(WS_TOP)/transforms/print-depend-require |\
	$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 |\
	sed -e '/^$$/d' -e '/^#.*$$/d' | $(SORT) -u)
endef

define ips-print-depend-require-versioned-rule
$(foreach v,$($(1)V_VALUES),\
	$(shell cat $(2) $(WS_TOP)/transforms/print-pkgs |\
	$(PKGMOGRIFY) $(PKG_OPTIONS) -D $($(1)V_FMRI_VERSION)=$(v) /dev/fd/0 |\
	sed -e '/^$$/d' -e '/^#.*$$/d' | $(SORT) -u))
endef

define ips-print-depend-require-type-rule
$(foreach m,$($(1)_MANIFESTS),$(call ips-print-depend-require-versioned-rule,$(1),$(m)))
endef

define ips-print-names-rule
$(shell cat $(1) $(WS_TOP)/transforms/print-pkgs |\
	$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 |\
	sed -e '/^$$/d' -e '/^#.*$$/d' | $(SORT) -u)
endef

define ips-print-names-versioned-rule
$(foreach v,$($(1)V_VALUES),\
	$(shell cat $(2) $(WS_TOP)/transforms/print-pkgs |\
	$(PKGMOGRIFY) $(PKG_OPTIONS) -D $($(1)V_FMRI_VERSION)=$(v) /dev/fd/0 |\
	sed -e '/^$$/d' -e '/^#.*$$/d' | $(SORT) -u))
endef

#
# In addition to the concrete per-version packages, we also need to emit the
# name of the generic package which pulls in the concrete packages.
#
define ips-print-names-generic-rule
$(shell cat $(2) $(WS_TOP)/transforms/mkgeneric $(BUILD_DIR)/mkgeneric-python \
    $(WS_TOP)/transforms/print-pkgs |\
    $(PKGMOGRIFY) $(PKG_OPTIONS) -D $($(1)V_FMRI_VERSION)=\#\#\# /dev/fd/0 |\
    sed -e '/^$$/d' -e '/^#.*$$/d' | $(SORT) -u)
endef

define ips-print-names-type-rule
$(foreach m,$($(1)_MANIFESTS),\
    $(call ips-print-names-versioned-rule,$(1),$(m))\
    $(call ips-print-names-generic-rule,$(1),$(m))\
)
endef

VERSIONED_MANIFEST_TYPES =
UNVERSIONED_MANIFESTS = $(filter-out %-GENFRAG.p5m, $(CANONICAL_MANIFESTS))
GENERATE_GENERIC_TRANSFORMS=

# Look for manifests which need to be duplicated for each version of python.
ifeq ($(findstring -PYVER,$(CANONICAL_MANIFESTS)),-PYVER)
VERSIONED_MANIFEST_TYPES+= PY
NOPY_MANIFESTS = $(filter-out %-PYVER.p5m,$(UNVERSIONED_MANIFESTS))
PY_MANIFESTS = $(filter %-PYVER.p5m,$(CANONICAL_MANIFESTS))
PYV_VALUES = $(shell echo $(PYTHON_VERSIONS) | tr -d .)
PYV_FMRI_VERSION = PYV
PYV_MANIFESTS = $(foreach v,$(PYV_VALUES),$(shell echo $(PY_MANIFESTS) | sed -e 's/-PYVER.p5m/-$(v).p5m/g'))
PYNV_MANIFESTS = $(shell echo $(PY_MANIFESTS) | sed -e 's/-PYVER//')
MKGENERIC_SCRIPTS += $(BUILD_DIR)/mkgeneric-python
else
NOPY_MANIFESTS = $(UNVERSIONED_MANIFESTS)
endif

# PYTHON_PYV_VALUES contains list of all possible PYV values we could encounter:
# - for all currently supported python versions (from PYTHON_VERSIONS)
# - for all python versions we are currently obsoleting (from PYTHON_VERSIONS_OBSOLETING)
# - the $(PYV) string itself
PYTHON_PYV_VALUES = $(shell echo $(PYTHON_VERSIONS) $(PYTHON_VERSIONS_OBSOLETING) | tr -d .) $$(PYV)
# Convert REQUIRED_PACKAGES to PYTHON_REQUIRED_PACKAGES for runtime/python
REQUIRED_PACKAGES_TRANSFORM += $(foreach v,$(PYTHON_PYV_VALUES), -e 's|^\(.*runtime/python\)-$(v)$$|PYTHON_\1|g')
# Convert REQUIRED_PACKAGES to PYTHON_REQUIRED_PACKAGES for library/python/*
REQUIRED_PACKAGES_TRANSFORM += $(foreach v,$(PYTHON_PYV_VALUES), -e 's|^\(.*library/python/.*\)-$(v)$$|PYTHON_\1|g')

# Look for manifests which need to be duplicated for each version of perl.
ifeq ($(findstring -PERLVER,$(UNVERSIONED_MANIFESTS)),-PERLVER)
VERSIONED_MANIFEST_TYPES+= PERL
NOPERL_MANIFESTS = $(filter-out %-PERLVER.p5m,$(NOPY_MANIFESTS))
PERL_MANIFESTS = $(filter %-PERLVER.p5m,$(UNVERSIONED_MANIFESTS))
PERLV_VALUES = $(shell echo $(PERL_VERSIONS) | tr -d .)
PERLV_FMRI_VERSION = PLV
PERLV_MANIFESTS = $(foreach v,$(PERLV_VALUES),$(shell echo $(PERL_MANIFESTS) | sed -e 's/-PERLVER.p5m/-$(v).p5m/g'))
PERLNV_MANIFESTS = $(shell echo $(PERL_MANIFESTS) | sed -e 's/-PERLVER//')
else
NOPERL_MANIFESTS = $(NOPY_MANIFESTS)
endif

# PERL_PLV_VALUES contains list of all possible PLV values we could encounter:
# - for all currently supported perl versions (from PERL_VERSIONS)
# - for all perl versions we are currently obsoleting (from PERL_VERSIONS_OBSOLETING)
# - the $(PLV) string itself
PERL_PLV_VALUES = $(shell echo $(PERL_VERSIONS) $(PERL_VERSIONS_OBSOLETING) | tr -d .) $$(PLV)
# Convert REQUIRED_PACKAGES to PERL_REQUIRED_PACKAGES for runtime/perl
REQUIRED_PACKAGES_TRANSFORM += $(foreach v,$(PERL_PLV_VALUES), -e 's|^\(.*runtime/perl\)-$(v)$$|PERL_\1|g')
# Convert REQUIRED_PACKAGES to PERL_REQUIRED_PACKAGES for library/perl-5/*
REQUIRED_PACKAGES_TRANSFORM += $(foreach v,$(PERL_PLV_VALUES), -e 's|^\(.*library/perl-5/.*\)-$(v)$$|PERL_\1|g')

# Look for manifests which need to be duplicated for each version of ruby.
# NOPERL_MANIFESTS represents the manifests that are not Python or
# Perl manifests.  Extract the Ruby Manifests from NOPERL_MANIFESTS.
# Any remaining manifests are stored in NONRUBY_MANIFESTS
ifeq ($(findstring -RUBYVER,$(NOPERL_MANIFESTS)),-RUBYVER)
VERSIONED_MANIFEST_TYPES+= RUBY
NORUBY_MANIFESTS = $(filter-out %-RUBYVER.p5m,$(NOPERL_MANIFESTS))
RUBY_MANIFESTS = $(filter %-RUBYVER.p5m,$(NOPERL_MANIFESTS))
RUBYV_VALUES = $(RUBY_VERSIONS)
RUBYV_FMRI_VERSION = RUBYV
RUBYV_MANIFESTS = $(foreach v,$(RUBY_VERSIONS),\
                      $(shell echo $(RUBY_MANIFESTS) |\
                      sed -e 's/-RUBYVER.p5m/-$(shell echo $(v) |\
                      cut -d. -f1,2 | tr -d .).p5m/g'))
RUBYNV_MANIFESTS = $(shell echo $(RUBY_MANIFESTS) | sed -e 's/-RUBYVER//')
else
NORUBY_MANIFESTS = $(NOPERL_MANIFESTS)
endif

NONVER_MANIFESTS = $(NORUBY_MANIFESTS)

VERSIONED_MANIFESTS = \
	$(PYV_MANIFESTS) $(PYNV_MANIFESTS) \
	$(PERLV_MANIFESTS) $(PERLNV_MANIFESTS) \
	$(RUBYV_MANIFESTS) $(RUBYNV_MANIFESTS) \
	$(NORUBY_MANIFESTS) $(HISTORICAL_MANIFESTS)

GENERATED =		$(MANIFEST_BASE)-generated
COMBINED =		$(MANIFEST_BASE)-combined
MANIFESTS =		$(VERSIONED_MANIFESTS:%=$(MANIFEST_BASE)-%)


DEPENDED=$(VERSIONED_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.depend)
RESOLVED=$(VERSIONED_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.depend.res)
PRE_PUBLISHED=$(RESOLVED:%.depend.res=%.pre-published)
PUBLISHED=$(RESOLVED:%.depend.res=%.published)

COPYRIGHT_FILE ?=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).copyright
IPS_COMPONENT_VERSION ?=	$(COMPONENT_VERSION)

.DEFAULT:		publish

.SECONDARY:

# allow publishing to be overridden, such as when
# a package is for one architecture only.
PRE_PUBLISH_STAMP ?= $(BUILD_DIR)/.pre-published-$(MACH)
PUBLISH_STAMP ?= $(BUILD_DIR)/.published-$(MACH)

# Do all that is needed to ensure the package is consistent for publishing,
# except actually pushing to a repo, separately from the push to the repo.
pre-publish:	build install $(PRE_PUBLISH_STAMP)
publish:		pre-publish update-metadata $(PUBLISH_STAMP)

sample-manifest:	$(GENERATED).p5m

$(GENERATED).p5m:	install $(GENERATE_EXTRA_DEPS)
	[ ! -d $(SAMPLE_MANIFEST_DIR) ] && $(MKDIR) $(SAMPLE_MANIFEST_DIR) || true
	$(PKGSEND) generate $(PKG_HARDLINKS:%=--target %) $(PROTO_DIR) | \
	$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 $(GENERATE_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' \
		-e '/\.la$$/d' | \
		$(PKGFMT) | \
		uniq | \
		cat $(METADATA_TEMPLATE) - $(GENERATE_EXTRA_CMD) | \
		$(TEE) $@ $(SAMPLE_MANIFEST_FILE) >/dev/null
	if [ "$(GENERATE_GENERIC_TRANSFORMS)X" != "X" ]; \
	then sed $(GENERATE_GENERIC_TRANSFORMS) $(SAMPLE_MANIFEST_FILE) \
		| gawk '!seen[$$0]++' > $(GENERIC_MANIFEST_FILE); fi;

# copy the canonical manifest(s) to the build tree
$(MANIFEST_BASE)-%.generate:	%.p5m canonical-manifests
	cat $(METADATA_TEMPLATE) $< >$@

# The text of a transform that will emit a dependency conditional on the
# presence of a particular version of a runtime, which will then draw in the
# runtime-version-specific version of the package we're operating on.  $(1) is
# the name of the runtime package, and $(2) is the version suffix.
mkgeneric = \
	echo "<transform set name=pkg.fmri value=(?:pkg:/)?(.+)-\#\#\#@(.*)" \
		"-> emit depend nodrop=true type=conditional" \
		"predicate=$(1)-$(2) fmri=%<1>-$(2)@%<2>>" >> $@;

mkgenericdep = \
	( echo -n "<transform set name=pkg.fmri value=(?:pkg:/)?(.+)-\#\#\#@(.*)" \
		"-> emit depend nodrop=true type=require-any " ;  \
        for i in $(2); do echo -n "fmri=%<1>-$$i@%<2> " ; done ; \
        echo ">" ) >> $@

# Define and execute a macro that generates a rule to create a manifest for a
# python module specific to a particular version of the python runtime.
define python-manifest-rule
$(MANIFEST_BASE)-%-$(2).mogrified: PKG_MACROS += PYTHON_$(1)_ONLY= PYTHON_$(1)_EXCL=\#

ifneq ($(filter $(1),$(PYTHON_64_ONLY_VERSIONS)),)
$(MANIFEST_BASE)-%-$(2).mogrified: PKG_MACROS += PYTHON_32_ONLY=\#
endif

$(MANIFEST_BASE)-%-$(2).p5m: %-PYVER.p5m
	$(PKGMOGRIFY) -D PYVER=$(1) $(MANIFEST_LIMITING_VARS) -D PYV=$(2)  $$< > $$@
endef
$(foreach ver,$(PYTHON_VERSIONS),$(eval $(call python-manifest-rule,$(ver),$(shell echo $(ver)|tr -d .))))

ifeq ($(strip $(SINGLE_PYTHON_VERSION)),yes)
PKG_MACROS += PYVER=$(PYTHON_VERSION)
PKG_MACROS += PYV=$(shell echo $(PYTHON_VERSION)|tr -d .)
endif

# A rule to create a helper transform package for python, that will insert the
# appropriate conditional dependencies into a python library's
# runtime-version-generic package to pull in the version-specific bits when the
# corresponding version of python is on the system.
$(BUILD_DIR)/mkgeneric-python: $(WS_TOP)/make-rules/shared-macros.mk $(MAKEFILE_PREREQ) $(BUILD_DIR)
	$(RM) $@
	$(foreach ver,$(shell echo $(PYTHON_VERSIONS) | tr -d .), \
		$(call mkgeneric,runtime/python,$(ver)))
	$(call mkgenericdep,runtime/python,$(shell echo $(PYTHON_VERSIONS) | tr -d .))

# Build Python version-wrapping manifests from the generic version.
$(MANIFEST_BASE)-%.p5m: %-PYVER.p5m $(BUILD_DIR)/mkgeneric-python
	$(PKGMOGRIFY) -D PYV=### $(BUILD_DIR)/mkgeneric-python \
		$(WS_TOP)/transforms/mkgeneric $< > $@
	if [ -f $*-GENFRAG.p5m ]; then cat $*-GENFRAG.p5m >> $@; fi

# Define and execute a macro that generates a rule to create a manifest for a
# perl module specific to a particular version of the perl runtime.
define perl-manifest-rule
$(MANIFEST_BASE)-%-$(shell echo $(1) | tr -d .).p5m: %-PERLVER.p5m
	$(PKGMOGRIFY) -D PERLVER=$(1) -D PLV=$$(shell echo $(1) | tr -d .) \
		-D PERL_ARCH=$$(call PERL_ARCH_FUNC,$$(PERL.$(1))) $$< > $$@
endef
$(foreach ver,$(PERL_VERSIONS),$(eval $(call perl-manifest-rule,$(ver))))

ifeq ($(strip $(SINGLE_PERL_VERSION)),yes)
PKG_MACROS += PERLVER=$(PERL_VERSION)
PKG_MACROS += PLV=$(shell echo $(PERL_VERSION)|tr -d .)
endif

# A rule to create a helper transform package for perl, that will insert the
# appropriate conditional dependencies into a perl library's
# runtime-version-generic package to pull in the version-specific bits when the
# corresponding version of perl is on the system.
$(BUILD_DIR)/mkgeneric-perl: $(WS_TOP)/make-rules/shared-macros.mk $(MAKEFILE_PREREQ)
	$(RM) $@
	$(foreach ver,$(shell echo $(PERL_VERSIONS) | tr -d .), \
		$(call mkgeneric,runtime/perl,$(ver)))
	$(call mkgenericdep,runtime/perl,$(shell echo $(PERL_VERSIONS) | tr -d .))

# Build Perl version-wrapping manifests from the generic version.
$(MANIFEST_BASE)-%.p5m: %-PERLVER.p5m $(BUILD_DIR)/mkgeneric-perl
	$(PKGMOGRIFY) -D PLV=### $(BUILD_DIR)/mkgeneric-perl \
		$(WS_TOP)/transforms/mkgeneric $< > $@
	if [ -f $*-GENFRAG.p5m ]; then cat $*-GENFRAG.p5m >> $@; fi

# Rule to generate historical manifests from the $(HISTORY) file.
define history-manifest-rule
$(MANIFEST_BASE)-$(1): $(HISTORY) $(BUILD_DIR)
	$(NAWK) -v TARGET=$(1) -v FUNCTION=manifest -f $(GENERATE_HISTORY) < \
	    $(HISTORY) > $$@
endef
$(foreach mfst,$(HISTORICAL_MANIFESTS),$(eval $(call history-manifest-rule,$(mfst))))

# Define and execute a macro that generates a rule to create a manifest for a
# ruby module specific to a particular version of the ruby runtime.
# Creates build/manifest-*-modulename-##.p5m file where ## is replaced with
# the version number.
define ruby-manifest-rule
$(MANIFEST_BASE)-%-$(shell echo $(1) | tr -d .).mogrified: \
        PKG_MACROS += RUBY_VERSION=$(1) RUBY_LIB_VERSION=$(2) \
            RUBYV=$(subst .,,$(1))

$(MANIFEST_BASE)-%-$(shell echo $(1) | tr -d .).p5m: %-RUBYVER.p5m
	if [ -f $$*-$(shell echo $(1) | tr -d .)GENFRAG.p5m ]; then \
	        cat $$*-$(shell echo $(1) | tr -d .)GENFRAG.p5m >> $$@; \
	fi
	$(PKGMOGRIFY) -D RUBY_VERSION=$(1) -D RUBY_LIB_VERSION=$(2) \
	    -D RUBYV=$(shell echo $(1) | tr -d .) $$< > $$@
endef
$(foreach ver,$(RUBY_VERSIONS),\
        $(eval $(call ruby-manifest-rule,$(shell echo $(ver) | \
            cut -d. -f1,2),$(ver))))

# A rule to create a helper transform package for ruby, that will insert the
# appropriate conditional dependencies into a ruby library's
# runtime-version-generic package to pull in the version-specific bits when the
# corresponding version of ruby is on the system.
$(BUILD_DIR)/mkgeneric-ruby: $(WS_TOP)/make-rules/shared-macros.mk $(MAKEFILE_PREREQ)
	$(RM) $@
	$(foreach ver,$(RUBY_VERSIONS),\
	        $(call mkgeneric,runtime/ruby,$(shell echo $(ver) | \
	            cut -d. -f1,2 | tr -d .)))
	$(call mkgenericdep,runtime/ruby,$(shell echo $(RUBY_VERSIONS) | cut -d. -f1,2 | tr -d .))

# Build Ruby version-wrapping manifests from the generic version.
# Creates build/manifest-*-modulename.p5m file.
#
$(MANIFEST_BASE)-%.p5m: %-RUBYVER.p5m $(BUILD_DIR)/mkgeneric-ruby
	$(PKGMOGRIFY) -D RUBYV=### $(BUILD_DIR)/mkgeneric-ruby \
	        $(WS_TOP)/transforms/mkgeneric $< > $@
	if [ -f $*-GENFRAG.p5m ]; then cat $*-GENFRAG.p5m >> $@; fi

ifeq   ($(strip $(COMPONENT_AUTOGEN_MANIFEST)),yes)
# auto-generate file/directory list
$(MANIFEST_BASE)-%.generated:	%.p5m $(BUILD_DIR)
	(cat $(METADATA_TEMPLATE); \
	$(PKGSEND) generate $(PKG_HARDLINKS:%=--target %) $(PROTO_DIR)) | \
	$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 $(AUTOGEN_MANIFEST_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | $(PKGFMT) | \
		cat $< - >$@

# mogrify non-parameterized manifests
$(MANIFEST_BASE)-%.mogrified:	%.generated $(MAKEFILE_PREREQ)
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@

# mogrify parameterized manifests
$(MANIFEST_BASE)-%.mogrified:	$(MANIFEST_BASE)-%.generated $(MAKEFILE_PREREQ)
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@
else
# mogrify non-parameterized manifests
$(MANIFEST_BASE)-%.mogrified:	%.p5m $(BUILD_DIR) $(MAKEFILE_PREREQ)
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@

# mogrify parameterized manifests
$(MANIFEST_BASE)-%.mogrified:	$(MANIFEST_BASE)-%.p5m $(BUILD_DIR) $(MAKEFILE_PREREQ)
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@
endif

# mangle the file contents
$(BUILD_DIR) $(MANGLED_DIR):
	$(MKDIR) $@

PKGMANGLE_OPTIONS = -D $(MANGLED_DIR) $(PKG_PROTO_DIRS:%=-d %)
$(MANIFEST_BASE)-%.mangled:	$(MANIFEST_BASE)-%.mogrified $(MANGLED_DIR)
	$(PKGMANGLE) $(PKGMANGLE_OPTIONS) -m $< >$@

# generate dependencies
PKGDEPEND_GENERATE_OPTIONS = -m $(PKG_PROTO_DIRS:%=-d %)
$(MANIFEST_BASE)-%.depend:	$(MANIFEST_BASE)-%.mangled
	$(PKGDEPEND) generate $(PKGDEPEND_GENERATE_OPTIONS) $< >$@

# pkgdepend resolve builds a map of all installed packages by default.  This
# makes dependency resolution particularly slow.  We can dramatically improve
# performance here by creating a file with a list of packages that we know
# are needed, dramatically reducing the overhead involved in creating and
# searching this map.
#
# Generate a resolve.deps file from the dependencies in the Makefile and
# fragments that it uses.
RESOLVE_DEPS=$(BUILD_DIR)/resolve.deps

$(RESOLVE_DEPS):	Makefile $(BUILD_DIR) $(DEPENDED)
	@(for pkg in $(REQUIRED_PACKAGES:%=/%) ; do \
	    echo $${pkg} ; \
	done ; \
	$(PKGMOGRIFY) $(WS_TRANSFORMS)/PRINT_COMPONENT_FMRIS $(DEPENDED) | \
		$(GSED) -e '/^[\t ]*$$/d' -e '/^#/d' ;) | $(SORT) -u >$@

$(BUILD_DIR)/runtime-perl.p5m: $(WS_TOOLS)/runtime-perl.p5m
	$(CP) $< $@

# resolve the dependencies all at once
$(BUILD_DIR)/.resolved-$(MACH):	$(DEPENDED) $(RESOLVE_DEPS) $(BUILD_DIR)/runtime-perl.p5m
	$(PKGDEPEND) resolve $(RESOLVE_DEPS:%=-e %) -m $(DEPENDED) $(BUILD_DIR)/runtime-perl.p5m
	$(TOUCH) $@

# generate list of sed rules to filter out component's own packages from
# REQUIRED_PACKAGES list
$(BUILD_DIR)/filter-own-pkgs: $(DEPENDED)
	$(PKGMOGRIFY) $(WS_TRANSFORMS)/PRINT_COMPONENT_FMRIS $(DEPENDED) \
		| $(GSED) -e '/^[\t ]*$$/d' -e '/^#/d' -e 's/^\///g' -e 's/\//\\\//g' \
		| $(SORT) -u \
		| $(GSED) -e 's/^\(.*\)$$/\/^REQUIRED_PACKAGES += \1$$\/d/g' >$@

# Set REQUIRED_PACKAGES macro substitution rules
REQUIRED_PACKAGES_TRANSFORM += $(foreach p,$(REQUIRED_PACKAGES_SUBST), -e 's|$($(p))|$$($(p))|')

#
# Generate a set of REQUIRED_PACKAGES based on what is needed for pkgdepend to
# resolve properly.  Automatically update the list in your Makefile for the
# truly lazy among us.  This is only a piece of the REQUIRED_PACKAGES puzzle.
# You must still include packages for tools you build and test with.
#
REQUIRED_PACKAGES::     $(RESOLVED) $(REQUIRED_PACKAGES_RESOLVED) $(BUILD_DIR)/filter-own-pkgs $(REQUIRED_PACKAGES_EXTRA_DEPS)
	$(GMAKE) RESOLVE_DEPS= $(BUILD_DIR)/.resolved-$(MACH)
	@$(GSED) -i -e '/^# Auto-generated dependencies$$/,$$d' Makefile
	@echo "# Auto-generated dependencies" >>Makefile
	$(PKGMOGRIFY) $(WS_TRANSFORMS)/$@ $(RESOLVED) $(REQUIRED_PACKAGES_RESOLVED) \
		| $(GSED) -e '/^[\t ]*$$/d' -e '/^#/d' \
		| tr '|' '\n' \
		| $(GSED) -e 's,pkg:/,,g' -e 's/@.*$$//g' \
			-f $(BUILD_DIR)/filter-own-pkgs \
			$(REQUIRED_PACKAGES_TRANSFORM) \
		| $(SORT) -u >>Makefile
	@echo "*** Please edit your Makefile and verify the new or updated content at the end ***"


# lint the manifests all at once
$(BUILD_DIR)/.linted-$(MACH):	$(BUILD_DIR)/.resolved-$(MACH)
	@echo "VALIDATING MANIFEST CONTENT: $(RESOLVED)"
	$(ENV) PYTHONPATH=$(WS_TOOLS)/python PROTO_PATH="$(PKG_PROTO_DIRS)" $(COMPONENT_PKGLINT_ENV)\
		$(PKGLINT) $(CANONICAL_REPO:%=-c $(WS_LINT_CACHE)) \
			-f $(WS_TOOLS)/pkglintrc $(RESOLVED)
	$(TOUCH) $@

lintme: FRC
	@echo "VALIDATING MANIFEST CONTENT: $(RESOLVED)"
	$(ENV) PYTHONPATH=$(WS_TOOLS)/python PROTO_PATH="$(PKG_PROTO_DIRS)" $(COMPONENT_PKGLINT_ENV)\
		$(PKGLINT) $(CANONICAL_REPO:%=-c $(WS_LINT_CACHE)) \
			-f $(WS_TOOLS)/pkglintrc $(RESOLVED)

FRC:


# published
PKGSEND_PUBLISH_OPTIONS = -s $(WS_REPO) publish --fmri-in-manifest
PKGSEND_PUBLISH_OPTIONS += $(PKG_PROTO_DIRS:%=-d %)
PKGSEND_PUBLISH_OPTIONS += -T \*.py

# Do all the hard work that is needed to ensure the package is consistent
# and ready for publishing, except actually pushing bits to a repository
$(MANIFEST_BASE)-%.pre-published:	$(MANIFEST_BASE)-%.depend.res $(BUILD_DIR)/.linted-$(MACH)
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(FINAL_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@
	@echo "NEW PACKAGE CONTENTS ARE LOCALLY VALIDATED AND READY TO GO"

# Push to the repo
$(MANIFEST_BASE)-%.published:	$(MANIFEST_BASE)-%.pre-published
	$(PKGSEND) $(PKGSEND_PUBLISH_OPTIONS) $<
	$(PKGFMT) <$< >$@

$(BUILD_DIR)/.pre-published-$(MACH):	$(PRE_PUBLISHED)
	$(TOUCH) $@

$(BUILD_DIR)/.published-$(MACH):	$(PUBLISHED)
	$(TOUCH) $@

print-depend-require:	canonical-manifests
	@echo $(call ips-print-depend-require-rule,$(NONVER_MANIFESTS)) \
		$(foreach t,$(VERSIONED_MANIFEST_TYPES),$(call ips-print-depend-require-type-rule,$(t))) | tr ' ' '\n'

print-package-names:	canonical-manifests $(MKGENERIC_SCRIPTS)
	@echo $(call ips-print-names-rule,$(NONVER_MANIFESTS)) \
	    $(foreach t,$(VERSIONED_MANIFEST_TYPES),\
	        $(call ips-print-names-type-rule,$(t))) \
	    | tr ' ' '\n'

print-package-paths:	canonical-manifests
	@cat $(CANONICAL_MANIFESTS) $(WS_TOP)/transforms/print-paths | \
		$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | \
		$(SORT) -u

install-packages:	publish
	@if [ $(IS_GLOBAL_ZONE) = 0 -o x$(ROOT) != x ]; then \
	    cat $(VERSIONED_MANIFESTS) $(WS_TOP)/transforms/print-paths | \
	    $(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
	    sed -e '/^$$/d' -e '/^#.*$$/d' -e 's;/;;' | \
	    $(SORT) -u | \
	    (cd $(PROTO_DIR) ; pfexec /bin/cpio -dump $(ROOT)) ; \
	 else ; \
	    echo "unsafe to install package(s) automatically" ; \
	 fi

$(RESOLVED):	install

canonical-manifests:	$(CANONICAL_MANIFESTS) Makefile $(PATCHES)
ifeq	($(strip $(CANONICAL_MANIFESTS)),)
	# If there were no canonical manifests in the workspace, nothing will
	# be published and we should fail.  A sample manifest can be generated
	# with
	#   $ gmake sample-manifest
	# Once created, it will need to be reviewed, edited, and added to the
	# workspace.
	$(error Missing canonical manifest(s))
endif

# Component variables are expanded directly to PKG_OPTIONS instead of via
# PKG_MACROS since the values may contain whitespace.
mkdefine = -D $(1)="$$(strip $(2))"

# Expand PKG_VARS into defines via PKG_OPTIONS.
$(foreach var, $(PKG_VARS), \
    $(eval PKG_OPTIONS += $(call mkdefine,$(var),$$($(var)))) \
)

# This converts required paths to containing package names for be able to
# properly setup the build environment for a component.
required-pkgs.mk:	Makefile
	@echo "generating $@ from Makefile REQUIRED_* data"
	@pkg search -H -l '<$(DEPENDS:%=% OR) /bin/true>' \
		| sed -e 's/pkg:\/\(.*\)@.*/REQUIRED_PKGS += \1/g' >$@

pre-prep:	required-pkgs.mk


CLEAN_PATHS +=	required-pkgs.mk
CLEAN_PATHS +=	$(BUILD_DIR)/mkgeneric-perl
CLEAN_PATHS +=	$(BUILD_DIR)/mkgeneric-python
CLEAN_PATHS +=	$(BUILD_DIR)/mkgeneric-ruby
