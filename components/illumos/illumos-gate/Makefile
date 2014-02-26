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
# Copyright 2013, Andrzej Szeszo
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-gate
COMPONENT_SRC=		$(COMPONENT_NAME)

GIT=git
GIT_REPO=git://github.com/illumos/illumos-gate.git
GIT_BRANCH=master
GIT_CHANGESET=HEAD

NIGHTLY_OPTIONS=-nClmprt
ONNV_BUILDNUM=$(BRANCHID)

COMPONENT_REVISION=$(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)

COMPONENT_ARCHIVE_1=		on-closed-bins-nd.$(MACH).tar.bz2
COMPONENT_ARCHIVE_URL_1= \
    http://dlc.openindiana.org/dlc.sun.com/osol/on/downloads/20100817/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1.i386= \
    sha256:da3ca1ea24972ba6a01169265d8d38a45789ed7cc45334bfe026c108b1d2ff56
COMPONENT_ARCHIVE_HASH_1.sparc= \
    sha256:88b8c4032c1d759abec98e346085e0ba350fa485f28a12ff63f247e4125916e3
COMPONENT_ARCHIVE_HASH_1=	$(COMPONENT_ARCHIVE_HASH_1.$(MACH))

COMPONENT_ARCHIVE_2=		on-closed-bins.$(MACH).tar.bz2
COMPONENT_ARCHIVE_URL_2= \
    http://dlc.openindiana.org/dlc.sun.com/osol/on/downloads/20100817/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2.i386= \
    sha256:18e82bace8481dca62586e4bdff7f6b44fc63b41443799929e4d4b2187e98535
COMPONENT_ARCHIVE_HASH_2.sparc= \
    sha256:ce5425387a61dbf6842f8278771f244d2b860786a9d296b72b61e6721f8b7398
COMPONENT_ARCHIVE_HASH_2=	$(COMPONENT_ARCHIVE_HASH_2.$(MACH))

ON_REPO=$(SOURCE_DIR)/packages/$(MACH)/nightly-nd/repo.redist

CLEAN_PATHS += $(BUILD_DIR)

include ../../../make-rules/prep.mk

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

$(BUILD_DIR)/$(MACH)/.closed-binaries: $(SOURCE_DIR)/.downloaded
	$(MKDIR) $(@D)
	[ -d $(SOURCE_DIR)/closed ] || \
	  (bzip2 -dc $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) | \
	  (cd $(SOURCE_DIR); tar xf -); \
	  bzip2 -dc $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_2) | \
	  (cd $(SOURCE_DIR); tar xf -))
	$(TOUCH) $@

prep:: $(BUILD_DIR)/$(MACH)/.closed-binaries

