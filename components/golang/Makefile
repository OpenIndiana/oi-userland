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

#
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_ARCH= i386
BUILD_BITS= 64
COMPILER= gcc
# The golang build process just doesn't work with Parfait.
export PARFAIT_BUILD=no
include ../../make-rules/shared-macros.mk

PATCH_EACH_ARCHIVE= 1

COMPONENT_NAME=		golang
COMPONENT_VERSION=	1.5
COMPONENT_MAJOR_VERSION=	$(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\([0-9]\+\.[0-9]\+\).*/\1/')
COMPONENT_PROJECT_URL=	https://golang.org/
COMPONENT_ARCHIVE=	go$(COMPONENT_VERSION).src.tar.gz
COMPONENT_ARCHIVE_URL=	https://storage.googleapis.com/golang/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	 \
	sha256:be81abec996d5126c05f2d36facc8e58a94d9183a56f026fc9441401d80062db
COMPONENT_PROJECT_URL=	https://golang.org

ARC_CASE=		PSARC/2015/203
TPNO=			23679

# Go has a number of supplementary tools and packages that are located in
# separate archives or source repositories. Because Go currently forces a
# recompile of all packages whenever the compiler changes, building and
# delivering them within the same build component build process is the best
# option for now.

# The long-term plan for packaging Go is roughly as follows:
#
# - when SPARC support is integrated into Go upstream, build upstream version
#   using system Go for x86, then build Go for SPARC using upstream version
#   just built for x86 (cross-compilation), package both at the same time
# - after SPARC version has been available for at least a few builds in the
#   WOS, switch to building Go with system version for x86 and SPARC
#

# Supplementary packages; these are delivered as source only for now as the
# paths to the compiled packages are written directly into the binaries and
# there's no way (currently) to fix that during the build process.
SUPP_PACKAGES=		crypto image lint net sys text tools tour

define supp-rules
COMPONENT_NAME_$(1)=		$(1)
COMPONENT_VERSION_$(1)=		$(COMPONENT_VERSION)
COMPONENT_IMPORT_SRC_$(1)=	golang.org/x
GIT_REPO_$(1)=			https://github.com/golang/$(1).git
TPNO_$(1)=			$(TPNO)
endef

$(foreach suffix, $(SUPP_PACKAGES), $(eval $(call supp-rules,$(suffix))))

# Desired "revision" of Go's "community" libraries; these are arbitrary
# revisions chosen from the last commit to the respective repository at the
# same time that this component was updated as there is no formal release
# process for these packages.  Whenever Go is updated, these should be as well.
GIT_COMMIT_ID_crypto=		0c93e1ff9f91f0c63bf17b123de503d023434fdd
GIT_COMMIT_ID_image=		baddd3465a05d84a6d8d3507547a91cb188c81ea
GIT_COMMIT_ID_lint=		32a87160691b3c96046c0c678fe57c5bef761456
GIT_COMMIT_ID_net=		b4e17d61b15679caf2335da776c614169a1b4643
GIT_COMMIT_ID_sys=		d9157a9621b69ad1d8d77a1933590c416593f24f
GIT_COMMIT_ID_text=		22af8577cc7d0b37e7fb5708399a12115bfe6900
GIT_COMMIT_ID_tools=		ac6d9c1d842f9b6482f39f7a172e0251a0f7cbc0
GIT_COMMIT_ID_tour=		1c790b9f8bfefe44f33fbc9aacf5a6bc06027321

# Resulting hash of related git commit once archived.
COMPONENT_ARCHIVE_HASH_crypto=	\
	sha256:6b088fa04632857c7b6244bf887f560f9fe2efa8342072f3837e9fe556c1190e
COMPONENT_ARCHIVE_HASH_image=	\
	sha256:96951cea9d34603209961d46010610894df6c708321e1b4781d71bdd180e75b8
COMPONENT_ARCHIVE_HASH_lint=	\
	sha256:1b5f8c917056dc850da9220a19f907ed323c62e1f42f5a09f3648ee73a98ae6d
COMPONENT_ARCHIVE_HASH_net=	\
	sha256:dca84ca46ed8eb46db12c27a3b5720acacdd6d0206304453d48056d6b9688e81
COMPONENT_ARCHIVE_HASH_sys=	\
	sha256:267416d3f0cda4c916192e5c2587ba2a591a593a0c8dc65df3e7f5e5c791acc7
COMPONENT_ARCHIVE_HASH_text=	\
	sha256:8484f1a25689f0e45c11768ed054acb7b747fe5b22c23565e744ec5c40f0e4c6
COMPONENT_ARCHIVE_HASH_tools=	\
	sha256:a02ef6a6c344bc6c643af00a6ba0549c7442fa0111279dca601341d16683ba56
COMPONENT_ARCHIVE_HASH_tour=	\
	sha256:19e6a5396b7b65cece97cb203a335a2924c6cd648709d80ef8aa3c220aab8f88

# Go package imports for lint are found in github directory.
COMPONENT_IMPORT_SRC_lint=	github.com/golang

# Go's "not well-formed" elf objects confuse elfsign, which then causes
# problems for RE.  For now, we workaround this by adding the
# 'com.oracle.elfsign=false' tag to every elf object.
NO_ELFSIGN_MOG=		$(BUILD_DIR)/no-elfsign.mog

# We're x86-only for now.
ifeq ($(MACH), sparc)
PUBLISH_STAMP=
else
PUBLISH_STAMP= $(NO_ELFSIGN_MOG) $(BUILD_DIR)/.published-$(MACH)
endif

# Bake in where Go package will be installed.
GOROOT_FINAL=		/usr/lib/golang/$(COMPONENT_MAJOR_VERSION)
# Enable easier stack unwinding for debugging.
GOEXPERIMENT=		framepointer
COMPONENT_BUILD_ENV +=	GOROOT_FINAL="$(GOROOT_FINAL)"
COMPONENT_BUILD_ENV +=	GOEXPERIMENT="$(GOEXPERIMENT)"
COMPONENT_BUILD_ENV +=	\
	GOROOT_BOOTSTRAP="$(USRLIBDIR)/golang/1.5"

# Install root for supplementary packages.
SUPP_ROOT=$(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)

# For convenience during installation of supplementary packages.
COMPONENT_INSTALL_ENV += PATH="$(PROTO_DIR)$(GOROOT_FINAL)/bin:$(PATH)"
COMPONENT_INSTALL_ENV += GOROOT="$(PROTO_DIR)$(GOROOT_FINAL)"
COMPONENT_INSTALL_ENV += GOPATH="$(SUPP_ROOT)"

BUILD_STYLE= justmake
BUILD_64 += $(BUILD_DIR)/man1/go.1
INSTALL_64 := build $(INSTALL_64)
include $(WS_MAKE_RULES)/common.mk

# Simplify source copying for install by eliding patch detritus.
GPATCH_BACKUP=

# Enable local transforms.
PKG_OPTIONS += -I $(COMPONENT_DIR)

# Avoid some of the default transforms:
# - facet.devel serves no useful purpose for a development package
# - facet.doc wrongly assumes all things in a doc directory are documentation;
#   in Go's case, some are binaries
#
# This requires completely redefining PUBLISH_TRANSFORMS for now.
PUBLISH_TRANSFORMS=	$(LICENSE_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/variant-cleanup
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/defaults
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/actuators
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/locale
PUBLISH_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/incorporate
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/publish-cleanup
ifeq ($(BUILD_TYPE),evaluation)
	PUBLISH_TRANSFORMS += $(WS_TOP)/transforms/evaluation
endif

$(NO_ELFSIGN_MOG): install
	cd $(PROTO_DIR); \
	find . -type f -exec elffile {} + | grep 'ELF [36]' | \
	    $(GSED) -e 's/^..\(.*\):.*$$/<transform file path=\1$$ -> \\\
	        default com.oracle.elfsign false>/' > $@

PUBLISH_TRANSFORMS +=	$(NO_ELFSIGN_MOG)

# Building go from the source repository version requires that we set an
# effective version and add some sort of unique identifier (in the case of
# pre-release versions), so we use 'devel' + archive hash + date similar to how
# Go internally determines one normally from git revision info.  Uncomment the
# block below when building from the upstream source repository:
#COMPONENT_POST_UNPACK_ACTION= \
#	$(MV) go-master $(COMPONENT_SRC) && \
#	$(TOUCH) $(COMPONENT_SRC)/VERSION && \
#	echo "devel $(shell digest -a md5 $(COMPONENT_ARCHIVE)) \
#		$(shell date -u +'%a %b %e %T %Z %Y')" > \
#		$(COMPONENT_SRC)/VERSION

# We have to fiddle with the package archives to get them into the same source
# directory so that we can use the standard build targets.  We're effectively
# building multiple components using a single target.
COMPONENT_POST_UNPACK_ACTION= \
	$(MV) go $(COMPONENT_SRC)

# Fixup compressed data affected by patches.
COMPONENT_PREP_ACTION= \
	cd $(COMPONENT_SRC) && \
	bzip2 -c src/compress/testdata/Mark.Twain-Tom.Sawyer.txt > \
		src/compress/bzip2/testdata/Mark.Twain-Tom.Sawyer.txt.bz2

# Go doesn't have a standard Makefile-based build process, so override the
# default.
COMPONENT_BUILD_ACTION=	\
	cd $(@D)/src; $(ENV) $(COMPONENT_BUILD_ENV) ./make.bash

COMPONENT_TARGET_DIR= \
	$(PROTOUSRLIBDIR)/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)

# We can't do any ASLR'ing as the Go 6l linker has no understanding of the
# -z aslr=... option. So just override where needed in the .p5m files.
ASLR_MODE = $(ASLR_DISABLE)

# Make sure the source code and object files have identical timestamps so
# the Go compiler doesn't try to rebuild them.
PKG_MACROS += TIMESTAMP=$(shell date +"%Y%m%dT%H%M%SZ")
# Extra macros for packaging convenience.
PKG_MACROS += COMPONENT_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)
# COMPONENT_MAJOR_VERSION suitable for use in regular expressions.
PKG_MACROS += COMPONENT_RE_MAJOR_VERSION=$(subst .,\\.,$(COMPONENT_MAJOR_VERSION))

