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
# Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
#

# One must do all unpack and patch in sequence.
.NOTPARALLEL: (SOURCE_DIR)/.prep

UNPACK =	$(WS_TOOLS)/userland-unpack
FETCH =		$(WS_TOOLS)/userland-fetch

ARCHIVES += $(COMPONENT_ARCHIVE)
CLEAN_PATHS += $(SOURCE_DIR)

# In order to override PATCH_DIR and PATCH_PATTERN in component makefiles, they
# need to be conditionally set here.  This means that the override needs to
# happen prior to including prep.mk.  Otherwise other variables set here which
# are based on those will be expanded too early for the override to take 
# effect.
# You also can't override PATCHES after including prep.mk; if you want to
# append filenames to PATCHES, you'll have to set $(EXTRA_PATCHES) prior to
# inclusion.
PATCH_DIR ?=	patches

# we may need patches only for use with parfait
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PARFAIT_PATCH_DIR =	parfait
endif
PATCH_PATTERN ?=	*.patch
PATCHES =	$(shell find $(PATCH_DIR) $(PARFAIT_PATCH_DIR) -type f -name '$(PATCH_PATTERN)' \
				2>/dev/null | sort) $(EXTRA_PATCHES)

# Rule to perform the patching.
$(SOURCE_DIR)/.%ed:	$(PATCH_DIR)/%
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) < $<
	$(TOUCH) $@

# Parfait patches rule: TODO - Integrate with other patch rules
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
$(SOURCE_DIR)/.%ed:	$(PARFAIT_PATCH_DIR)/%
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) < $<
	$(TOUCH) $@
endif

# Template for download rules.
define download-rule
ARCHIVES += $$(COMPONENT_ARCHIVE$(1))
CLOBBER_PATHS += $$(COMPONENT_ARCHIVE$(1))
$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1)):	Makefile
	$$(FETCH) --file $$@ \
		$$(COMPONENT_ARCHIVE_URL$(1):%=--url %) \
		$$(COMPONENT_ARCHIVE_HASH$(1):%=--hash %)
	$$(TOUCH) $$@
endef

# Template for patching rules, note that patching is actually done by the 
# %.ed pattern rule above.
# To maintain backwards compatibility, the flag PATCH_EACH_ARCHIVE must
# be non-empty in order to activate individual archive patching.
define patch-rule
ifneq ($(strip $$(PATCH_EACH_ARCHIVE)),)
# Prepend the patch directory to each archive patch.
#$$(COMPONENT_PATCHES$(1):%=$$(PATCH_DIR)/%)
#PATCHDIR_PATCHES$(1) += $$(COMPONENT_PATCHES)
PATCHDIR_PATCHES$(1) += $$(foreach patch,$$(COMPONENT_PATCHES$(1)), \
						 $$(PATCH_DIR)/$$(patch))
else
PATCHDIR_PATCHES = $$(PATCHES)
endif
# Substitute the patch dir for the source dir on the patches
STAMPS$(1)+= $$(PATCHDIR_PATCHES$(1):$$(PATCH_DIR)/%=$$(SOURCE_DIR)/.%ed)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
STAMPS$(1)+= $$(PATCHDIR_PATCHES$(1):$$(PARFAIT_PATCH_DIR)/%=$$(SOURCE_DIR)/.%ed)
endif
$$(SOURCE_DIR)/.patched$(1): $$(SOURCE_DIR)/.unpacked$(1) $$(STAMPS$(1))
	$$(TOUCH) $$@
endef

# Template for unpacking rules.
define unpack-rule
$$(SOURCE_DIR)/.unpacked$(1): download Makefile $$(PATCHDIR_PATCHES$(1)) 
	$$(RM) -r $$(COMPONENT_SRC$(1))
	$$(UNPACK) $$(UNPACK_ARGS$(1)) \
		$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1))
	$$(COMPONENT_POST_UNPACK_ACTION$(1))
	$$(TOUCH) $$@
endef

# If an archive is defined, create a download, unpack and patch rule.
define archive-rule
ifneq ($(strip $$(COMPONENT_ARCHIVE$(1))),)
$(eval $(call download-rule,$(1)))
$(eval $(call unpack-rule,$(1)))
$(eval $(call patch-rule,$(1)))
ARCHIVE_STAMPS +=$$(SOURCE_DIR)/.patched$(1)
endif
endef

# Calculate the number of defined archives.
# Always generate at least the basic prep rules.
# Work out if there are any other archives to be downloaded and patched.
$(eval $(call archive-rule,))
ifneq ($(strip $(PATCH_EACH_ARCHIVE)),)
$(foreach suffix,$(NUM_EXTRA_ARCHIVES), \
	$(eval $(call archive-rule,_$(suffix))))
else
# Backwards compatibility - only download, do not unpack or patch automatically
$(foreach suffix,$(NUM_EXTRA_ARCHIVES), \
	$(eval $(call download-rule,_$(suffix))))
endif

$(SOURCE_DIR)/.prep: $(ARCHIVE_STAMPS)
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::	$(SOURCE_DIR)/.prep

download::	$(ARCHIVES:%=$(USERLAND_ARCHIVES)%)

clean::
	$(RM) -r $(CLEAN_PATHS)

clobber::	clean
	$(RM) -r $(CLOBBER_PATHS)
