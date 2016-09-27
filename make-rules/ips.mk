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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#

#
# Rules and Macros for generating an IPS package manifest and publishing an
# IPS package to a pkg depot.
#
# To use these rules, include $(WS_MAKE_RULES)/ips.mk in your Makefile
# and define an "install" target appropriate to building your component.
# Ex:
#
#	install:	$(BUILD_DIR)/build/$(MACH32)/.installed \
#	 		$(BUILD_DIR)/build/$(MACH64)/.installed
#
# This set of rules makes the "publish" target the default target for make(1)
#

PKGDEPEND =	/usr/bin/pkgdepend
PKGFMT =	/usr/bin/pkgfmt
PKGMANGLE =	$(WS_TOOLS)/userland-mangler

GENERATE_HISTORY= $(WS_TOOLS)/generate-history
HISTORY=	history

# pkgfmt has an odd behavior at present where -c means "check validity
# against any format" whereas -d means "diffs against latest format" and
# no arguments means "update to latest format".  Thus, 'pkgfmt -c' can
# run clean on a v1 manifest that actually needs to be updated.  So we
# use the explicit format version argument below.  If this behavior is
# changed, then the -f argument below can be dropped.
PKGFMT_CHECK_ARGS =	-c -fv2

WS_TRANSFORMS =	$(WS_TOP)/transforms

# Package headers should all pretty much follow the same format
METADATA_TEMPLATE =		$(WS_TOP)/transforms/manifest-metadata-template
COPYRIGHT_TEMPLATE =		$(WS_TOP)/transforms/copyright-template

# order is important
GENERATE_TRANSFORMS +=		$(WS_TOP)/transforms/generate-cleanup

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop

COMPARISON_TRANSFORMS +=	$(WS_TOP)/transforms/comparison-cleanup
COMPARISON_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)

LICENSE_TRANSFORMS =		$(WS_TOP)/transforms/license-changes

