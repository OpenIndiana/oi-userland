#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Adam Stevko. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkg
COMPONENT_SRC=		$(COMPONENT_NAME)

GIT=git
GIT_REPO=git://github.com/OpenIndiana/pkg5.git
GIT_BRANCH=oi
GIT_CHANGESET=HEAD

MAKE=/usr/bin/make

# BRANCHID is defined in make-rules/ips-buildinfo.mk
PKG_BUILDNUM=$(BRANCHID)

PKG_REPO=$(SOURCE_DIR)/packages/$(MACH)/repo

CLEAN_PATHS += $(BUILD_DIR)

include $(WS_TOP)/make-rules/prep.mk

#export CC 

$(SOURCE_DIR)/.downloaded: $(ARCHIVES:%=$(USERLAND_ARCHIVES)%)
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	@cd $(SOURCE_DIR); $(GIT) checkout $(GIT_BRANCH); $(GIT) pull \
	  $(GIT_REPO); $(GIT) log -1 --format=%H > .downloaded

update:
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	cd $(SOURCE_DIR); $(GIT) pull $(GIT_REPO); \
	  [ $$($(GIT) log -1 --format=%H) == $$(cat .downloaded) ] || \
	  $(GIT) log -1 --format=%H > .downloaded

download:: $(SOURCE_DIR)/.downloaded

$(BUILD_DIR)/$(MACH)/.built: $(SOURCE_DIR)/.downloaded 
	$(MKDIR) $(@D) && \
	cd $(SOURCE_DIR)/src && \
	$(MAKE) && $(MAKE) install && \
	cd pkg && \
	$(MAKE) PKGVERS=$(PKG_BUILDNUM) && \
	$(MAKE) publish-pkgs PKGVERS=$(PKG_BUILDNUM) && \
	$(MAKE) repository-metadata && \
	$(TOUCH) $@

build install: $(BUILD_DIR)/$(MACH)/.built

$(BUILD_DIR)/$(MACH)/publish.transforms: $(BUILD_DIR)/$(MACH)/.built
	echo "<transform set name=pkg.fmri -> edit value pkg://[^/]+/ pkg://$(PUBLISHER)/>" > \
	  $(BUILD_DIR)/$(MACH)/publish.transforms

$(BUILD_DIR)/$(MACH)/.published: $(BUILD_DIR)/$(MACH)/publish.transforms
	if [ -d $(@D)/pkgrecv.dir ]; then $(RM) -r $(@D)/pkgrecv.dir; fi
	$(MKDIR) $(@D)/pkgrecv.dir

	pkgrecv -s $(PKG_REPO) -d $(@D)/pkgrecv.dir --raw \
	  $$(pkgrecv -s $(PKG_REPO) --newest)

	for pkg in $$(echo $(@D)/pkgrecv.dir/*/*); do \
	  pkgmogrify -O $$pkg/manifest $$pkg/manifest \
	  $(BUILD_DIR)/$(MACH)/publish.transforms; \
	  pkgsend -s $(WS_REPO) publish --fmri-in-manifest \
	  -d $(BUILD_DIR)/$(MACH)/overlay -d $$pkg $$pkg/manifest; \
	done

	$(TOUCH) $@

publish: $(BUILD_DIR)/$(MACH)/.published
