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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#

# All Perl versions are 32-bit only.

COMMON_PERL_ENV +=	MAKE=$(GMAKE)
COMMON_PERL_ENV +=	PATH=$(dir $(CC)):$(SPRO_VROOT)/bin:$(PATH)
COMMON_PERL_ENV +=	LANG=""
COMMON_PERL_ENV +=	CC="$(CC)"
COMMON_PERL_ENV +=	CFLAGS="$(PERL_OPTIMIZE)"

# Yes.  Perl is just scripts, for now, but we need architecture
# directories so that it populates all architecture prototype
# directories.

$(BUILD_DIR)/$(MACH32)-5.22/.configured:	PERL_VERSION=5.22
$(BUILD_DIR)/$(MACH32)-5.22/.configured:	BITS=32
$(BUILD_DIR)/$(MACH64)-5.24/.configured:	PERL_VERSION=5.24
$(BUILD_DIR)/$(MACH64)-5.24/.configured:	BITS=64

$(BUILD_DIR)/$(MACH32)-5.22/.built:	PERL_VERSION=5.22
$(BUILD_DIR)/$(MACH32)-5.22/.built:	BITS=32
$(BUILD_DIR)/$(MACH64)-5.24/.built:	PERL_VERSION=5.24
$(BUILD_DIR)/$(MACH64)-5.24/.built:	BITS=64

$(BUILD_DIR)/$(MACH32)-5.22/.tested:	PERL_VERSION=5.22
$(BUILD_DIR)/$(MACH32)-5.22/.tested:	BITS=32
$(BUILD_DIR)/$(MACH64)-5.24/.tested:	PERL_VERSION=5.24
$(BUILD_DIR)/$(MACH64)-5.24/.tested:	BITS=64

$(BUILD_DIR)/$(MACH32)-5.22/.tested-and-compared:	BITS=32
$(BUILD_DIR)/$(MACH32)-5.22/.tested-and-compared:	PERL_VERSION=5.22
$(BUILD_DIR)/$(MACH64)-5.24/.tested-and-compared:	PERL_VERSION=5.24
$(BUILD_DIR)/$(MACH64)-5.24/.tested-and-compared:	BITS=64

PERL_32_TEST_FILES:=$(foreach ver, $(PERL_VERSIONS), $(BUILD_DIR)/$(MACH32)-$(ver)/.tested )
PERL_32_TEST_AND_COMPARE_FILES:=$(foreach ver, $(PERL_VERSIONS), $(BUILD_DIR)/$(MACH32)-$(ver)/.tested-and-compared )

BUILD_32 =	$(BUILD_DIR)/$(MACH32)-5.22/.built
BUILD_64 =	$(BUILD_DIR)/$(MACH64)-5.24/.built

INSTALL_32 =	$(BUILD_DIR)/$(MACH32)-5.22/.installed
INSTALL_64 =	$(BUILD_DIR)/$(MACH64)-5.24/.installed

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
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PERL_VERSION)-$(BITS).master
COMPONENT_TEST_OUTPUT = $(COMPONENT_TEST_BUILD_DIR)/test-$(PERL_VERSION)-$(BITS)-results
COMPONENT_TEST_DIFFS =  $(COMPONENT_TEST_BUILD_DIR)/test-$(PERL_VERSION)-$(BITS)-diffs
COMPONENT_TEST_SNAPSHOT = $(COMPONENT_TEST_BUILD_DIR)/results-$(PERL_VERSION)-$(BITS).snapshot
COMPONENT_TEST_TRANSFORM_CMD = $(COMPONENT_TEST_BUILD_DIR)/transform-$(PERL_VERSION)-$(BITS)-results

COMPONENT_TEST_TARGETS =	check
COMPONENT_TEST_ENV +=	$(COMMON_PERL_ENV)

# determine the type of tests we want to run.
ifeq ($(strip $(wildcard $(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
TEST_32 =	$(BUILD_DIR)/$(MACH32)-5.22/.tested
TEST_64 =	$(BUILD_DIR)/$(MACH64)-5.24/.tested
else
TEST_32 =       $(BUILD_DIR)/$(MACH32)-5.22/.tested-and-compared
TEST_64 =       $(BUILD_DIR)/$(MACH32)-5.24/.tested-and-compared
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
