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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#

CVS=$(WS_TOP)/tools/proxy_cvs

#
# Anything that we pull from a CVS repo must have a CVS_REPO{_[0-9]+} and
# CVS_TAG{_[0-9]+} to match.
#

CVS_SUFFIXES = $(subst CVS_REPO_,, $(filter CVS_REPO_%, $(.VARIABLES)))

define cvs-rules
ifdef CVS_REPO$(1)
ifdef CVS_PATH$(1)
ifdef CVS_TAG$(1)

COMPONENT_SRC$(1) = $(COMPONENT_NAME)-$(COMPONENT_VERSION)-$$(CVS_TAG$(1))
COMPONENT_ARCHIVE$(1) = $$(COMPONENT_SRC$(1)).tar.bz2

CLEAN_PATHS += $$(COMPONENT_SRC$(1))
CLOBBER_PATHS += $$(COMPONENT_ARCHIVE$(1))
SOURCE_DIR$(1) = $$(COMPONENT_DIR)/$(COMPONENT_SRC$(1))

download::	$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1))

# First attempt to download a cached archive of the CVS repo at the proper
# CVS tag.  If that fails, create an archive by cloning the CVS repo,
# updating to the selected tag, archiving that directory, and cleaning up
# when complete.
$$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1)):	$(MAKEFILE_PREREQ)
	$$(FETCH) --file $$@ $$(CVS_HASH$(1):%=--hash %) || \
	(TMP_REPO=$$$$(mktemp --directory ./cvs.XXXXXX) && \
	 $(CVS) -qd $$(CVS_REPO$(1)) get $$(CVS_TAG$(1):%=-r%) -d $$$${TMP_REPO} $$(CVS_PATH$(1)) && \
	/usr/gnu/bin/tar --create --file - --absolute-names \
	      --transform="s;$$$${TMP_REPO};$$(COMPONENT_SRC$(1));g" \
	      --bzip2 $$$${TMP_REPO} >$$@ && \
	 $(RM) -rf $$$${TMP_REPO} && \
	 CVS_HASH=$$$$(digest -a sha256 $$@) && \
	 $(GSED) -i \
		-e "s/^CVS_HASH$(1)=.*/CVS_HASH$(1)=  sha256:$$$${CVS_HASH}/" \
		Makefile)

REQUIRED_PACKAGES += developer/versioning/cvs

endif
endif
endif
endef

#
# Define the rules required to download any source archives and augment any
# cleanup macros.
#
$(eval $(call cvs-rules,))
$(foreach suffix, $(CVS_SUFFIXES), $(eval $(call cvs-rules,_$(suffix))))
