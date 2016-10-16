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

FETCH=$(WS_TOOLS)/userland-fetch

GIT=git

#
#
#

CLEAN_PATHS += $(BUILD_DIR)
CLOBBER_PATHS += $(SOURCE_DIR)
CLOBBER_PATHS += $(PROTO_DIR)

#
# Download
#

$(SOURCE_DIR)/.downloaded: 
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	@cd $(SOURCE_DIR); $(GIT) checkout $(GIT_BRANCH); $(GIT) pull \
	  $(GIT_REPO); $(GIT) log -1 --format=%H > .downloaded

download:: $(SOURCE_DIR)/.downloaded

#
# Update
#

$(SOURCE_DIR)/.updated: download
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	cd $(SOURCE_DIR); $(GIT) pull $(GIT_REPO); \
	  [ "$$($(GIT) log -1 --format=%H)" == "$$(cat .downloaded)" ] || \
	  $(GIT) log -1 --format=%H > .downloaded

update:: $(SOURCE_DIR)/.updated

#
# Patch
#

PATCH_DIR ?= patches
PATCH_PATTERN ?= *.patch
PATCHES = $(shell find $(PATCH_DIR) $(PARFAIT_PATCH_DIR) -type f \
                      -name '$(PATCH_PATTERN)' \
                          2>/dev/null | sort) $(EXTRA_PATCHES)

$(SOURCE_DIR)/.patched:	$(SOURCE_DIR)/.downloaded $(PATCHES)
	$(MKDIR) $(@D)
	@cd $(SOURCE_DIR) && \
        $(GIT) checkout -f && \
              $(GIT) clean -f
	@for p in $(PATCHES); do \
          $(GPATCH) -d $(@D) $(GPATCH_FLAGS) < $$p; \
        done
	@cd $(SOURCE_DIR); $(GIT) log -1 --format=%H > .downloaded
	$(TOUCH) $@


patch:: update

#
# Prep
#

$(SOURCE_DIR)/.prep:	download update patch
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::	$(SOURCE_DIR)/.prep

clean::
	$(PRE_CLEAN_ACTION)
	$(RM) -r $(CLEAN_PATHS)

clobber::       clean
	$(RM) -r $(CLOBBER_PATHS)

REQUIRED_PACKAGES+= developer/git
