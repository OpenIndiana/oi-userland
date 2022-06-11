
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

# perl-5.22 is 32 bit (only), perl-5.24 and later are 64 bit (only)

COMMON_PERL_ENV +=	MAKE=$(GMAKE)
COMMON_PERL_ENV +=	PATH=$(dir $(CC)):$(SPRO_VROOT)/bin:$(PATH)
COMMON_PERL_ENV +=	LANG=""
COMMON_PERL_ENV +=	CC="$(CC)"
COMMON_PERL_ENV +=	CFLAGS="$(CC_BITS) $(PERL_OPTIMIZE)"

# Generate requirements on all built perl version variants for given packages
REQUIRED_PACKAGES += $(PERL_REQUIRED_PACKAGES)
REQUIRED_PACKAGES += $(foreach ver,$(PERL_VERSIONS),$(PERL_REQUIRED_PACKAGES:%=%-$(shell echo $(ver) | tr -d .)))

# Yes.  Perl is just scripts, for now, but we need architecture
# directories so that it populates all architecture prototype
# directories.

$(BUILD_DIR)/%-5.22/.configured:	PERL_VERSION=5.22
$(BUILD_DIR)/%-5.24/.configured:	PERL_VERSION=5.24
$(BUILD_DIR)/%-5.34/.configured:	PERL_VERSION=5.34
$(BUILD_DIR)/$(MACH32)-%/.configured:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.configured:	BITS=64

$(BUILD_DIR)/%-5.22/.built:	PERL_VERSION=5.22
$(BUILD_DIR)/%-5.24/.built:	PERL_VERSION=5.24
$(BUILD_DIR)/%-5.34/.built:	PERL_VERSION=5.34
$(BUILD_DIR)/$(MACH32)-%/.built:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64

$(BUILD_DIR)/%-5.22/.installed:	PERL_VERSION=5.22
$(BUILD_DIR)/%-5.24/.installed:	PERL_VERSION=5.24
$(BUILD_DIR)/%-5.34/.installed:	PERL_VERSION=5.34
$(BUILD_DIR)/$(MACH32)-%/.installed:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64

$(BUILD_DIR)/%-5.22/.tested:	PERL_VERSION=5.22
$(BUILD_DIR)/%-5.24/.tested:	PERL_VERSION=5.24
$(BUILD_DIR)/%-5.34/.tested:	PERL_VERSION=5.34
$(BUILD_DIR)/$(MACH32)-%/.tested:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested:	BITS=64

$(BUILD_DIR)/%-5.22/.tested-and-compared:	PERL_VERSION=5.22
$(BUILD_DIR)/%-5.24/.tested-and-compared:	PERL_VERSION=5.24
$(BUILD_DIR)/%-5.34/.tested-and-compared:	PERL_VERSION=5.34
$(BUILD_DIR)/$(MACH32)-%/.tested-and-compared:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared:	BITS=64

PERL_32_ONLY_VERSIONS = $(filter-out $(PERL_64_ONLY_VERSIONS), $(PERL_VERSIONS))

BUILD_32 =	$(PERL_32_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.built)
BUILD_64 =	$(PERL_64_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
BUILD_NO_ARCH =	$(PERL_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.built)

ifeq ($(PERL_VERSION),5.24)
BUILD_32_and_64 = $(BUILD_64)
BUILD_64_and_32 = $(BUILD_64)
endif
ifeq ($(PERL_VERSION),5.34)
BUILD_32_and_64 = $(BUILD_64)
BUILD_64_and_32 = $(BUILD_64)
endif

INSTALL_32 = $(PERL_32_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.installed)
INSTALL_64 = $(PERL_64_ONLY_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)
INSTALL_NO_ARCH = $(PERL_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.installed)

COMPONENT_CONFIGURE_ENV +=	$(COMMON_PERL_ENV)
COMPONENT_CONFIGURE_ENV +=	PERL="$(PERL)"
$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -r $(@D) ; $(MKDIR) $(@D))
	$(CLONEY) $(SOURCE_DIR) $(@D)
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
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PERL_VERSION)-$(BITS).master
endif
COMPONENT_TEST_OUTPUT = $(COMPONENT_TEST_BUILD_DIR)/test-$(PERL_VERSION)-$(BITS)-results
COMPONENT_TEST_DIFFS =  $(COMPONENT_TEST_BUILD_DIR)/test-$(PERL_VERSION)-$(BITS)-diffs
COMPONENT_TEST_SNAPSHOT = $(COMPONENT_TEST_BUILD_DIR)/results-$(PERL_VERSION)-$(BITS).snapshot
COMPONENT_TEST_TRANSFORM_CMD = $(COMPONENT_TEST_BUILD_DIR)/transform-$(PERL_VERSION)-$(BITS)-results
#
# delete any lines up through test_harness
# delete timings
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/test_harness/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"'

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

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
parfait: build
else
parfait:
	$(MAKE) PARFAIT_BUILD=yes parfait
endif

clean:: 
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