$(BUILD_DIR)/$(MACH)/.built: $(BUILD_DIR)/$(MACH)/.closed-binaries
	cd $(SOURCE_DIR) && \
	  cat usr/src/tools/env/illumos.sh | \
	  (sed \
	    -e 's|^export NIGHTLY_OPTIONS=.*|export NIGHTLY_OPTIONS=\"$(NIGHTLY_OPTIONS)\"|' \
	    -e 's|^export GATE=.*|export GATE=\"$$(git log -1 --format=illumos-%h)\"|' \
	    -e 's|^export CODEMGR_WS=.*|export CODEMGR_WS=\"$$PWD\"|'; \
	  echo export CW_NO_SHADOW=1; \
	  echo export __GNUC=\"\"; \
	  echo export ONLY_LINT_DEFS=-I\$$SPRO_ROOT/sunstudio12.1/prod/include/lint; \
	  echo export ONNV_BUILDNUM=$(ONNV_BUILDNUM); \
	  echo export PKGVERS_BRANCH=$(ONNV_BUILDNUM)) > \
	  illumos.sh && \
	  time /opt/onbld/bin/nightly illumos.sh
	$(TOUCH) $@

build install: $(BUILD_DIR)/$(MACH)/.built

$(BUILD_DIR)/$(MACH)/.overlay: $(BUILD_DIR)/$(MACH)/.built
	$(MKDIR) $(BUILD_DIR)/$(MACH)/overlay

	$(CP) -RP $(COMPONENT_DIR)/overlay $(BUILD_DIR)/$(MACH)

	# Boot Splash Images
	$(CP) $(BUILD_DIR)/$(MACH)/overlay/boot/splashimage.xpm \
	    $(BUILD_DIR)/$(MACH)/overlay/boot/solaris.xpm || true
	
	# Fix closed lc_core.h header
	# Patch was taken from here https://www.illumos.org/issues/3853

	if ! grep 199711L \
	    $(SOURCE_DIR)/proto/root_$(MACH)/usr/include/sys/lc_core.h \
	    >/dev/null; then \
	    mkdir -p $(BUILD_DIR)/$(MACH)/overlay/usr/include/sys; \
	    cp $(SOURCE_DIR)/proto/root_$(MACH)/usr/include/sys/lc_core.h \
	    $(BUILD_DIR)/$(MACH)/overlay/usr/include/sys/lc_core.h; \
	    (printf "/^struct tm;$/\n-2\na\n#if __cplusplus >= 199711L\nnamespace std {\n#endif\n.\n"; \
	    printf "+2\na\n#if __cplusplus >= 199711L\n}\n#endif /* end of namespace std */\n\n.\nw\nq\n") | \
		ed -s $(BUILD_DIR)/$(MACH)/overlay/usr/include/sys/lc_core.h \
		>/dev/null; \
	fi

	$(TOUCH) $@

$(BUILD_DIR)/$(MACH)/publish.transforms: $(BUILD_DIR)/$(MACH)/.overlay
	echo "<transform set name=pkg.fmri -> edit value pkg://[^/]+/ pkg://$(PUBLISHER)/>" > \
	  $(BUILD_DIR)/$(MACH)/publish.transforms

	echo "<transform set name=pkg.fmri -> edit value ,.+: ,$(BUILD_VERSION):>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms

	echo "<transform set name=pkg.fmri -> emit set name=userland.info.git-remote value=$(USERLAND_GIT_REMOTE)>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri -> emit set name=userland.info.git-branch value=$(USERLAND_GIT_BRANCH)>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri -> emit set name=userland.info.git-rev value=$(USERLAND_GIT_REV)>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms

	echo "<transform set name=pkg.fmri -> emit set name=illumos-gate.info.git-remote value=$(GIT_REPO)>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri -> emit set name=illumos-gate.info.git-branch value=$(GIT_BRANCH)>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri -> emit set name=illumos-gate.info.git-rev value=$(shell cd $(COMPONENT_SRC); git rev-parse HEAD)>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms

	echo "<transform depend fmri=pkg:/driver/network/bnx@.* -> drop>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms

	echo "<transform depend fmri=pkg:/driver/network/bnxe@.* -> drop>" >> \
	  $(BUILD_DIR)/$(MACH)/publish.transforms

	for i in $$(cd $(BUILD_DIR)/$(MACH)/overlay; find . -type f | \
	  cut -c 3- | sort); do \
	  echo "<transform file path=$$i -> set action.hash $$i >" >> \
	    $(BUILD_DIR)/$(MACH)/publish.transforms; \
	  echo "<transform file path=$$i -> delete chash .* >" >> \
	    $(BUILD_DIR)/$(MACH)/publish.transforms; \
	done

$(BUILD_DIR)/$(MACH)/.published: $(BUILD_DIR)/$(MACH)/publish.transforms
	if [ -d $(@D)/pkgrecv.dir ]; then $(RM) -r $(@D)/pkgrecv.dir; fi
	$(MKDIR) $(@D)/pkgrecv.dir

	#pkgrepo -s $(ON_REPO) list -H -F tsv | awk '{ print $2 }' | sort -u
	#pkgrecv -s illumos-gate/packages/i386/nightly-nd/repo.redist --newest
	
	pkgrepo -s $(ON_REPO) rebuild
	pkgrecv -s $(ON_REPO) -d $(@D)/pkgrecv.dir --raw \
	  $$(pkgrecv -s $(ON_REPO) --newest | sed -f packages.ignore)

	for pkg in $$(echo $(@D)/pkgrecv.dir/*/*); do \
	  pkgmogrify -O $$pkg/manifest $$pkg/manifest \
	  $(BUILD_DIR)/$(MACH)/publish.transforms; \
	  pkgsend -s $(WS_REPO) publish --fmri-in-manifest \
	  -d $(BUILD_DIR)/$(MACH)/overlay -d $$pkg $$pkg/manifest; \
	done

	$(TOUCH) $@

.NOTPARALLEL:

publish: update $(BUILD_DIR)/$(MACH)/.published