COMPONENT_TEST_ENV +=	PATH="$(@D)/bin:$(PATH)"
COMPONENT_TEST_ENV +=	GOROOT="$(@D)"
COMPONENT_TEST_DIR=	$(@D)/src
COMPONENT_TEST_CMD=	./run.bash
COMPONENT_TEST_TARGETS=

# Go's test suite does not have deterministic output or order, and as such,
# success can only be determined by exit code, not by output comparison.
COMPONENT_TEST_CREATE_TRANSFORMS=
COMPONENT_TEST_PERFORM_TRANSFORM=
COMPONENT_TEST_COMPARE=

XML2ROFF= $(USRSHAREDIR)/xml/xsolbook/python/xml2roff.py

$(BUILD_DIR)/man1/go.1:
	$(XML2ROFF) $(COMPONENT_DIR)/docs/go.1 -o $(BUILD_DIR)

define COMPONENT_INSTALL_ACTION=
	($(MKDIR) $(COMPONENT_TARGET_DIR)/src); \
	(cd $(SOURCE_DIR) && \
	$(GNUBIN)/find . -maxdepth 1 -print \
	  -exec $(GNUBIN)/cp -r \
	  --parents {} $(COMPONENT_TARGET_DIR) \;); \
	(cd $(BUILD_DIR_64) && \
	$(GNUBIN)/find src -type f \
		-exec $(GNUBIN)/cp --parents {} $(COMPONENT_TARGET_DIR) \;); \
	(cd $(BUILD_DIR_64) && $(CP) -r bin $(COMPONENT_TARGET_DIR)/); \
	(cd $(BUILD_DIR_64) && $(CP) -r pkg $(COMPONENT_TARGET_DIR)/); \
	($(MKDIR) $(PROTOUSRSHAREMAN1DIR)); \
	($(CP) $(BUILD_DIR)/man1/go.1 $(PROTOUSRSHAREMAN1DIR)/); \
	($(RM) $(NO_ELFSIGN_MOG))
