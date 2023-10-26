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
# Copyright (c) 2010, 2015, Oracle and/or its affiliates. All rights reserved.
#

GPATCH =	/usr/gnu/bin/patch
PATCH_LEVEL ?=	1
GPATCH_BACKUP =	--backup --version-control=numbered
GPATCH_FLAGS =	--strip=$(PATCH_LEVEL) $(GPATCH_BACKUP)

#
# Rules for patching source that is downloaded and unpacked or pulled from
# a source repository.  Patches should be named
# patches/{patch-file-name}.patch{version} where {patch-file-name} is a
# meaningful name for the patch contents and {version} corresponds to the
# COMPONENT_NAME{version} of the source to be patched.  Typically, version
# would be something like "_1", "_2", ...  After all {version} patches have
# been applied, a final set of patches without a {version} suffix may be
# applied.
#
# PATCH_DIR can be overridden to move patches to a different location
# PATCH_PATTERN can be overridden to adjust the patch naming scheme that the
#     build recognizes.
# ADDITIONAL_PATCHES can be defined in the component Makefile to include
#     additional patches.
#

PATCH_PATTERN ?=	*.patch*

PATCH_DIR ?=		patches

PATCHES =	$(shell find $(PATCH_DIR) -type f \
			 -name '$(PATCH_PATTERN)' 2>/dev/null | \
				LC_COLLATE=C sort)

PCH_SUFFIXES = $(patsubst .patch_%,%, $(filter-out .patch,$(suffix $(PATCHES))))

define patch-rule

ifeq ($(1),_0)
PATCH_PATTERN$(1) ?=	%.patch
PATCHES$(1) = $(filter %.patch,$(PATCHES))
else
PATCH_PATTERN$(1) ?=	%.patch$(1)
PATCHES$(1) = $(filter %.patch$(1),$(PATCHES))
endif

ifneq ($(strip $(ADDITIONAL_PATCHES$(1))),)
PATCHES$(1) += $(ADDITIONAL_PATCHES$(1))
endif

ifneq ($$(PATCHES$(1)),)
PATCH_STAMPS$(1) += $$(PATCHES$(1):$(PATCH_DIR)/%=$$(SOURCE_DIR$(1))/.patched-%)

# We should unpack the source that we patch before we patch it.
$$(PATCH_STAMPS$(1)):	unpack

# Adding MAKEFILE_PREREQ because gmake seems to evaluate the need to patch
# before re-unpacking if the Makefile changed.  The various stamps are
# removed as part of the unpacking process, and it doesn't appear to
# re-evaluate the need for patching.  If we ever move the stamps to the build
# directory, we may not need the dependency any more.
$$(SOURCE_DIR$(1))/.patched-%:	$(PATCH_DIR)/% $(MAKEFILE_PREREQ)
	$(GPATCH) -d $$(@D) $$(GPATCH_FLAGS) < $$<
	$(TOUCH) $$(@)

$$(SOURCE_DIR$(1))/.patched-%:	$(MAKEFILE_PREREQ)
	$(GPATCH) -d $$(@D) $$(GPATCH_FLAGS) < $$<
	$(TOUCH) $$(@)

$$(SOURCE_DIR$(1))/.patched:	$$(PATCH_STAMPS$(1))
	$(TOUCH) $$(@)

patch::	$$(SOURCE_DIR$(1))/.patched

USERLAND_REQUIRED_PACKAGES += text/gnu-patch

endif
endef

#
# Define the rules required to download any source archives and augment any
# cleanup macros.
#
$(foreach suffix, $(PCH_SUFFIXES), $(eval $(call patch-rule,_$(suffix))))
$(eval $(call patch-rule,))	# this must be last so we don't drop *.patch_%.

# Helper target for patches refresh
refresh-patches: $(QUILT) patch
	# Unapply all patches
	for p in $(PATCHES) ; do \
		echo $$p ; \
	done | $(TAC) | while read p ; do \
		$(GPATCH) -d $(SOURCE_DIR) --strip=$(PATCH_LEVEL) --reverse < $$p ; \
	done
	# Make sure the series file does not exist
	$(RM) $(COMPONENT_DIR)/$(PATCH_DIR)/series
	# Apply and refresh patches, then unapply them
	cd $(SOURCE_DIR) ; for p in $(PATCHES) ; do \
		QUILT_PATCHES=../$(PATCH_DIR) $(QUILT) import --quiltrc /dev/null "../$$p" ; \
		QUILT_PATCHES=../$(PATCH_DIR) $(QUILT) push --quiltrc /dev/null -q ; \
		QUILT_PATCHES=../$(PATCH_DIR) $(QUILT) refresh --quiltrc /dev/null -p 1 --no-timestamps --no-index ; \
	done ; \
	[ ! -e $(COMPONENT_DIR)/$(PATCH_DIR)/series ] || QUILT_PATCHES=../$(PATCH_DIR) quilt pop --quiltrc /dev/null -a -q
	# cleanup
	$(RM) -r $(SOURCE_DIR)/.pc
	$(RM) $(COMPONENT_DIR)/$(PATCH_DIR)/series
	# Apply and refresh patches again to get the desired patch format
	for p in $(PATCHES) ; do \
		QUILT_PATCHES=$(PATCH_DIR) $(QUILT) import --quiltrc /dev/null -p 0 "$$p" ; \
		QUILT_PATCHES=$(PATCH_DIR) $(QUILT) push --quiltrc /dev/null -q ; \
		QUILT_PATCHES=$(PATCH_DIR) $(QUILT) refresh --quiltrc /dev/null -p 0 --no-timestamps --no-index ; \
	done
	# final cleanup
	$(RM) -r $(COMPONENT_DIR)/.pc
	$(RM) $(COMPONENT_DIR)/$(PATCH_DIR)/series