# order is important
PUBLISH_TRANSFORMS +=	$(LICENSE_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/variant-cleanup
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/autopyc
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/defaults
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/actuators
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/depends
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/devel
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/docs
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/locale
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/standard-python-libraries
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/python-rename
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/python-3-groups
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/python-3-soabi
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/python-3-no-32bit
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/ruby-tests
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/puppet
PUBLISH_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/incorporate
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/publish-cleanup

# If we are building "evaluation" packages, add the evaluation information
# action so that the package(s) display the terms and require acceptance
# to install.
ifeq ($(BUILD_TYPE),evaluation)
PUBLISH_TRANSFORMS += $(WS_TOP)/transforms/evaluation
endif

# For items defined as variables or that may contain whitespace, add
# them to a list to be expanded into PKG_OPTIONS later.
PKG_VARS += ARC_CASE TPNO
PKG_VARS += BUILD_VERSION OS_VERSION SOLARIS_VERSION PKG_SOLARIS_VERSION
PKG_VARS += CONSOLIDATION CONSOLIDATION_CHANGESET CONSOLIDATION_REPOSITORY_URL
PKG_VARS += COMPONENT_VERSION IPS_COMPONENT_VERSION HUMAN_VERSION
PKG_VARS += COMPONENT_ARCHIVE_URL COMPONENT_PROJECT_URL COMPONENT_NAME
PKG_VARS += HG_REPO HG_REV HG_URL
PKG_VARS += GIT_COMMIT_ID GIT_REPO GIT_TAG
PKG_VARS += MACH MACH32 MACH64
PKG_VARS += PUBLISHER PUBLISHER_LOCALIZABLE
PKG_VARS += SOLARIS_11_ONLY SOLARIS_12_ONLY

# Include TPNO_* Makefile variables in PKG_VARS.
$(foreach macro, $(filter TPNO_%, $(.VARIABLES)), \
    $(eval PKG_VARS += $(macro)) \
)

# For items that need special definition, add them to PKG_MACROS.
# IPS_COMPONENT_VERSION suitable for use in regular expressions.
PKG_MACROS +=		IPS_COMPONENT_RE_VERSION=$(subst .,\\.,$(IPS_COMPONENT_VERSION))
# COMPONENT_VERSION suitable for use in regular expressions.
PKG_MACROS +=		COMPONENT_RE_VERSION=$(subst .,\\.,$(COMPONENT_VERSION))

PKG_MACROS +=		PYTHON_2.7_ONLY=\#
PKG_MACROS +=		PYTHON_3.4_ONLY=\#
PKG_MACROS +=		PYTHON_3.5_ONLY=\#

# Convenience macros for quoting in manifests; necessary because pkgfmt will
# drop literal quotes in attribute values if they do not contain whitespace
# since the action parsing in pkg will drop them during action stringification.
PKG_MACROS +=		SQ=\'
PKG_MACROS +=		DQ=\"
PKG_MACROS +=		Q=\"

PKG_OPTIONS +=		$(PKG_MACROS:%=-D %)

MANGLED_DIR =	$(PROTO_DIR)/mangled

# We use += below so anyone wishing to put other directories at the beginning
# of the list can do so, by setting PKG_PROTO_DIRS before including this file.
# So don't change += to = here or components that use this will break.
PKG_PROTO_DIRS += $(MANGLED_DIR) $(PROTO_DIR) $(@D) $(COMPONENT_DIR) $(COMPONENT_SRC) $(WS_LICENSES)

MANIFEST_BASE =		$(BUILD_DIR)/manifest-$(MACH)

CANONICAL_MANIFESTS =	$(wildcard *.p5m)
ifneq ($(wildcard $(HISTORY)),)
HISTORICAL_MANIFESTS = $(shell $(NAWK) -v FUNCTION=name -f $(GENERATE_HISTORY) < $(HISTORY))
endif

# Look for manifests which need to be duplicated for each version of python.
ifeq ($(findstring -PYVER,$(CANONICAL_MANIFESTS)),-PYVER)
UNVERSIONED_MANIFESTS = $(filter-out %GENFRAG.p5m,$(filter-out %-PYVER.p5m,$(CANONICAL_MANIFESTS)))
PY_MANIFESTS = $(filter %-PYVER.p5m,$(CANONICAL_MANIFESTS))
PYV_MANIFESTS = $(foreach v,$(shell echo $(PYTHON_VERSIONS) | tr -d .),$(shell echo $(PY_MANIFESTS) | sed -e 's/-PYVER.p5m/-$(v).p5m/g'))
PYNV_MANIFESTS = $(shell echo $(PY_MANIFESTS) | sed -e 's/-PYVER//')
else
UNVERSIONED_MANIFESTS = $(CANONICAL_MANIFESTS)
endif

# Look for manifests which need to be duplicated for each version of perl.
ifeq ($(findstring -PERLVER,$(UNVERSIONED_MANIFESTS)),-PERLVER)
NOPERL_MANIFESTS = $(filter-out %GENFRAG.p5m,$(filter-out %-PERLVER.p5m,$(UNVERSIONED_MANIFESTS)))
PERL_MANIFESTS = $(filter %-PERLVER.p5m,$(UNVERSIONED_MANIFESTS))
PERLV_MANIFESTS = $(foreach v,$(shell echo $(PERL_VERSIONS) | tr -d .),$(shell echo $(PERL_MANIFESTS) | sed -e 's/-PERLVER.p5m/-$(v).p5m/g'))
PERLNV_MANIFESTS = $(shell echo $(PERL_MANIFESTS) | sed -e 's/-PERLVER//')
else
NOPERL_MANIFESTS = $(UNVERSIONED_MANIFESTS)
endif

# Look for manifests which need to be duplicated for each version of ruby.
# NOPERL_MANIFESTS represents the manifests that are not Python or
# Perl manifests.  Extract the Ruby Manifests from NOPERL_MANIFESTS.
# Any remaining manifests are stored in NONRUBY_MANIFESTS
ifeq ($(findstring -RUBYVER,$(NOPERL_MANIFESTS)),-RUBYVER)
NORUBY_MANIFESTS = $(filter-out %GENFRAG.p5m,\
		   $(filter-out %-RUBYVER.p5m,$(NOPERL_MANIFESTS)))
RUBY_MANIFESTS = $(filter %-RUBYVER.p5m,$(NOPERL_MANIFESTS))
RUBYV_MANIFESTS = $(foreach v,$(shell echo $(RUBY_VERSIONS)),\
                      $(shell echo $(RUBY_MANIFESTS) |\
                      sed -e 's/-RUBYVER.p5m/-$(shell echo $(v) |\
                      cut -d. -f1,2 | tr -d .).p5m/g'))
RUBYNV_MANIFESTS = $(shell echo $(RUBY_MANIFESTS) | sed -e 's/-RUBYVER//')
else
NORUBY_MANIFESTS = $(NOPERL_MANIFESTS)
endif

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
PUBLISHED=$(RESOLVED:%.depend.res=%.published)

COPYRIGHT_FILE ?=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).copyright
IPS_COMPONENT_VERSION ?=	$(COMPONENT_VERSION)

