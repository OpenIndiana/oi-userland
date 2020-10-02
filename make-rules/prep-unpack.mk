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
# Copyright (c) 2018, Michal Nowak
#

UNPACK =		$(WS_TOOLS)/userland-unpack

#
# Anything that we downloaded and want to unpack must have a
# COMPONENT_ARCHIVE{_[0-9]+} macro.
#
PCK_SUFFIXES = $(subst COMPONENT_ARCHIVE_,, \
                $(filter COMPONENT_ARCHIVE_%, $(.VARIABLES)))

# Template for unpacking rules.
define unpack-rules
ifdef COMPONENT_ARCHIVE$(1)
ifdef COMPONENT_SRC$(1)

CLEAN_PATHS += $$(COMPONENT_SRC$(1))
SOURCE_DIR$(1) = $$(COMPONENT_DIR)/$(COMPONENT_SRC$(1))

UNPACK_STAMP$(1) =	$$(SOURCE_DIR$(1))/.unpacked

# RUBY_VERSION is passed on to ensure userland-unpack uses the
# correct gem command for the ruby version specified
$$(UNPACK_STAMP$(1)):	$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1)) $(MAKEFILE_PREREQ) download
	$$(RM) -r $$(SOURCE_DIR$(1))
	$(ENV) RUBY_VERSION=$(RUBY_VERSION) \
	$$(UNPACK) $$(UNPACK_ARGS$(1)) $$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1))
	$$(COMPONENT_POST_UNPACK_ACTION$(1))
	$$(TOUCH) $$@

unpack::	$$(UNPACK_STAMP$(1))

USERLAND_REQUIRED_PACKAGES += archiver/gnu-tar
USERLAND_REQUIRED_PACKAGES += compress/bzip2
USERLAND_REQUIRED_PACKAGES += compress/gzip
USERLAND_REQUIRED_PACKAGES += compress/p7zip
USERLAND_REQUIRED_PACKAGES += compress/unzip
USERLAND_REQUIRED_PACKAGES += compress/lzip
USERLAND_REQUIRED_PACKAGES += compress/xz
USERLAND_REQUIRED_PACKAGES += compress/zip
USERLAND_REQUIRED_PACKAGES += compress/zstd
USERLAND_REQUIRED_PACKAGES += developer/java/jdk
USERLAND_REQUIRED_PACKAGES += runtime/ruby

endif
endif
endef

#
# Define the rules required to download any source archives and augment any
# cleanup macros.
#
$(eval $(call unpack-rules,))
$(foreach suffix, $(PCK_SUFFIXES), $(eval $(call unpack-rules,_$(suffix))))