endef

#
# Magic to deliver supplemental package source into proto area.
#
define install-rules
$(MANIFEST_BASE)-$(1)-15.mogrified: PKG_PROTO_DIRS= $(MANGLED_DIR) $(PROTO_DIR) $(@D) $(COMPONENT_DIR) $(COMPONENT_SRC_$(1))

BUILD_64 += $$(UNPACK_STAMP_$(1))

COMPONENT_POST_INSTALL_ACTION += \
	($(MKDIR) \
		$(SUPP_ROOT)/src/$$(COMPONENT_IMPORT_SRC_$(1))/$$(COMPONENT_NAME_$(1)); \
	$(CP) -r $$(COMPONENT_SRC_$(1))/* \
		$(SUPP_ROOT)/src/$$(COMPONENT_IMPORT_SRC_$(1))/$$(COMPONENT_NAME_$(1)));

endef

$(foreach suffix,$(SUPP_PACKAGES), $(eval $(call install-rules,$(suffix))))

# XXX For now, the install of supplementary packages is intentionally disabled
# as the result cannot be used as expected due to an unknown issue with the Go
# compilers.
#
# Install supplementary packages (this cannot be done one-by-one); install
# tools/go/types first to avoid quirk with trimpath and dependencies.  This is
# technically a build and install, but go's build command won't "install"
# results, it only verifies a target can be built and dumps it into a temporary
# directory.
#
# The -trimpath option used here ensures that the paths recorded in the
# pre-built packages are relative to the $(SUPP_ROOT) so that when a devleoper
# sets their GOPATH to that directory, things work as expected.
#COMPONENT_POST_INSTALL_ACTION += \
#	($(ENV) $(COMPONENT_INSTALL_ENV) go install \
#		-asmflags -trimpath=$(SUPP_ROOT) -gcflags -trimpath=$(SUPP_ROOT) \
#		"golang.org/x/tools/go/types"; \
#	$(ENV) $(COMPONENT_INSTALL_ENV) go install \
#		-asmflags -trimpath=$(SUPP_ROOT) -gcflags -trimpath=$(SUPP_ROOT) \
#		"golang.org/x/..."; \
#	$(ENV) $(COMPONENT_INSTALL_ENV) go install \
#		-asmflags -trimpath=$(SUPP_ROOT) -gcflags -trimpath=$(SUPP_ROOT) \
#		"github.com/golang/...");

# Go's test suite is currently designed to be run from the build area.

# Used during the build.
REQUIRED_PACKAGES += developer/gcc
ifneq ($(MACH), sparc)
# Go 1.5 now bootstraps itself using 1.5; 1.6 will bootstrap using 1.5 as well.
REQUIRED_PACKAGES += developer/golang-15
endif
# Used in this Makefile.
REQUIRED_PACKAGES += file/gnu-findutils
REQUIRED_PACKAGES += text/gnu-sed
# Required to build man pages.
REQUIRED_PACKAGES += developer/documentation-tool/xml2roff
# There's a single test script which requires perl.
REQUIRED_PACKAGES += runtime/perl-520
REQUIRED_PACKAGES += system/header
REQUIRED_PACKAGES += system/library
# Used for cgo support at runtime; we don't add a package dependency since cgo
# support is optional.
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/linker
