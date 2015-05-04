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
# EXTRA_PATCHES{version} can be defined in the component Makefile to include
#     additional patches.
#

PATCH_PATTERN ?=	*.patch*

PATCH_DIR ?=		patches
# patches specific to parfait builds.
PARFAIT_PATCH_DIR =	parfait

PATCHES =	$(shell find $(PATCH_DIR) $(PARFAIT_PATCH_DIR) -type f \
			 -name '$(PATCH_PATTERN)' 2>/dev/null | \
				LC_COLLATE=C sort)
PATHCES +=	$(EXTRA_PATCHES)

PCH_SUFFIXES = $(patsubst .patch_%,%, $(filter-out .patch,$(suffix $(PATCHES))))

define patch-rule

ifeq ($(1),_0)
PATCH_PATTERN$(1) ?=	%.patch
PATCHES$(1) = $(filter %.patch,$(PATCHES))
else
PATCH_PATTERN$(1) ?=	%.patch$(1)
PATCHES$(1) = $(filter %.patch$(1),$(PATCHES))
endif

ifneq ($$(PATCHES$(1)),)
PATCH_STAMPS$(1) += $$(PATCHES$(1):$(PATCH_DIR)/%=$$(SOURCE_DIR$(1))/.patched-%)

# We should unpack the source that we patch before we patch it.
$$(PATCH_STAMPS$(1)::	$$(UNPACK_STAMP$(1)) unpack

$$(SOURCE_DIR$(1))/.patched-%:	$(PATCH_DIR)/%
	$(GPATCH) -d $$(@D) $$(GPATCH_FLAGS) < $$<
	$(TOUCH) $$(@)

patch::	$$(PATCH_STAMPS$(1))

REQUIRED_PACKAGES += text/gnu-patch

endif
endef

#
# Define the rules required to download any source archives and augment any
# cleanup macros.
#
$(foreach suffix, $(PCH_SUFFIXES), $(eval $(call patch-rule,_$(suffix))))
$(eval $(call patch-rule,))	# this must be last so we don't drop *.patch_%.
