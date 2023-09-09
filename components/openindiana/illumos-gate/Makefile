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
GIT_REPO=https://github.com/illumos/illumos-gate.git
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

$(SOURCE_DIR):
	$(GIT) -c fetch.fsckobjects=false \
	    clone -b $(GIT_BRANCH) $(GIT_REPO) $(SOURCE_DIR)

$(SOURCE_DIR)/.downloaded:  $(SOURCE_DIR)
	@cd $(SOURCE_DIR); $(GIT) checkout $(GIT_BRANCH); $(GIT) pull \
	  $(GIT_REPO); $(GIT) log -1 --format=%H > .downloaded

update: $(SOURCE_DIR)
	cd $(SOURCE_DIR); $(GIT) pull $(GIT_REPO); \
	  [ "$$($(GIT) log -1 --format=%H)" == "$$(cat .downloaded)" ] || \
	  $(GIT) log -1 --format=%H > .downloaded

download:: $(SOURCE_DIR)/.downloaded

PATCH_DIR ?=    patches
PATCH_PATTERN ?=        *.patch
PATCHES =       $(shell find $(PATCH_DIR) -type f -name '$(PATCH_PATTERN)' \
                                2>/dev/null | sort)

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
	  echo export PERL_VERSION=\"$(PERL_VERSION)\"; \
	  echo export PERL_VARIANT=\"-thread-multi\" ; \
	  echo export PERL_PKGVERS=\"-$(subst .,,$(PERL_VERSION))\"; \
	  echo export BUILDPERL32=\"#\"; \
	  echo export BLD_JAVA_8=; \
	  echo export CW_NO_SHADOW=1; \
	  echo export __GNUC=\"\"; \
	  echo export ONNV_BUILDNUM=$(ONNV_BUILDNUM); \
	  echo export PKGVERS_BRANCH=$(ONNV_BUILDNUM); \
	  echo export BOOTBANNER1=\"$(DISTRIBUTION_NAME) $(DISTRIBUTION_VERSION) Version ^v ^w-bit\") > \
	  illumos.sh && \
	  time $(ENV) -i ./usr/src/tools/scripts/nightly illumos.sh
	$(TOUCH) $@

build install: $(BUILD_DIR)/$(MACH)/.built

$(BUILD_DIR)/$(MACH)/.overlay: $(BUILD_DIR)/$(MACH)/.built
	$(MKDIR) $(BUILD_DIR)/$(MACH)/overlay

	$(CP) -RP $(COMPONENT_DIR)/overlay $(BUILD_DIR)/$(MACH)

	# Boot Splash Images
	$(CP) $(BUILD_DIR)/$(MACH)/overlay/boot/splashimage.xpm \
	    $(BUILD_DIR)/$(MACH)/overlay/boot/solaris.xpm || true

	$(TOUCH) $@

$(BUILD_DIR)/$(MACH)/publish.transforms: packages.ignore.in $(BUILD_DIR)/$(MACH)/.overlay
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
	echo "<transform set name=pkg.fmri value=pkg://[^/]*/system/boot/loader@.* -> emit file path=boot/openindiana.png group=sys mode=0444 owner=root >" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri value=pkg://[^/]*/system/boot/loader@.* -> emit file path=boot/forth/brand-hipster.4th group=sys mode=0444 owner=root >" >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo "<transform set name=pkg.fmri value=pkg://[^/]*/system/boot/loader@.* -> emit file path=boot/forth/logo-openindiana.4th group=sys mode=0444 owner=root >" >> $(BUILD_DIR)/$(MACH)/publish.transforms

	# Settings for tagged pointers
	echo "<transform set name=pkg.fmri value=pkg://[^/]*/system/kernel@.* -> emit file path=etc/system.d/reserve_bits_for_tagged_pointers group=sys mode=0644 owner=root preserve=true>" >> $(BUILD_DIR)/$(MACH)/publish.transforms

	# Fix dependencies on renamed runtime/java and runtime/java/runtime64 packages
	echo '<transform depend fmri=runtime/java$$ -> set fmri runtime/java/openjdk8>' >> $(BUILD_DIR)/$(MACH)/publish.transforms
	echo '<transform depend fmri=runtime/java/runtime64$$ -> set fmri runtime/java/openjdk8>' >> $(BUILD_DIR)/$(MACH)/publish.transforms

	# Drop dependency on ignored packages
	$(GSED) -e 's|^\(.*\)$$|<transform depend fmri=pkg:/\1@.* -> drop>|' $< >> $@

	# Handle overlay files
	for i in $$(cd $(BUILD_DIR)/$(MACH)/overlay; find . -type f | \
	  cut -c 3- | sort); do \
	  echo "<transform file path=$$i -> set action.hash $$i >" >> \
	    $(BUILD_DIR)/$(MACH)/publish.transforms; \
	  echo "<transform file path=$$i -> delete chash .* >" >> \
	    $(BUILD_DIR)/$(MACH)/publish.transforms; \
	done

#
# Generate the sed script for ignoring packages by fully qualified FMRI from a
# list of bare package names (without publisher or version information, etc).
# The list of FMRIs to ignore is also useful for other things, and is easier to
# use when not phrased directly as a sed script.
#
$(BUILD_DIR)/$(MACH)/packages.ignore: packages.ignore.in
	$(MKDIR) $(@D)
	sed -e 's,/,\\/,g' -e 's,.*,/^pkg:\\/\\/on-nightly\\/&@.*/d,' $< > $@

packages.ignore: $(BUILD_DIR)/$(MACH)/packages.ignore

$(BUILD_DIR)/$(MACH)/.published: $(BUILD_DIR)/$(MACH)/packages.ignore $(BUILD_DIR)/$(MACH)/publish.transforms
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
	  $$(pkgrecv -s $(@D)/pkgrepo-merged.dir --newest \
	  | sed -f $(BUILD_DIR)/$(MACH)/packages.ignore)
else
	pkgrepo -s $(ON_REPO.NON_DEBUG) rebuild
	pkgrecv -s $(ON_REPO.NON_DEBUG) -d $(@D)/pkgrecv.dir --raw \
	  $$(pkgrecv -s $(ON_REPO.NON_DEBUG) --newest \
	  | sed -f $(BUILD_DIR)/$(MACH)/packages.ignore)
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

#
# Ensure that when printing packages delivered by illumos, we ignore the
# packages that will be dropped when publishing to the userland repository.
#
# Note that the "pkg5.complete.fmris" cache file should contain all packages
# delivered by the gate, so that "packages.ignore.in" can be modified to apply
# a new filter without rebuilding the gate or the cached list.
#
print-package-names:
	if test -d $(ON_REPO.NON_DEBUG); then \
		pkgrepo list -H -F tsv -s $(ON_REPO.NON_DEBUG) \
		    | cut -f 2 \
		    | LANG=C LC_ALL=C sort -u \
		    > pkg5.complete.fmris; \
	fi
	grep -v -x -F -f packages.ignore.in pkg5.complete.fmris > pkg5.fmris
	cat pkg5.fmris

REQUIRED_PACKAGES += developer/gcc-7
REQUIRED_PACKAGES += developer/illumos-closed
PYTHON_REQUIRED_PACKAGES += runtime/python
