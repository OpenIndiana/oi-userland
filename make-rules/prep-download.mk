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

FETCH =		$(WS_TOOLS)/userland-fetch

#
# Anything that we download must have a COMPONENT_ARCHIVE_URL{_[0-9]+} macro
# that tells us where the canonical source for the archive can be found.  The
# macro for the first archive is typically un-suffixed.  By convention,
# subsequent archives will include a _[0-9]+ in the macro name.  This allows
# an arbitrary number of archives to be downloaded for a particular component
# Makefile.  It is also important to note that there is a corresponding
# COMPONENT_ARCHIVE macro defining a local file name for the archive, and
# optional COMPONENT_ARCHIVE_HASH and COMPONENT_SIG_URL containing a hash of
# the file and signature for verification of its contents.
#

URL_SUFFIXES = $(subst COMPONENT_ARCHIVE_URL_,, \
		$(filter COMPONENT_ARCHIVE_URL_%, $(.VARIABLES)))

# Argument to "userland-fetch" script that causes it to download and verify
# files, but not to remove mismatches; good to save traffic when initially
# fetching a new archive just to learn what checksum to expect in Makefile.
#FETCH_KEEP ?= --keep
FETCH_KEEP ?=

# Template for download rules.
define download-rules
ifdef COMPONENT_ARCHIVE_URL$(1)

ARCHIVES += $$(COMPONENT_ARCHIVE$(1))
CLOBBER_PATHS += $$(COMPONENT_ARCHIVE$(1))

fetch::	FETCH_KEEP=--keep
fetch::	$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1))

download::	$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1))

$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1)):	$(MAKEFILE_PREREQ)
	$$(FETCH) $$(FETCH_KEEP) --file $$@ \
		$$(COMPONENT_ARCHIVE_URL$(1):%=--url %) \
		$$(COMPONENT_ARCHIVE_HASH$(1):%=--hash %) \
		$$(COMPONENT_SIG_URL$(1):%=--sigurl %) \
		$$(if $$(COMPONENT_FETCH_USER_AGENT$(1)),--user-agent $$(COMPONENT_FETCH_USER_AGENT$(1)))
	$$(TOUCH) $$@

USERLAND_REQUIRED_PACKAGES += runtime/python-27

endif
endef

#
# Define the rules required to download any source archives and augment any
# cleanup macros.
#
$(eval $(call download-rules,))
$(foreach suffix, $(URL_SUFFIXES), $(eval $(call download-rules,_$(suffix))))

# Needed for signature validation of downloads
USERLAND_REQUIRED_PACKAGES += crypto/gnupg
