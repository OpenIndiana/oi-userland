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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#

SVN =		/usr/bin/svn

#
# Anything that we pull from a Subversion repo must have a SVN_REPO{_[0-9]+} and
# SVN_REV{_[0-9]+} to match.
#

SVN_SUFFIXES = $(subst SVN_REPO_,, $(filter SVN_REPO_%, $(.VARIABLES)))

define subversion-rules
ifdef SVN_REPO$(1)
ifdef SVN_REV$(1)

COMPONENT_SRC$(1) = $$(COMPONENT_NAME$(1))-$$(SVN_REV$(1))
COMPONENT_ARCHIVE$(1) = $$(COMPONENT_SRC$(1)).tar.bz2
COMPONENT_ARCHIVE_SRC$(1) = svn

CLEAN_PATHS += $$(COMPONENT_SRC$(1))
CLOBBER_PATHS += COMPONENT_ARCHIVE$(1)
SOURCE_DIR$(1) = $$(COMPONENT_DIR)/$(COMPONENT_SRC$(1))

download::	$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1))

# First attempt to download a cached archive of the SCM repo at the proper
# changeset ID.  If that fails, create an archive by cloning the SCM repo,
# updating to the selected changeset, archiving that directory, and cleaning up # when complete.
$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1)):	$(MAKEFILE_PREREQ)
	$$(FETCH) --file $$@ $$(SVN_HASH$(1):%=--hash %) || \
	(TMP_REPO=$$$$(mktemp --directory --dry-run) && \
	 $(SVN) export $$(SVN_REPO$(1)) $$(SVN_REV$(1):%=--revision %) \
			$$$${TMP_REPO} && \
	 /usr/gnu/bin/tar --create --file - --absolute-names \
	      --transform="s;$$$${TMP_REPO};$$(COMPONENT_SRC$(1));g" \
	      --bzip2 $$$${TMP_REPO} >$$@ && \
	 $(RM) -rf $$$${TMP_REPO} && \
	 SVN_HASH=$$$$(digest -a sha256 $$@) && \
	 $(GSED) -i \
		-e "s/^SVN_HASH$(1)=.*/SVN_HASH$(1)=  sha256:$$$${SVN_HASH}/" \
		Makefile)

REQUIRED_PACKAGES += developer/versioning/subversion

endif
endif
endef

#
# Define the rules required to download any source archives and augment any
# cleanup macros.
#
$(eval $(call subversion-rules,))
$(foreach suffix, $(SVN_SUFFIXES), $(eval $(call subversion-rules,_$(suffix))))