.DEFAULT:		publish

.SECONDARY:

# allow publishing to be overridden, such as when
# a package is for one architecture only.
PUBLISH_STAMP ?= $(BUILD_DIR)/.published-$(MACH)

publish:		build install $(PUBLISH_STAMP)

sample-manifest:	$(GENERATED).p5m

$(GENERATED).p5m:	install
	$(PKGSEND) generate $(PKG_HARDLINKS:%=--target %) $(PROTO_DIR) | \
	$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 $(GENERATE_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | $(PKGFMT) | \
		cat $(METADATA_TEMPLATE) - >$@

# copy the canonical manifest(s) to the build tree
$(MANIFEST_BASE)-%.generate:	%.p5m canonical-manifests
	cat $(METADATA_TEMPLATE) $< >$@

# The text of a transform that will emit a dependency conditional on the
# presence of a particular version of a runtime, which will then draw in the
# runtime-version-specific version of the package we're operating on.  $(1) is
# the name of the runtime package, and $(2) is the version suffix.
mkgeneric = \
	echo "<transform set name=pkg.fmri value=(?:pkg:/)?(.+)-\#\#\#PYV\#\#\#@(.*)" \
		"-> emit depend nodrop=true type=conditional" \
		"predicate=$(1)-$(2) fmri=%<1>-$(2)@%<2>>" >> $@;

# Define and execute a macro that generates a rule to create a manifest for a
# python module specific to a particular version of the python runtime.
# Creates build/manifest-*-modulename-##.p5m file where ## is replaced with
# the version number.
define python-manifest-rule
$(MANIFEST_BASE)-%-$(shell echo $(1) | tr -d .).mogrified: PKG_MACROS += PYTHON_$(1)_ONLY=

$(MANIFEST_BASE)-%-$(shell echo $(1) | tr -d .).p5m: %-PYVER.p5m
	if [ -f $$*-$(shell echo $(1) | tr -d .)GENFRAG.p5m ]; then cat $$*-$(shell echo $(1) | tr -d .)GENFRAG.p5m >> $$@; fi
	$(PKGFMT) $(PKGFMT_CHECK_ARGS) $(CANONICAL_MANIFESTS)
	$(PKGMOGRIFY) -D PYVER=$(1) -D MAYBE_PYVER_SPACE="$(1) " \
		-D MAYBE_SPACE_PYVER=" $(1)" \
		-D SOLARIS_11_ONLY="$(SOLARIS_11_ONLY)" \
		-D PYV=$(shell echo $(1) | tr -d .) $$< > $$@
endef
$(foreach ver,$(PYTHON_VERSIONS),$(eval $(call python-manifest-rule,$(ver))))

# A rule to create a helper transform package for python, that will insert the
# appropriate conditional dependencies into a python library's
# runtime-version-generic package to pull in the version-specific bits when the
# corresponding version of python is on the system.
$(BUILD_DIR)/mkgeneric-python: $(WS_MAKE_RULES)/shared-macros.mk
	$(RM) $@
	$(foreach ver,$(shell echo $(PYTHON_VERSIONS) | tr -d .), \
		$(call mkgeneric,runtime/python,$(ver)))

# Build Python version-wrapping manifests from the generic version.
# Creates build/manifest-*-modulename.p5m file.
# Note that the mkgeneric transform uses the literal string "###PYV###"
# as the place-holder for the Python version (for mkgeneric-python) and
# the Perl version (for mkgeneric-perl below) and the Ruby version (for
# mkgeneric-ruby further below).  The authors did not anticipate that this
# mechanism would be extended beyond Python when they wrote it; something
# more generic like LANGVER might make more sense, but for now we are
# sticking with something known to work.
$(MANIFEST_BASE)-%.p5m: %-PYVER.p5m $(BUILD_DIR)/mkgeneric-python
	$(PKGFMT) $(PKGFMT_CHECK_ARGS) $(CANONICAL_MANIFESTS)
	$(PKGMOGRIFY) -D PYV=###PYV### -D MAYBE_PYVER_SPACE= \
		-D SOLARIS_11_ONLY="$(SOLARIS_11_ONLY)" \
		-D MAYBE_SPACE_PYVER= $(BUILD_DIR)/mkgeneric-python \
		$(WS_TOP)/transforms/mkgeneric $< > $@
	if [ -f $*-GENFRAG.p5m ]; then cat $*-GENFRAG.p5m >> $@; fi

# Define and execute a macro that generates a rule to create a manifest for a
# perl module specific to a particular version of the perl runtime.
define perl-manifest-rule
$(MANIFEST_BASE)-%-$(shell echo $(1) | tr -d .).p5m: %-PERLVER.p5m
	$(PKGFMT) $(PKGFMT_CHECK_ARGS) $$<
	$(PKGMOGRIFY) -D PERLVER=$(1) -D MAYBE_PERLVER_SPACE="$(1) " \
		-D MAYBE_SPACE_PERLVER=" $(1)" \
		-D PLV=$(shell echo $(1) | tr -d .) \
		-D PERL_ARCH=$(call PERL_ARCH_FUNC,$(PERL.$(1))) $$< > $$@
endef
$(foreach ver,$(PERL_VERSIONS),$(eval $(call perl-manifest-rule,$(ver))))

# A rule to create a helper transform package for perl, that will insert the
# appropriate conditional dependencies into a perl library's
# runtime-version-generic package to pull in the version-specific bits when the
# corresponding version of perl is on the system.
$(BUILD_DIR)/mkgeneric-perl: $(WS_MAKE_RULES)/shared-macros.mk
	$(RM) $@
	$(foreach ver,$(shell echo $(PERL_VERSIONS) | tr -d .), \
		$(call mkgeneric,runtime/perl,$(ver)))

# Build Perl version-wrapping manifests from the generic version.
# See the block comment above about why "###PYV###" is used here even
# though this is for Perl rather than Python.
$(MANIFEST_BASE)-%.p5m: %-PERLVER.p5m $(BUILD_DIR)/mkgeneric-perl
	$(PKGFMT) $(PKGFMT_CHECK_ARGS) $(CANONICAL_MANIFESTS)
	$(PKGMOGRIFY) -D PLV=###PYV### -D MAYBE_PERLVER_SPACE= \
		-D MAYBE_SPACE_PERLVER= $(BUILD_DIR)/mkgeneric-perl \
		$(WS_TOP)/transforms/mkgeneric $< > $@
	if [ -f $*-GENFRAG.p5m ]; then cat $*-GENFRAG.p5m >> $@; fi

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
	$(PKGFMT) $(PKGFMT_CHECK_ARGS) $(CANONICAL_MANIFESTS)
	$(PKGMOGRIFY) -D RUBY_VERSION=$(1) -D RUBY_LIB_VERSION=$(2) \
	    -D MAYBE_RUBY_VERSION_SPACE="$(1) " \
	    -D MAYBE_SPACE_RUBY_VERSION=" $(1)" \
	    -D RUBYV=$(shell echo $(1) | tr -d .) $$< > $$@
endef
$(foreach ver,$(RUBY_VERSIONS),\
	$(eval $(call ruby-manifest-rule,$(shell echo $(ver) | \
	    cut -d. -f1,2),$(ver))))

# A rule to create a helper transform package for ruby, that will insert the
# appropriate conditional dependencies into a ruby library's
# runtime-version-generic package to pull in the version-specific bits when the
# corresponding version of ruby is on the system.
$(BUILD_DIR)/mkgeneric-ruby: $(WS_MAKE_RULES)/shared-macros.mk
	$(RM) $@
	$(foreach ver,$(RUBY_VERSIONS),\
		$(call mkgeneric,runtime/ruby,$(shell echo $(ver) | \
		    cut -d. -f1,2 | tr -d .)))

# Build Ruby version-wrapping manifests from the generic version.
# Creates build/manifest-*-modulename.p5m file.
#
# See the block comment above about why "###PYV###" is used here even
# though this is for Ruby rather than Python.
$(MANIFEST_BASE)-%.p5m: %-RUBYVER.p5m $(BUILD_DIR)/mkgeneric-ruby
	$(PKGFMT) $(PKGFMT_CHECK_ARGS) $(CANONICAL_MANIFESTS)
	$(PKGMOGRIFY) -D RUBYV=###PYV### -D MAYBE_RUBY_VERSION_SPACE= \
		-D MAYBE_SPACE_RUBY_VERSION= $(BUILD_DIR)/mkgeneric-ruby \
		$(WS_TOP)/transforms/mkgeneric $< > $@
	if [ -f $*-GENFRAG.p5m ]; then cat $*-GENFRAG.p5m >> $@; fi

# Rule to generate historical manifests from the $(HISTORY) file.
define history-manifest-rule
$(MANIFEST_BASE)-$(1): $(HISTORY) $(BUILD_DIR)
	$(NAWK) -v TARGET=$(1) -v FUNCTION=manifest -f $(GENERATE_HISTORY) < \
	    $(HISTORY) > $$@
endef
$(foreach mfst,$(HISTORICAL_MANIFESTS),$(eval $(call history-manifest-rule,$(mfst))))

# mogrify non-parameterized manifests
$(MANIFEST_BASE)-%.mogrified:	%.p5m $(BUILD_DIR)
	$(PKGFMT) $(PKGFMT_CHECK_ARGS) $<
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@

# mogrify parameterized manifests
$(MANIFEST_BASE)-%.mogrified:	$(MANIFEST_BASE)-%.p5m $(BUILD_DIR)
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@

# mangle the file contents
$(BUILD_DIR) $(MANGLED_DIR):
	$(MKDIR) $@

PKGMANGLE_OPTIONS = -D $(MANGLED_DIR) $(PKG_PROTO_DIRS:%=-d %)
$(MANIFEST_BASE)-%.mangled:	$(MANIFEST_BASE)-%.mogrified $(MANGLED_DIR)
	$(PKGMANGLE) $(PKGMANGLE_OPTIONS) -m $< >$@

# generate dependencies
PKGDEPEND_GENERATE_OPTIONS = -m $(PKG_PROTO_DIRS:%=-d %)
$(MANIFEST_BASE)-%.depend:	$(MANIFEST_BASE)-%.mangled
	$(ENV) $(COMPONENT_PUBLISH_ENV) $(PKGDEPEND) generate \
	    $(PKGDEPEND_GENERATE_OPTIONS) $< >$@

# pkgdepend resolve builds a map of all installed packages by default.  This
# makes dependency resolution particularly slow.  We can dramatically improve
# performance here by creating a file with a list of packages that we know
# are needed, dramatically reducing the overhead involved in creating and
# searching this map.
#
# Generate a resolve.deps file from the dependencies in the Makefile and
# fragments that it uses.
RESOLVE_DEPS=$(BUILD_DIR)/resolve.deps

$(RESOLVE_DEPS):	$(MAKEFILE_PREREQ) $(BUILD_DIR)
	@for pkg in $(REQUIRED_PACKAGES:%=/%) ; do \
	    echo $${pkg} ; \
	done | sort -u >$@

# resolve the dependencies all at once
$(BUILD_DIR)/.resolved-$(MACH):	$(DEPENDED) $(RESOLVE_DEPS)
	$(PKGDEPEND) resolve $(RESOLVE_DEPS:%=-e %) -m $(DEPENDED)
	$(TOUCH) $@

#
# Generate a set of REQUIRED_PACKAGES based on what is needed to for pkgdepend
# to resolve properly.  Automatically append this to your Makefile for the truly
# lazy among us.  This is only a piece of the REQUIRED_PACKAGES puzzle.
# You must still include packages for tools you build and test with.
#
REQUIRED_PACKAGES::	$(RESOLVED)
	$(GMAKE) RESOLVE_DEPS= $(BUILD_DIR)/.resolved-$(MACH)
	@echo "# Auto-generated contents below.  Please manually verify and remove this comment" >>Makefile
	@$(PKGMOGRIFY) $(WS_TRANSFORMS)/$@ $(RESOLVED) | \
		$(GSED) -e '/^[\t ]*$$/d' -e '/^#/d' | sort -u >>Makefile
	@echo "*** Please edit your Makefile and verify the new content at the end ***"

# lint the manifests all at once
$(BUILD_DIR)/.linted-$(MACH):	$(BUILD_DIR)/.resolved-$(MACH)
	@echo "VALIDATING MANIFEST CONTENT: $(RESOLVED)"
	$(ENV) PYTHONPATH=$(WS_TOOLS)/python PROTO_PATH="$(PKG_PROTO_DIRS)"\
		SOLARIS_VERSION=$(SOLARIS_VERSION)\
		$(PKGLINT) $(CANONICAL_REPO:%=-c $(WS_LINT_CACHE)) \
			-f $(WS_TOOLS)/pkglintrc $(RESOLVED)
	$(TOUCH) $@

lintme: FRC
	@echo "VALIDATING MANIFEST CONTENT: $(RESOLVED)"
	$(ENV) PYTHONPATH=$(WS_TOOLS)/python PROTO_PATH="$(PKG_PROTO_DIRS)"\
		SOLARIS_VERSION=$(SOLARIS_VERSION)\
		$(PKGLINT) $(CANONICAL_REPO:%=-c $(WS_LINT_CACHE)) \
			-f $(WS_TOOLS)/pkglintrc $(RESOLVED)

FRC:


# published
PKGSEND_PUBLISH_OPTIONS = -s $(PKG_REPO) publish --fmri-in-manifest
PKGSEND_PUBLISH_OPTIONS += --no-catalog
PKGSEND_PUBLISH_OPTIONS += $(PKG_PROTO_DIRS:%=-d %)
PKGSEND_PUBLISH_OPTIONS += -T \*.py

# PKGREPO_REMOVE_BEFORE_PUBLISH remove previously published versions of this package
# before publishing the new build
PKGREPO_REMOVE_BEFORE_PUBLISH ?= no

$(MANIFEST_BASE)-%.published:	$(MANIFEST_BASE)-%.depend.res $(BUILD_DIR)/.linted-$(MACH)
ifeq ($(PKGREPO_REMOVE_BEFORE_PUBLISH),yes)
	-$(PKGREPO) -s $(PKG_REPO) remove \
			$(shell $(CAT) $< $(WS_TOP)/transforms/print-pkgs | \
				$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
				sed -e '/^$$/d' -e '/^#.*$$/d' | sort -u)
endif
	$(PKGSEND) $(PKGSEND_PUBLISH_OPTIONS) $<
	$(PKGFMT) <$< >$@

$(BUILD_DIR)/.published-$(MACH):	$(PUBLISHED)
ifndef DISABLE_IPS_CATALOG_AND_INDEX_UPDATES
	$(PKGREPO) refresh -s $(PKG_REPO)
endif
	$(TOUCH) $@

print-package-names:	canonical-manifests
	@cat $(VERSIONED_MANIFESTS) $(WS_TOP)/transforms/print-pkgs | \
		$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
 		sed -e '/^$$/d' -e '/^#.*$$/d' | sort -u

print-package-paths:	canonical-manifests
	@cat $(VERSIONED_MANIFESTS) $(WS_TOP)/transforms/print-paths | \
		$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
 		sed -e '/^$$/d' -e '/^#.*$$/d' | sort -u

install-packages:	publish
	@if [ $(IS_GLOBAL_ZONE) = 0 -o x$(ROOT) != x ]; then \
	    cat $(VERSIONED_MANIFESTS) $(WS_TOP)/transforms/print-paths | \
		$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
 		sed -e '/^$$/d' -e '/^#.*$$/d' -e 's;/;;' | sort -u | \
		(cd $(PROTO_DIR) ; pfexec /bin/cpio -dump $(ROOT)) ; \
	else ; \
	    echo "unsafe to install package(s) automatically" ; \
        fi

$(RESOLVED):	install

canonical-manifests:	$(CANONICAL_MANIFESTS) $(MAKEFILE_PREREQ) $(ALL_PATCHES) \
    $(HISTORY)
ifeq	($(strip $(CANONICAL_MANIFESTS)),)
	# If there were no canonical manifests in the workspace, nothing will
	# be published and we should fail.  A sample manifest can be generated
	# with
	#   $ gmake sample-manifest
	# Once created, it will need to be reviewed, edited, and added to the
	# workspace.
	$(error Missing canonical manifest(s))
endif

# Add component-specific variables and export to PKG_OPTIONS.
COMP_SUFFIXES = $(subst COMPONENT_NAME_,, \
		$(filter COMPONENT_NAME_%, $(.VARIABLES)))

# Component variables are expanded directly to PKG_OPTIONS instead of via
# PKG_MACROS since the values may contain whitespace.
mkdefine = -D $(1)="$(2)"

# Expand PKG_VARS into defines via PKG_OPTIONS.
$(foreach var, $(PKG_VARS), \
    $(eval PKG_OPTIONS += $(call mkdefine,$(var),$$($(var)))) \
)

# Expand any variables ending in component _$(suffix) via PKG_OPTIONS excluding
# variables known to always be irrelevant and TPNO_% variables as those have
# already been processed.
$(foreach suffix, $(COMP_SUFFIXES), \
    $(eval COMPONENT_RE_VERSION_$(suffix) ?= $(subst .,\\.,$$(COMPONENT_VERSION_$(suffix)))) \
    $(eval IPS_COMPONENT_VERSION_$(suffix) ?= $$(COMPONENT_VERSION_$(suffix))) \
    $(eval IPS_COMPONENT_RE_VERSION_$(suffix) ?= $(subst .,\\.,$$(IPS_COMPONENT_VERSION_$(suffix)))) \
    $(eval COMP_VARS=$(filter %_$(suffix), $(.VARIABLES))) \
    $(eval COMP_VARS=$(filter-out COMPONENT_POST_UNPACK_%, $(COMP_VARS))) \
    $(eval COMP_VARS=$(filter-out TPNO_%, $(COMP_VARS))) \
    $(eval COMP_VARS=$(filter-out UNPACK_ARGS_%, $(COMP_VARS))) \
    $(foreach macro, $(COMP_VARS), \
        $(eval PKG_OPTIONS += $(call mkdefine,$(macro),$$($(macro)))) \
    ) \
)
