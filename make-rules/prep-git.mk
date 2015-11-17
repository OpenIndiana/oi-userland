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

GIT =		/usr/bin/git

#
# Anything that we pull from a GIT repo must have a GIT_REPO{_[0-9]+} and
# GIT_COMMIT_ID{_[0-9]+} to match.
#

GIT_SUFFIXES = $(subst GIT_REPO_,, $(filter GIT_REPO_%, $(.VARIABLES)))

define git-rules
ifdef GIT_REPO$(1)
ifdef GIT_COMMIT_ID$(1)

COMPONENT_SRC$(1) ?= $$(COMPONENT_NAME$(1))-$$(GIT_COMMIT_ID$(1))
COMPONENT_ARCHIVE$(1) ?= $$(COMPONENT_SRC$(1)).tar.gz

CLEAN_PATHS += $$(COMPONENT_SRC$(1))
CLOBBER_PATHS += $$(COMPONENT_ARCHIVE$(1))
SOURCE_DIR$(1) = $$(COMPONENT_DIR)/$(COMPONENT_SRC$(1))

download::	$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1))

# First attempt to download a cached archive of the SCM repo at the proper
# changeset ID.  If that fails, create an archive by cloning the SCM repo,
# updating to the selected changeset, archiving that directory, and cleaning up
# when complete.
$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1)):	$(MAKEFILE_PREREQ)
	$$(FETCH) --file $$@ $$(GIT_HASH$(1):%=--hash %) || \
	(TMP_REPO=$$$$(mktemp --directory) && \
	 $(GIT) clone $$(GIT_REPO$(1)) $$$${TMP_REPO} && \
	 (cd $$$${TMP_REPO} ; $(GIT) checkout \
		 $$(GIT_COMMIT_ID$(1))) && \
	 (cd $$$${TMP_REPO} ; $(GIT) archive --format tar.gz \
		--prefix $$(COMPONENT_SRC$(1))/ \
		$$(GIT_COMMIT_ID$(1))) > $$@ && \
	 $(RM) -r $$$${TMP_REPO} && \
	 GIT_HASH=$$$$(digest -a sha256 $$@) && \
	 $(GSED) -i \
		-e "s/^GIT_HASH$(1)=.*/GIT_HASH$(1)=  sha256:$$$${GIT_HASH}/" \
		Makefile)


REQUIRED_PACKAGES += developer/versioning/git

endif
endif
endef

#
# Define the rules required to download any source archives and augment any
# cleanup macros.
#
$(eval $(call git-rules,))
$(foreach suffix, $(GIT_SUFFIXES), $(eval $(call git-rules,_$(suffix))))
