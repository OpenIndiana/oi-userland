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
# Copyright (c) 2010, 2013, Oracle and/or its affiliates. All rights reserved.
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

PKGDEPEND =	/usr/bin/pkgdepend
PKGFMT =	/usr/bin/pkgfmt
PKGMOGRIFY =	/usr/bin/pkgmogrify
PKGSEND =	/usr/bin/pkgsend
ifeq   ($(strip $(PKGLINT_COMPONENT)),)
PKGLINT =	/usr/bin/pkglint
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

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/ignore-libs

ifneq ($(GCC_ROOT), /usr/gcc/4.9)
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/ignore-gcc-usr-lib
endif

COMPARISON_TRANSFORMS +=	$(WS_TOP)/transforms/comparison-cleanup
COMPARISON_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)

LICENSE_TRANSFORMS =		$(WS_TOP)/transforms/license-changes

# order is important
PUBLISH_TRANSFORMS +=	$(LICENSE_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/variant-cleanup
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/autopyc
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/defaults
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/actuators
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/devel
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/docs
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/locale
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/python-3-soabi
PUBLISH_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/publish-cleanup

ifeq   ($(strip $(COMPONENT_AUTOGEN_MANIFEST)),yes)
AUTOGEN_MANIFEST_TRANSFORMS +=		$(WS_TOP)/transforms/generate-cleanup
else
AUTOGEN_MANIFEST_TRANSFORMS +=		$(WS_TOP)/transforms/drop-all
endif

PKG_MACROS +=		MACH=$(MACH)
PKG_MACROS +=		MACH32=$(MACH32)
PKG_MACROS +=		MACH64=$(MACH64)
PKG_MACROS +=		PUBLISHER=$(PUBLISHER)
PKG_MACROS +=		PUBLISHER_LOCALIZABLE=$(PUBLISHER_LOCALIZABLE)
PKG_MACROS +=		CONSOLIDATION=$(CONSOLIDATION)
PKG_MACROS +=		BUILD_VERSION=$(BUILD_VERSION)
PKG_MACROS +=		SOLARIS_VERSION=$(SOLARIS_VERSION)
PKG_MACROS +=		OS_VERSION=$(OS_VERSION)
PKG_MACROS +=		PKG_SOLARIS_VERSION=$(PKG_SOLARIS_VERSION)
PKG_MACROS +=		HUMAN_VERSION=$(HUMAN_VERSION)
PKG_MACROS +=		IPS_COMPONENT_VERSION=$(IPS_COMPONENT_VERSION)
PKG_MACROS +=		COMPONENT_VERSION=$(COMPONENT_VERSION)
PKG_MACROS +=		COMPONENT_PROJECT_URL=$(COMPONENT_PROJECT_URL)
PKG_MACROS +=		COMPONENT_ARCHIVE_URL=$(COMPONENT_ARCHIVE_URL)
PKG_MACROS +=		COMPONENT_HG_URL=$(COMPONENT_HG_URL)
PKG_MACROS +=		COMPONENT_HG_REV=$(COMPONENT_HG_REV)
PKG_MACROS +=		COMPONENT_NAME=$(COMPONENT_NAME)
PKG_MACROS +=		COMPONENT_FMRI=$(COMPONENT_FMRI)
PKG_MACROS +=		COMPONENT_LICENSE_FILE=$(COMPONENT_LICENSE_FILE)
PKG_MACROS +=		TPNO=$(TPNO)
PKG_MACROS +=		USERLAND_GIT_REMOTE=$(USERLAND_GIT_REMOTE)
PKG_MACROS +=		USERLAND_GIT_BRANCH=$(USERLAND_GIT_BRANCH)
PKG_MACROS +=		USERLAND_GIT_REV=$(USERLAND_GIT_REV)

PKG_OPTIONS +=		$(PKG_MACROS:%=-D %) \
					-D COMPONENT_SUMMARY="$(strip $(COMPONENT_SUMMARY))" \
					-D COMPONENT_CLASSIFICATION="org.opensolaris.category.2008:$(strip $(COMPONENT_CLASSIFICATION))" \
					-D COMPONENT_DESCRIPTION="$(strip $(COMPONENT_DESCRIPTION))" \
					-D COMPONENT_LICENSE="$(strip $(COMPONENT_LICENSE))"

PKG_MACROS +=           PYTHON_2.7_ONLY=\#
PKG_MACROS +=           PYTHON_3.4_ONLY=\#

MANGLED_DIR =	$(PROTO_DIR)/mangled

PKG_PROTO_DIRS += $(MANGLED_DIR) $(PROTO_DIR) $(@D) $(COMPONENT_DIR) $(COMPONENT_SRC)

MANIFEST_BASE =		$(BUILD_DIR)/manifest-$(MACH)

SAMPLE_MANIFEST_DIR = 	$(COMPONENT_DIR)/manifests
SAMPLE_MANIFEST_FILE =	$(SAMPLE_MANIFEST_DIR)/sample-manifest.p5m

CANONICAL_MANIFESTS =	$(wildcard *.p5m)
ifneq ($(wildcard $(HISTORY)),)
HISTORICAL_MANIFESTS = $(shell $(NAWK) -v FUNCTION=name -f $(GENERATE_HISTORY) < $(HISTORY))
endif

# Look for manifests which need to be duplicated for each version of python.
ifeq ($(findstring -PYVER,$(CANONICAL_MANIFESTS)),-PYVER)
UNVERSIONED_MANIFESTS = $(filter-out %-GENFRAG.p5m,$(filter-out %-PYVER.p5m,$(CANONICAL_MANIFESTS)))
PY_MANIFESTS = $(filter %-PYVER.p5m,$(CANONICAL_MANIFESTS))
PYV_MANIFESTS = $(foreach v,$(shell echo $(PYTHON_VERSIONS) | tr -d .),$(shell echo $(PY_MANIFESTS) | sed -e 's/-PYVER.p5m/-$(v).p5m/g'))
PYNV_MANIFESTS = $(shell echo $(PY_MANIFESTS) | sed -e 's/-PYVER//')
else
UNVERSIONED_MANIFESTS = $(CANONICAL_MANIFESTS)
endif

# Look for manifests which need to be duplicated for each version of perl.
ifeq ($(findstring -PERLVER,$(UNVERSIONED_MANIFESTS)),-PERLVER)
NOPERL_MANIFESTS = $(filter-out %-GENFRAG.p5m,$(filter-out %-PERLVER.p5m,$(UNVERSIONED_MANIFESTS)))
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
publish:		pre-publish $(PUBLISH_STAMP)

sample-manifest:	$(GENERATED).p5m

$(GENERATED).p5m:	install
	[ ! -d $(SAMPLE_MANIFEST_DIR) ] && $(MKDIR) $(SAMPLE_MANIFEST_DIR) || true
	$(PKGSEND) generate $(PKG_HARDLINKS:%=--target %) $(PROTO_DIR) | \
	$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 $(GENERATE_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' -e '/^dir .*$$/d' \
		-e '/\.la$$/d' -e '/\.pyo$$/d' -e '/usr\/lib\/python[23]\..*\.pyc$$/d' \
		-e '/.*\/__pycache__\/.*/d'  | \
		$(PKGFMT) | \
		cat $(METADATA_TEMPLATE) - | \
		$(TEE) $@ $(SAMPLE_MANIFEST_FILE) >/dev/null

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

# Define and execute a macro that generates a rule to create a manifest for a
# python module specific to a particular version of the python runtime.
define python-manifest-rule
$(MANIFEST_BASE)-%-$(shell echo $(1) | tr -d .).mogrified: PKG_MACROS += PYTHON_$(1)_ONLY=

$(MANIFEST_BASE)-%-$(shell echo $(1) | tr -d .).p5m: %-PYVER.p5m
	$(PKGMOGRIFY) -D PYVER=$(1) -D PYV=$(shell echo $(1) | tr -d .) $$< > $$@
endef
$(foreach ver,$(PYTHON_VERSIONS),$(eval $(call python-manifest-rule,$(ver))))

# A rule to create a helper transform package for python, that will insert the
# appropriate conditional dependencies into a python library's
# runtime-version-generic package to pull in the version-specific bits when the
# corresponding version of python is on the system.
$(BUILD_DIR)/mkgeneric-python: $(WS_TOP)/make-rules/shared-macros.mk $(MAKEFILE_PREREQ)
	$(RM) $@
	$(foreach ver,$(shell echo $(PYTHON_VERSIONS) | tr -d .), \
		$(call mkgeneric,runtime/python,$(ver)))

# Build Python version-wrapping manifests from the generic version.
$(MANIFEST_BASE)-%.p5m: %-PYVER.p5m $(BUILD_DIR)/mkgeneric-python
	$(PKGMOGRIFY) -D PYV=### $(BUILD_DIR)/mkgeneric-python \
		$(WS_TOP)/transforms/mkgeneric $< > $@
	if [ -f $*-GENFRAG.p5m ]; then cat $*-GENFRAG.p5m >> $@; fi

# Define and execute a macro that generates a rule to create a manifest for a
# perl module specific to a particular version of the perl runtime.
define perl-manifest-rule
$(MANIFEST_BASE)-%-$(shell echo $(1) | tr -d .).p5m: %-PERLVER.p5m
	$(PKGMOGRIFY) -D PERLVER=$(1) -D PLV=$(shell echo $(1) | tr -d .) \
		-D PERL_ARCH=$(call PERL_ARCH_FUNC,$(PERL.$(1))) $$< > $$@
endef
$(foreach ver,$(PERL_VERSIONS),$(eval $(call perl-manifest-rule,$(ver))))

# A rule to create a helper transform package for perl, that will insert the
# appropriate conditional dependencies into a perl library's
# runtime-version-generic package to pull in the version-specific bits when the
# corresponding version of perl is on the system.
$(BUILD_DIR)/mkgeneric-perl: $(WS_TOP)/make-rules/shared-macros.mk $(MAKEFILE_PREREQ)
	$(RM) $@
	$(foreach ver,$(shell echo $(PERL_VERSIONS) | tr -d .), \
		$(call mkgeneric,runtime/perl,$(ver)))

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
$(MANIFEST_BASE)-%.mogrified:	%.generated
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@

# mogrify parameterized manifests
$(MANIFEST_BASE)-%.mogrified:	$(MANIFEST_BASE)-%.generated
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@
else
# mogrify non-parameterized manifests
$(MANIFEST_BASE)-%.mogrified:	%.p5m $(BUILD_DIR)
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@

# mogrify parameterized manifests
$(MANIFEST_BASE)-%.mogrified:	$(MANIFEST_BASE)-%.p5m $(BUILD_DIR)
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

# These files should contain a list of packages that the component is known to
# depend on.  Using resolve.deps is not required, but significantly speeds up
# the "pkg resolve" step.
# XXX existing pkg5 is too old for that
#EXTDEPFILES = $(wildcard $(sort $(addsuffix ../resolve.deps, $(dir $(DEPENDED)))))

# This is a target that should only be run by hand, and not something that
# .resolved-$(MACH) should depend on.
sample-resolve.deps:
	echo "<transform depend type=(require|require-any) -> print %(fmri)>" > rd-trans
	for i in build/*.depend; do \
		$(PKGMOGRIFY) -O /dev/null $$i rd-trans | tr " " "\n" | sort -u > m1; \
		$(PKGMOGRIFY) -O /dev/null $$i.res rd-trans | tr " " "\n" | sort -u > m2; \
		comm -13 m1 m2; \
	done | sed -e 's/@[^ ]*//g' -e 's,pkg:/,,g' | sort -u > resolve.deps
	$(RM) rd-trans m1 m2
	if [[ ! -s resolve.deps ]]; then \
		echo "No computed dependencies found; removing empty resolve.deps."; \
		$(RM) resolve.deps; \
	fi


# resolve the dependencies all at once
$(BUILD_DIR)/.resolved-$(MACH):	$(DEPENDED)
	$(PKGDEPEND) resolve $(EXTDEPFILES:%=-e %) -m $(DEPENDED)
	$(TOUCH) $@

#
# Generate a set of REQUIRED_PACKAGES based on what is needed to for pkgdepend
# to resolve properly.  Automatically append this to your Makefile for the truly
# lazy among us.  This is only a piece of the REQUIRED_PACKAGES puzzle.
# You must still include packages for tools you build and test with.
#
REQUIRED_PACKAGES::     $(RESOLVED)
	$(GMAKE) RESOLVE_DEPS= $(BUILD_DIR)/.resolved-$(MACH)
	@echo "# Auto-generated dependencies" >>Makefile
	@$(PKGMOGRIFY) $(WS_TRANSFORMS)/$@ $(RESOLVED) | \
               $(GSED) -e '/^[\t ]*$$/d' -e '/^#/d' | sort -u >>Makefile
	@echo "*** Please edit your Makefile and verify the new content at the end ***"


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
	$(CP) $< $@
	@echo "NEW PACKAGE CONTENTS ARE LOCALLY VALIDATED AND READY TO GO"

# Push to the repo
$(MANIFEST_BASE)-%.published:	$(MANIFEST_BASE)-%.pre-published
	$(PKGSEND) $(PKGSEND_PUBLISH_OPTIONS) $<
	$(PKGFMT) <$< >$@

$(BUILD_DIR)/.pre-published-$(MACH):	$(PRE_PUBLISHED)
	$(TOUCH) $@

$(BUILD_DIR)/.published-$(MACH):	$(PUBLISHED)
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
