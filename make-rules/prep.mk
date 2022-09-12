
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
# Copyright (c) 2010, 2015, Oracle and/or its affiliates. All rights reserved.
#


####### Collect relevant suffixes, using regexes:
#
# Anything that we pull from a Mercurial repo must have a HG_REPO{_[0-9]+} and
# HG_REV{_[0-9]+} to match.
#
#
# Anything that we pull from a GIT repo must have a GIT_REPO{_[0-9]+} and
# GIT_COMMIT_ID{_[0-9]+} to match.
#
#
# Anything that we pull from a Subversion repo must have a SVN_REPO{_[0-9]+} and
# SVN_REV{_[0-9]+} to match.
#
#
# Anything that we downloaded and want to unpack must have a
# COMPONENT_ARCHIVE{_[0-9]+} macro.
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
#
# Anything that we pull from a GIT repo must have a GIT_REPO{_[0-9]+} and
# GIT_COMMIT_ID{_[0-9]+} to match.
#

URL_SUFFIXES=
PCK_SUFFIXES=
SVN_SUFFIXES=
GIT_SUFFIXES=
HG_SUFFIXES=
GIT_SUFFIXES=

ARCHIVE_NOISE= COMPONENT_ARCHIVE_URL_% COMPONENT_ARCHIVE_HASH_%

define scan-suffix
GIT_SUFFIXES += $$(subst GIT_REPO_,, $$(filter GIT_REPO_%, $(1)))
URL_SUFFIXES += $$(subst COMPONENT_ARCHIVE_URL_,, \
		$$(filter COMPONENT_ARCHIVE_URL_%, $(1)))
PCK_SUFFIXES += $$(subst COMPONENT_ARCHIVE_,, \
                $$(filter COMPONENT_ARCHIVE_%, $$(filter-out $(ARCHIVE_NOISE),$(1))))
SVN_SUFFIXES += $$(subst SVN_REPO_,, $$(filter SVN_REPO_%, $(1)))
GIT_SUFFIXES += $$(subst GIT_REPO_,, $$(filter GIT_REPO_%, $(1)))
HG_SUFFIXES  += $$(subst HG_REPO_,,  $$(filter HG_REPO_%, $(1)))
endef

SUFFIXED_VARS=$(strip $(shell echo '$(.VARIABLES)' | tr ' ' $$'\n' | sed -E 's/ /$$\n/g;/_[0-9]+$$/!d' --))
$(foreach var, $(SUFFIXED_VARS),$(eval $(call scan-suffix,$(var))))

####### New SOURCE_DIR stuff
# SOURCE_DIR must be set somewhere in the Makefile, prep.mk, or the prep-x.mk
# files. All included prep-x.mk methods set SOURCE_DIR, unless COMPONENT_PREP_x is not "yes".
#
# Every prep_*.mk file sets SOURCE_DIR, CLEAN_PATHS, and CLOBBER_PATHS the same way.
# These should be set here instead - this also allows us to override SOURCE_DIR in one place.
# 
# So, instead of doing it for each prep-x.mk file (and making it impossible to override),
# we set it here, conditionally.
#
# If SOURCE_DIR is defined in the Makefile, it must be COMPONENT_DIR-relative,
# and not contain '..', to keep from cleaning unexpected directories. The directory
# is changed to absolute in this template.

CLOBBER_PATHS += $(HASH_DIR)
define set-variables
ifneq (,$$(strip $$(COMPONENT_SRC$(1))))
SOURCE_DIR$(1) ?= $$(COMPONENT_SRC$(1))
ifneq,(,$$(strip $(1)))
COMPONENT_DOWNLOAD_BASE$(1) ?= $$(COMPONENT_DOWNLOAD_BASE)
endif
CLEAN_PATHS += $$(SOURCE_DIR$(1))
ifneq ($$(strip \
$$(filter yes,$$(patsubst ../%,yes,$$(SOURCE_DIR$(1)))) \
$$(filter yes,$$(patsubst   /%,yes,$$(SOURCE_DIR$(1)))) \
$$(filter yes,$$(subst /../,yes,$$(findstring /../, $$(SOURCE_DIR$(1))))) \
),)
$$(warning SOURCE_DIR was $$(SOURCE_DIR$(1)) )
$$(warning SOURCE_DIR gets routinely deleted, and if set wrong, this could cause damage.)
$$(error Please don't use absolute paths or '..' in SOURCE_DIR. )
endif
SOURCE_DIR$(1) := $$(COMPONENT_DIR)/$$(COMPONENT_SRC$(1))
endif
ifneq (,$$(strip $$(COMPONENT_ARCHIVE$(1))))
CLOBBER_PATHS += $$(USERLAND_ARCHIVES)$$(COMPONENT_ARCHIVE$(1))
endif
endef


$(eval $(call set-variables,))
$(foreach suffix\
,$(HG_SUFFIXES) $(GIT_SUFFIXES) $(SVN_SUFFIXES) $(PCK_SUFFIXES),\
$(eval $(call set-variables,_$(suffix))))


include $(WS_MAKE_RULES)/prep-download.mk
include $(WS_MAKE_RULES)/prep-hg.mk
include $(WS_MAKE_RULES)/prep-git.mk
include $(WS_MAKE_RULES)/prep-svn.mk

include $(WS_MAKE_RULES)/prep-unpack.mk
include $(WS_MAKE_RULES)/prep-patch.mk

download::

unpack::	download

patch::		unpack

$(SOURCE_DIR)/.prep:	component-environment-prep download unpack patch
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::	$(SOURCE_DIR)/.prep

clean::
	$(PRE_CLEAN_ACTION)
	$(RM) -r $(CLEAN_PATHS)

clobber::	clean
	$(RM) -r $(CLOBBER_PATHS)
