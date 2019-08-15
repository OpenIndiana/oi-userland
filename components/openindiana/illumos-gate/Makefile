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
# Copyright 2016, Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-gate
COMPONENT_SRC=		$(COMPONENT_NAME)

GIT=git
GIT_REPO=git://github.com/illumos/illumos-gate.git
GIT_BRANCH=master
GIT_CHANGESET=HEAD

FETCH=$(WS_TOOLS)/userland-fetch

DEBUG=no

ifeq ($(DEBUG),yes)
NIGHTLY_OPTIONS=-nCDmpt
else
NIGHTLY_OPTIONS=-nCmpt
endif
ONNV_BUILDNUM=$(BRANCHID)

COMPONENT_REVISION=$(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)

ON_REPO.NON_DEBUG=$(SOURCE_DIR)/packages/$(MACH)/nightly-nd/repo.redist
ON_REPO.DEBUG=$(SOURCE_DIR)/packages/$(MACH)/nightly/repo.redist

CLEAN_PATHS += $(BUILD_DIR)
CLOBBER_PATHS += $(SOURCE_DIR)

ifeq ($(DEBUG),yes)
MULTI_PROTO=yes
else
MULTI_PROTO=no
endif

$(SOURCE_DIR)/.downloaded: 
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

PATCH_DIR ?=    patches
PATCH_PATTERN ?=        *.patch
PATCHES =       $(shell find $(PATCH_DIR) $(PARFAIT_PATCH_DIR) -type f -name '$(PATCH_PATTERN)' \
                                2>/dev/null | sort) $(EXTRA_PATCHES)

$(SOURCE_DIR)/.patched:	$(SOURCE_DIR)/.downloaded $(PATCHES)
	$(MKDIR) $(@D)
	cd $(SOURCE_DIR) && \
	$(GIT) checkout -f && \
	$(GIT) clean -f
	for p in $(PATCHES); do \
	  echo "\nPatch: $$p:"; \
	  $(GPATCH) -d $(@D) $(GPATCH_FLAGS) < $$p; \
	done
	@cd $(SOURCE_DIR); $(GIT) log -1 --format=%H > .downloaded
	$(TOUCH) $@

prep::	$(SOURCE_DIR)/.patched

