
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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#

# Common perl environment
COMMON_PERL_ENV +=	MAKE=$(GMAKE)
COMMON_PERL_ENV +=	PATH=$(dir $(CC)):$(SPRO_VROOT)/bin:$(PATH)
COMMON_PERL_ENV +=	LANG=""
COMMON_PERL_ENV +=	CC="$(CC)"
COMMON_PERL_ENV +=	CFLAGS="$(CC_BITS) $(PERL_OPTIMIZE)"

# Particular perl runtime is always required (at least to run Makefile.PL)
PERL_REQUIRED_PACKAGES += runtime/perl

# Yes.  Perl is just scripts, for now, but we need architecture
# directories so that it populates all architecture prototype
# directories.

define perl-version-rule
$(BUILD_DIR)/%-$(1)/.configured:		PERL_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.built:			PERL_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.installed:			PERL_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.tested:			PERL_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.tested-and-compared:	PERL_VERSION=$(1)
endef
$(foreach perlver,$(PERL_VERSIONS),$(eval $(call perl-version-rule,$(perlver))))

$(BUILD_DIR)/$(MACH32)-%/.configured:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.configured:	BITS=64

$(BUILD_DIR)/$(MACH32)-%/.built:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64

$(BUILD_DIR)/$(MACH32)-%/.installed:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64

$(BUILD_DIR)/$(MACH32)-%/.tested:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested:	BITS=64

$(BUILD_DIR)/$(MACH32)-%/.tested-and-compared:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared:	BITS=64

PERL_32_ONLY_VERSIONS = $(filter-out $(PERL_64_ONLY_VERSIONS), $(PERL_VERSIONS))

