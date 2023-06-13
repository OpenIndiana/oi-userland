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

COMPONENT_REVISION=$(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)

GIT=git
GIT_REPO=https://github.com/OpenIndiana/pkg5.git
GIT_BRANCH=oi
GIT_CHANGESET=HEAD

MAKE=/usr/bin/make

PKG_REPO=$(SOURCE_DIR)/packages/$(MACH)/repo

DEVBOOK=$(SOURCE_DIR)/proto/dev-guide/book.pdf

CLEAN_PATHS += $(BUILD_DIR)

COMPONENT_PREP_GIT=no
include $(WS_TOP)/make-rules/prep.mk

$(SOURCE_DIR)/.downloaded: component-environment-prep $(ARCHIVES:%=$(USERLAND_ARCHIVES)%)
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
	PATH=$(PATH) $(MAKE) && PATH=$(PATH) $(MAKE) install && \
	cd pkg && \
	$(MAKE) BUILD_VERSION=$(BUILD_VERSION) && \
	$(MAKE) publish-pkgs BUILD_VERSION=$(BUILD_VERSION) && \
	$(MAKE) repository-metadata && \
	$(TOUCH) $@

# Target to generate developer's guide
devbook: $(DEVBOOK)

$(DEVBOOK): $(SOURCE_DIR)/.downloaded
	cd $(SOURCE_DIR)/doc/dev-guide && \
	$(MAKE)

build install: $(BUILD_DIR)/$(MACH)/.built

$(BUILD_DIR)/$(MACH)/publish.transforms: $(BUILD_DIR)/$(MACH)/.built
	echo "<transform set name=pkg.fmri -> edit value pkg://[^/]+/ pkg://$(PUBLISHER)/>" > \
	  $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri -> edit value ,.+: ,$(BUILD_VERSION):>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri -> emit set name=pkg5.info.git-remote value=$(GIT_REPO)>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri -> emit set name=pkg5.info.git-branch value=$(GIT_BRANCH)>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri -> emit set name=pkg5.info.git-rev value=$(shell cd $(COMPONENT_SRC); git rev-parse HEAD)>" >> \
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

.NOTPARALLEL:

publish: update $(BUILD_DIR)/$(MACH)/.published

PACKAGE_NAMES  = consolidation/ips/ips-incorporation
PACKAGE_NAMES += consolidation/ips/ips-message-files
PACKAGE_NAMES += developer/opensolaris/pkg5
PACKAGE_NAMES += package/pkg
PACKAGE_NAMES += package/pkg/depot
PACKAGE_NAMES += package/pkg/package-manager
PACKAGE_NAMES += package/pkg/system-repository
PACKAGE_NAMES += package/pkg/update-manager
PACKAGE_NAMES += package/pkg/zones-proxy
PACKAGE_NAMES += system/zones/brand/ipkg
PACKAGE_NAMES += system/zones/brand/kvm
PACKAGE_NAMES += system/zones/brand/nlipkg

# Manually added dependencies
REQUIRED_PACKAGES += developer/opensolaris/pkg5
REQUIRED_PACKAGES += system/zones/internal
REQUIRED_PACKAGES += library/python/cherrypy-39
REQUIRED_PACKAGES += library/python/python-rapidjson-39
REQUIRED_PACKAGES += library/python/jsonschema-39
REQUIRED_PACKAGES += library/python/jsonrpclib-pelix-39
