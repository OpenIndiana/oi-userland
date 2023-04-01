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
# Copyright 2014 Alexander Pyhalov. All rights reserved.
# Copyright 2023 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		slim_source
COMPONENT_SRC=		$(COMPONENT_NAME)

COMPONENT_REVISION=$(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)

GIT=git
GIT_REPO=https://github.com/OpenIndiana/slim_source.git
GIT_BRANCH=oi/hipster
GIT_CHANGESET=HEAD
NIGHTLY_OPTIONS=-AWndmp +t
DMAKE=/usr/bin/dmake
ONNV_BUILDNUM=$(BRANCHID)

PKG_REPO=$(SOURCE_DIR)/packages/$(MACH)/nightly-nd/repo.redist

CLEAN_PATHS += $(BUILD_DIR)

COMPONENT_PREP_GIT=no
include $(WS_MAKE_RULES)/prep.mk

$(SOURCE_DIR)/.downloaded: $(ARCHIVES:%=$(USERLAND_ARCHIVES)%)
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	@cd $(SOURCE_DIR); $(GIT) checkout $(GIT_BRANCH); $(GIT) pull \
	  $(GIT_REPO); $(GIT) log -1 --format=%H > .downloaded

update:
	@[ -d $(SOURCE_DIR) ] || \
	$(GIT) clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)
	cd $(SOURCE_DIR); $(GIT) pull $(GIT_REPO); \
	  [ "$$($(GIT) log -1 --format=%H)" == "$$(cat .downloaded)" ] || \
	  $(GIT) log -1 --format=%H > .downloaded

download:: $(SOURCE_DIR)/.downloaded

$(BUILD_DIR)/$(MACH)/.built: $(SOURCE_DIR)/.downloaded Makefile
	$(MKDIR) $(@D) && \
        cd $(SOURCE_DIR) && \
	cp usr/src/tools/env/nightly $(BUILD_DIR)/$(MACH)/nightly && \
	chmod u+wx $(BUILD_DIR)/$(MACH)/nightly && \
	NIGHTLY="$(BUILD_DIR)/$(MACH)/nightly" && \
        cat usr/src/tools/env/developer.sh | \
          (sed \
            -e 's|^export NIGHTLY_OPTIONS=.*|export NIGHTLY_OPTIONS=\"$(NIGHTLY_OPTIONS)\"|' \
            -e 's|^export GATE=.*|export GATE=\"$$(git log -1 --format=illumos-%h)\"|' \
            -e 's|^export CODEMGR_WS=.*|export CODEMGR_WS=\"$$PWD\"|'; \
          echo export VERIFY_ELFSIGN=n; \
          echo export LC_ALL=en_US.UTF-8; \
          echo export CW_NO_SHADOW=1; \
          echo export SPRO_ROOT=; \
          echo export ON_CLOSED_BINS=/tmp; \
          echo export CC=$(CC); \
          echo export MAKE=$(DMAKE); \
          echo export ONNV_BUILDNUM=$(ONNV_BUILDNUM); \
          echo export PKGVERS_BRANCH=$(ONNV_BUILDNUM)) > \
          developer.sh && \
        time $${NIGHTLY} developer.sh &&\
	$(TOUCH) $@

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

print-package-names:
	if test -d $(PKG_REPO); \
	then pkgrepo list -H -F tsv -s $(PKG_REPO) | cut -f 2 | sort -u > pkg5.fmris; fi; \
	cat pkg5.fmris

PACKAGE_NAMES  = consolidation/install/install-incorporation
PACKAGE_NAMES += consolidation/install/install-redistributable
PACKAGE_NAMES += install/distribution-constructor
PACKAGE_NAMES += install/installadm
PACKAGE_NAMES += SUNWauto-install-common
PACKAGE_NAMES += SUNWauto-install
PACKAGE_NAMES += SUNWdistro-const
PACKAGE_NAMES += SUNWgui-install
PACKAGE_NAMES += SUNWinstall-libs
PACKAGE_NAMES += SUNWinstall-test
PACKAGE_NAMES += SUNWinstall
PACKAGE_NAMES += SUNWinstalladm-tools
PACKAGE_NAMES += SUNWslim-utils
PACKAGE_NAMES += system/install
PACKAGE_NAMES += system/install/auto-install
PACKAGE_NAMES += system/install/auto-install/auto-install-common
PACKAGE_NAMES += system/install/gui-install
PACKAGE_NAMES += system/install/media/internal
PACKAGE_NAMES += system/install/tests
PACKAGE_NAMES += system/install/text-install
PACKAGE_NAMES += system/library/install

# Build dependencies
REQUIRED_PACKAGES += library/desktop/libglade
REQUIRED_PACKAGES += system/install/text-install
REQUIRED_PACKAGES += system/library/install/libinstzones
REQUIRED_PACKAGES += system/library/storage/ima/header-ima
REQUIRED_PACKAGES += system/zones/internal