BUILD_32 =	$(PERL_32_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.built)
BUILD_64 =	$(PERL_64_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
BUILD_NO_ARCH =	$(PERL_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.built)

INSTALL_32 = $(PERL_32_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.installed)
INSTALL_64 = $(PERL_64_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)
INSTALL_NO_ARCH = $(PERL_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.installed)

COMPONENT_CONFIGURE_ENV +=	$(COMMON_PERL_ENV)
COMPONENT_CONFIGURE_ENV +=	PERL="$(PERL)"
$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -r $(@D) ; $(MKDIR) $(@D))
	$(ENV) $(CLONEY_ARGS) $(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; $(COMPONENT_CONFIGURE_ENV) $(PERL) $(PERL_FLAGS) \
				Makefile.PL $(PERL_STUDIO_OVERWRITE) $(CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@


COMPONENT_BUILD_ENV +=	$(COMMON_PERL_ENV)
$(BUILD_DIR)/%/.built:	$(BUILD_DIR)/%/.configured
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
		$(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@


COMPONENT_INSTALL_ARGS +=	DESTDIR="$(PROTO_DIR)"
COMPONENT_INSTALL_TARGETS =	install_vendor
COMPONENT_INSTALL_ENV +=	$(COMMON_PERL_ENV)
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) \
			$(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

# Define bit specific and Perl version specific filenames.
ifeq ($(strip $(USE_COMMON_TEST_MASTER)),no)
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PERL_VERSION).master
endif
COMPONENT_TEST_BUILD_DIR = $(BUILD_DIR)/test
COMPONENT_TEST_OUTPUT = $(COMPONENT_TEST_BUILD_DIR)/test-$(PERL_VERSION)-results
COMPONENT_TEST_DIFFS =  $(COMPONENT_TEST_BUILD_DIR)/test-$(PERL_VERSION)-diffs
COMPONENT_TEST_SNAPSHOT = $(COMPONENT_TEST_BUILD_DIR)/results-$(PERL_VERSION).snapshot
COMPONENT_TEST_TRANSFORM_CMD = $(COMPONENT_TEST_BUILD_DIR)/transform-$(PERL_VERSION)-results

# Normalize perl test results.
COMPONENT_TEST_TRANSFORMS += '-e "0,/test_harness/d"'		# delete any lines up through test_harness
COMPONENT_TEST_TRANSFORMS += '-e "s/,  *[0-9]* wallclock.*//"'	# delete timings
COMPONENT_TEST_TRANSFORMS += '-e "/^\#/d"'			# delete comments
COMPONENT_TEST_TRANSFORMS += '-e "/^make\[/d"'			# delete make logs

# Add the expected 'test_harness' line if it is missing in the test results.
COMPONENT_POST_TEST_ACTION += $(GNU_GREP) -q test_harness $(COMPONENT_TEST_OUTPUT) \
	|| $(GSED) -i -e '1i\test_harness' $(COMPONENT_TEST_OUTPUT) ;

COMPONENT_TEST_TARGETS =	test
COMPONENT_TEST_ENV +=	$(COMMON_PERL_ENV)

# determine the type of tests we want to run.
ifeq ($(strip $(wildcard $(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
TEST_32 =	$(PERL_32_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.tested)
TEST_64 =	$(PERL_64_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested)
TEST_NO_ARCH =	$(PERL_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.tested)
else
TEST_32 =	$(PERL_32_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.tested-and-compared)
TEST_64 =	$(PERL_64_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared)
TEST_NO_ARCH = $(PERL_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.tested-and-compared)
endif

# test the built source
$(BUILD_DIR)/%/.tested-and-compared:    $(BUILD_DIR)/%/.built
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_TEST_ACTION)
	-(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS)) \
		&> $(COMPONENT_TEST_OUTPUT)
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_COMPARE)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

$(BUILD_DIR)/%/.tested:    $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_TEST_ACTION)
	(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS))
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@


# We need to add -$(PLV) to package fmri and generate runtime dependencies based on META.json
GENERATE_EXTRA_DEPS += $(BUILD_DIR)/META.json
GENERATE_EXTRA_CMD ?= \
	$(GSED) -e 's/^\(set name=pkg.fmri [^@]*\)\(.*\)$$/\1-$$(PLV)\2/' | \
	$(CAT) - <( \
		echo "" ; \
		echo "\# perl modules are unusable without perl runtime binary" ; \
		echo "depend type=require fmri=__TBD pkg.debug.depend.file=perl \\" ; \
		echo "    pkg.debug.depend.path=usr/perl5/\$$(PERLVER)/bin" ; \
		$(CAT) $(BUILD_DIR)/META.json \
			| $(WS_TOOLS)/perl-meta-deps $(WS_MACH) $(BUILD_DIR) runtime $(PERL_VERSION) \
			| $(GSED) -e 's|^\(depend.*pkg:/runtime/perl-\$$(PLV).*\)$$|\#\1|g' \
	)

# Support for adding dependencies from META.json to REQUIRED_PACKAGES
REQUIRED_PACKAGES_RESOLVED += $(BUILD_DIR)/META.depend.res
$(BUILD_DIR)/META.depend.res: $(BUILD_DIR)/META.json
	$(CAT) $(BUILD_DIR)/META.json | $(WS_TOOLS)/perl-meta-deps $(WS_MACH) $(BUILD_DIR) $(PERL_VERSION) > $@

$(BUILD_DIR)/META.json: $(SOURCE_DIR)/.prep
	$(MKDIR) $(BUILD_DIR)
	if [ -f $(SOURCE_DIR)/META.json ] ; then \
		$(CAT) $(SOURCE_DIR)/META.json ; \
	elif [ -f $(SOURCE_DIR)/META.yml ] ; then \
		$(CAT) $(SOURCE_DIR)/META.yml \
			| python -c 'import sys, yaml, json; y=yaml.safe_load(sys.stdin.read()); print(json.dumps(y))' \
			| jq '{prereqs:{configure:{requires:.configure_requires},build:{requires:.build_requires},runtime:{requires}}}' ; \
	fi > $@

# perl-meta-deps requires jq
USERLAND_REQUIRED_PACKAGES += text/jq
# pyyaml is needed to convert META.yml to META.json
USERLAND_REQUIRED_PACKAGES += library/python/pyyaml


ifeq   ($(strip $(PARFAIT_BUILD)),yes)
parfait: build
else
parfait:
	$(MAKE) PARFAIT_BUILD=yes parfait
endif

clean:: 
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
