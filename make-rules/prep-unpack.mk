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
# Copyright (c) 2010, 2017, Oracle and/or its affiliates. All rights reserved.
#

UNPACK =		$(WS_TOOLS)/userland-unpack

#
# Anything that we downloaded and want to unpack must have a
# COMPONENT_ARCHIVE{_[0-9]+} macro.  Filter out a handful of
# well-known macros that don't correspond to extra archives.
#
PCK_SUFFIXES = $(filter-out HASH OVERRIDE SRC URL, $(subst COMPONENT_ARCHIVE_,, \
                $(filter COMPONENT_ARCHIVE_%, $(.VARIABLES))))

# Templates for unpacking variables and rules.  We separate the variable
# assignments from the rules so that all the variable assignments are given a
# chance to complete before those variables are used in targets or
# prerequisites, where they'll be expanded immediately.
#
# Some components don't have an archive that we download, but host their source
# directly in the repo, and a separate unpacking step will fail.  So we don't do
# any unpacking if COMPONENT_ARCHIVE_SRC is "none", and rely on such components
# to set that variable specifically.
#
# The reason we don't condition on an empty COMPONENT_ARCHIVE is that any
# components that rely on that being set by default by prep.mk won't have it set
# for this conditional.  It's easier to make the very few archive-less
# components declare themselves rather than force everyone else to use
# boilerplate code to name their archives.
define unpack-variables
ifneq ($(strip $(COMPONENT_ARCHIVE_SRC$(1))),none)
CLEAN_PATHS += $$(COMPONENT_SRC$(1))
SOURCE_DIR$(1) = $$(COMPONENT_SRC$(1):%=$$(COMPONENT_DIR)/%)

UNPACK_STAMP$(1) =	$$(SOURCE_DIR$(1):%=%/.unpacked)
else
CLEAN_PATHS += $$(SOURCE_DIR$(1))/.prep
endif
endef

define unpack-rules
ifneq ($(strip $(COMPONENT_ARCHIVE_SRC$(1))),none)
# RUBY_VERSION is passed on to ensure userland-unpack uses the
# correct gem command for the ruby version specified
$$(UNPACK_STAMP$(1)):	$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1)) download
	$$(RM) -r $$(SOURCE_DIR$(1))
	$(ENV) RUBY_VERSION=$(RUBY_VERSION) \
	$$(UNPACK) $$(UNPACK_ARGS$(1)) $$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1))
	$$(COMPONENT_POST_UNPACK_ACTION$(1))
	$$(TOUCH) $$@

unpack::	$$(UNPACK_STAMP$(1))

REQUIRED_PACKAGES += archiver/gnu-tar
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/gzip
REQUIRED_PACKAGES += compress/p7zip
REQUIRED_PACKAGES += compress/unzip
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zip
REQUIRED_PACKAGES += developer/java/jdk-8
REQUIRED_PACKAGES += runtime/ruby
endif
endef

# Evaluate the variable assignments immediately.
$(eval $(call unpack-variables,))
$(foreach suffix, $(PCK_SUFFIXES), $(eval $(call unpack-variables,_$(suffix))))

# Put the rule evaluations in a variable for deferred evaluation.
define eval-unpack-rules
$(eval $(call unpack-rules,))
$(foreach suffix, $(PCK_SUFFIXES), $(eval $(call unpack-rules,_$(suffix))))
endef