$(BUILD_DIR)/$(MACH)/.built: $(SOURCE_DIR)/.patched
	$(MKDIR) $(@D)
	cd $(SOURCE_DIR) && \
	  if [ -f tools/nightly ] ; then  \
		cp tools/nightly $(BUILD_DIR)/$(MACH)/nightly ; \
	  else  \
		cp usr/src/tools/scripts/nightly.sh $(BUILD_DIR)/$(MACH)/nightly ; \
	  fi && \
	  chmod u+wx $(BUILD_DIR)/$(MACH)/nightly && \
	  NIGHTLY="$(BUILD_DIR)/$(MACH)/nightly" && \
	  cat usr/src/tools/env/illumos.sh | \
	  (sed \
	    -e 's|^export NIGHTLY_OPTIONS=.*|export NIGHTLY_OPTIONS=\"$(NIGHTLY_OPTIONS)\"|' \
	    -e 's|^export VERSION=.*|export VERSION=\"$$(git log -1 --format=illumos-%h)\"|' \
	    -e 's|^export CODEMGR_WS=.*|export CODEMGR_WS=\"$$PWD\"|' \
	    -e 's|^export ENABLE_SMATCH=.*||' \
	    -e 's|^export ON_CLOSED_BINS=.*|export ON_CLOSED_BINS=\"/opt/onbld/closed\"|' \
	    -e 's|^export MULTI_PROTO=.*|export MULTI_PROTO=\"$(MULTI_PROTO)\"|' \
	    -e 's|^export SHADOW_CCS=.*||' \
	    -e 's|^export SHADOW_CCCS=.*||' ; \
	  echo export PERL_VERSION=\"5.22\"; \
	  echo export PERL_PKGVERS=\"-522\"; \
	  echo export BUILDPY2TOOLS=\"#\"; \
	  echo export BLD_JAVA_8=; \
	  echo export CW_NO_SHADOW=1; \
	  echo export __GNUC=\"\"; \
	  echo export ONLY_LINT_DEFS=-I\$$SPRO_ROOT/sunstudio12.1/prod/include/lint; \
	  echo export ONNV_BUILDNUM=$(ONNV_BUILDNUM); \
	  echo export PKGVERS_BRANCH=$(ONNV_BUILDNUM)) > \
	  illumos.sh && \
	  time $(ENV) -i $${NIGHTLY} illumos.sh
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

	# Drop man pages for sun-solaris perl module to avoid conflicts between different versions
	echo "<transform file path=usr/share/man/man3perl/.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms

	# Drop old obsolete and renamed package dependencies
	echo "<transform depend fmri=pkg:/avs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/BRCMbnx@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/BRCMbnxe@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/consolidation/man/man-incorporation@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/CPQary3@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/benchmark/filebench@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/driver/graphics/drm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/driver/network/arbel@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/driver/network/ibd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/driver/network/llc2@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/driver/network/qlc/qlc-mdb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/locale/ar-extra@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/network/iscsi@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/network/iscsi/target/legacy@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/service/network/snmp/mibiisa@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/source/network/pppdump@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/source/security/tcp-wrapper@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/storage-nas@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/storage-server@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNW0on@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNW1394@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNW1394h@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaac@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWacc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWad810@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWadixp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWadpu320@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWafe@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWagp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWagph@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWahci@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWamd8111s@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWamr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWamt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWapct@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWarbel@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWarc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWarcmsr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWarn@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWastdev@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWatfs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWatge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWatheros@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWatigfx@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWatu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWauda@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudf@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudh@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudiocmi@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudioemu10k@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudiohd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudiols@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudiop16x@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudiosolo@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudiovia97@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWaudit@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWav1394@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbart@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbcmsata@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbeadm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbfe@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbip@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbnu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbridge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWbtool@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcakr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcakrx@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcar@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcarx@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcdrw@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcfcl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcfpl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWchxge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWckr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcnetr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcns@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcpc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcpcu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcpr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcsl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWcstl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdcaf@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdcopy@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdfb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdfbh@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdhcm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdhcs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdhcsb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdmfe@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdmgt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdoc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdpl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdrmr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdsd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdtrc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdtrp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWdtrt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWemlxs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWesu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfchba@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfcip@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfcmdb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfcoe@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfcoei@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfcoet@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfcoeu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfcp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfcprt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfcsm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfctl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfilebench@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfipe@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfmd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfruid@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfruip@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfss@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWftdu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWftp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfwdc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfwdcu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWfwflash@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWgrub@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWgrubS@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWgss@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWgssc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWgssdh@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWgssk@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWhal@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWhea@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWhermon@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWhmd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWhwdata@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWhxge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWib@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWibdma@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWibsdp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWibsdpib@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWibsdpu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWigb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWii@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWilb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWima@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWimac@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWinstallint@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWintgige@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWio-tools@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWiot@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWipc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWipf@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWipfh@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWipoib@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWippcore@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWippl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWipw@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWiscsi@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWiscsidm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWiscsit@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWiscsitgt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWisns@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWiwh@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWiwi@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWiwk@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWiwp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWixgb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWixgbe@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWkdc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWkey@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWkrb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWkvm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWlatencytop@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWldskint@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWlibm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWlibms@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWlibsasl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWllc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWlldap@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWloc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWlp-cmds@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWlpr-cmds@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWlsimega@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWluxop@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWlx@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWman@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmda@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmdb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmdbdm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmddr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmegasas@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmibii@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmms@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmpapi@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmpathadm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmpsvplr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmptsas@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmrsas@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmv88sx@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmwl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmxfe@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWmyri10ge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnca@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWndmp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnetcat@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnfsc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnfsckr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnfss@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnfsskr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnis@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWntfsprogs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWntxn@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnvsata@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWnxge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWonbld@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWonfmes@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWonzfs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWos86r@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWosdem@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpacket@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpapi@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWparted@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpcan@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpcelx@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpcmci@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpcmcu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpcmem@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpcser@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpcwl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpicl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpiclh@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpkgcmds@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpl5p@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpl5u@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpl5v@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpmcs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpolkit@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpool@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpoold@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpowertop@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWppm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpppd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpppdt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpppg@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpppgS@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWps@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpsdcr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpsdir@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpsdpr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpsf@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpsh@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpsm-ipp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWpsm-lpd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWqlc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWqlcu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWqos@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWqosu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWralink@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrcap@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrcmdc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrcmds@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrdc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrds@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrmod@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrmodr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrmodu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrmvolmgr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrmwb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWroute@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrpcib@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrsg@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrsgk@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrsm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrsmo@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrtls@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrtw@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrum@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrwd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWrwn@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWs10brand@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsacom@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsasnm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsbp2@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWscm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWscp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWscplp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWscsa1394@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWscsip@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsdcard@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWses@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsfe@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsi3124@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWslp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsmapi@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsmbfs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsmbfskr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsmbs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsmbskr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsmedia@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsmhba@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsmpd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsn1int@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsndm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWspnego@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWspsv@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsra@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsrh@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsrpt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWssh@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsshcu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWsshd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWstmf@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtavor@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtcpd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtcpdS@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtecla@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWter@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtftp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtnetc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtnetd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtnfc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtnfd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtoo@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtpm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWts@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWtsg@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWuacm@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWuath@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWucbt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWudapl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWudaplt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWudf@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWuedg@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWuftdi@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWugen@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWugenu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWuksp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWukspfw@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWuprl@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWural@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWurtw@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWusb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWusbs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWusbu@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWusbvc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWuwb@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWvia823x@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWvr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWvrrp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWvscan@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWvscankr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWwbint@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWwbsup@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWwlan@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWwpa@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWwpi@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWxcu4@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWxcu6@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWxdt@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWxge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWxsvc@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWxvmipa@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWxvmpv@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWxwdv@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWyge@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWyp@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWzfs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWzfskr@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWzone@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWzoneint@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/SUNWzyd@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/dtrace@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/file-system/ntfsprogs@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/library/security/crypto/pkcs11_kms@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/library/storage/scsi-plugin@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/management/snmp/sea@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/management/wbem/resource-management@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/manual@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/storage/mms@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/storage/parted@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend fmri=pkg:/system/zones/brand/lx@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms

	# Needed for MTA replacement
	echo "<transform depend type=require fmri=pkg:/service/network/smtp/sendmail@.* -> emit depend type=require fmri=pkg:/system/mta>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend type=require fmri=pkg:/service/network/smtp/sendmail@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend type=require fmri=service/network/smtp/sendmail -> emit depend type=require fmri=pkg:/system/mta>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend type=require fmri=service/network/smtp/sendmail -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms

	# We want to replace dependency on particular agpart version, but preserve dependency on any version
	echo "<transform depend type=require fmri=pkg:/driver/graphics/agpgart@.* -> emit depend type=require fmri=pkg:/driver/graphics/agpgart>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend type=require fmri=pkg:/driver/graphics/agpgart@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms

	# Fix pkgdepend issue with GCC 7 runtime (https://www.illumos.org/issues/11255)
	echo "<transform depend type=require-any fmri=pkg:/system/library/gcc-\d+-runtime@.* -> emit depend type=require fmri=pkg:/system/library/gcc-7-runtime>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend type=require-any fmri=pkg:/system/library/gcc-\d+-runtime@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend type=require-any fmri=pkg:/system/library/g\+\+-\d+-runtime@.* -> emit depend type=require fmri=pkg:/system/library/g++-7-runtime> " >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform depend type=require-any fmri=pkg:/system/library/g\+\+-\d+-runtime@.* -> drop>" >> $(BUILD_DIR)/$(MACH)/publish.transforms

	# Loader branding
	echo "<transform set name=pkg.fmri value=pkg://[^/]*/system/boot/loader@.* -> emit file path=boot/loader.conf group=sys mode=0644 owner=root preserve=true>" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri value=pkg://[^/]*/system/boot/loader@.* -> emit file path=boot/forth/brand-hipster.4th group=sys mode=0444 owner=root >" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri value=pkg://[^/]*/system/boot/loader@.* -> emit file path=boot/forth/logo-openindiana.4th group=sys mode=0444 owner=root >" >> $(BUILD_DIR)/$(MACH)/publish.transforms

	for i in $$(cd $(BUILD_DIR)/$(MACH)/overlay; find . -type f | \
	  cut -c 3- | sort); do \
	  echo "<transform file path=$$i -> set action.hash $$i >" >> \
	    $(BUILD_DIR)/$(MACH)/publish.transforms; \
	  echo "<transform file path=$$i -> delete chash .* >" >> \
	    $(BUILD_DIR)/$(MACH)/publish.transforms; \
	done

$(BUILD_DIR)/$(MACH)/.published: $(BUILD_DIR)/$(MACH)/publish.transforms
	$(RM) -r $(@D)/pkgrecv.dir
	$(MKDIR) $(@D)/pkgrecv.dir

ifeq ($(DEBUG),yes)
	$(RM) -r $(@D)/pkgrepo-merged.dir
	$(MKDIR) $(@D)/pkgrepo-merged.dir
	pkgrepo -s $(@D)/pkgrepo-merged.dir create

	pkgmerge -d $(@D)/pkgrepo-merged.dir \
		-s variant.debug.illumos=true,$(ON_REPO.DEBUG) \
		-s variant.debug.illumos=false,$(ON_REPO.NON_DEBUG)

	pkgrepo -s $(@D)/pkgrepo-merged.dir rebuild
	pkgrecv -s $(@D)/pkgrepo-merged.dir -d $(@D)/pkgrecv.dir --raw \
	  $$(pkgrecv -s $(@D)/pkgrepo-merged.dir --newest | sed -f packages.ignore)
else
	pkgrepo -s $(ON_REPO.NON_DEBUG) rebuild
	pkgrecv -s $(ON_REPO.NON_DEBUG) -d $(@D)/pkgrecv.dir --raw \
	  $$(pkgrecv -s $(ON_REPO.NON_DEBUG) --newest | sed -f packages.ignore)
endif

	for pkg in $$(echo $(@D)/pkgrecv.dir/*/*); do \
	  pkgmogrify -O $$pkg/manifest $$pkg/manifest \
	  $(BUILD_DIR)/$(MACH)/publish.transforms; \
	  pkgsend -s $(WS_REPO) publish --fmri-in-manifest \
	  -d $(BUILD_DIR)/$(MACH)/overlay -d $$pkg $$pkg/manifest; \
	done

	$(TOUCH) $@

.NOTPARALLEL:

publish: update $(BUILD_DIR)/$(MACH)/.published

clean::
	$(RM) -r $(CLEAN_PATHS)

clobber::       clean
	$(RM) -r $(CLOBBER_PATHS)

REQUIRED_PACKAGES += developer/gcc-7
REQUIRED_PACKAGES += developer/illumos-closed
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
