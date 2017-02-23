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
# Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
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
COMPONENT_ANITYA_ID=	1227

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
COMPONENT_LABEL_$(1)=
COMPONENT_IMPORT_SRC_$(1)=	golang.org/x
GIT_REPO_$(1)=			https://github.com/golang/$(1).git
TPNO_$(1)=			$(TPNO)
endef

$(foreach suffix, $(SUPP_PACKAGES), $(eval $(call supp-rules,$(suffix))))

# Desired "revision" of Go's "community" libraries; these are arbitrary
# revisions chosen from the last commit to the respective repository at the
# same time that this component was updated as there is no formal release
# process for these packages.  Whenever Go is updated, these should be as well.
GIT_COMMIT_ID_crypto=		1777f3ba8c1fed80fcaec3317e3aaa4f627764d2
GIT_COMMIT_ID_image=		baddd3465a05d84a6d8d3507547a91cb188c81ea
GIT_COMMIT_ID_lint=		8f348af5e29faa4262efdc14302797f23774e477
GIT_COMMIT_ID_net=		fb93926129b8ec0056f2f458b1f519654814edf0
GIT_COMMIT_ID_sys=		9eef40adf05b951699605195b829612bd7b69952
GIT_COMMIT_ID_text=		5ee49cfe751141f8017047bab800d1f528ee3be1
GIT_COMMIT_ID_tools=		5da1e91fb2cc877989e7c73748b505a0612956f2
GIT_COMMIT_ID_tour=		41d86d51aaa4f1cf4f66e42456ba137c93cad950

# Resulting hash of related git commit once archived.
GIT_HASH_crypto=  sha256:05003de0b534b6e0303dc7c2a0f88a1cd53af11acde96fa5a38bcbaf31250c5e
GIT_HASH_image=  sha256:96951cea9d34603209961d46010610894df6c708321e1b4781d71bdd180e75b8
GIT_HASH_lint=  sha256:1ad5bbf9c21327c73cb67db1329aee8253e18de994302c8ce1a98581bda4da44
GIT_HASH_net=  sha256:ca7830ac9af95232204ebc52d27c4726c32e4c0df760e039faba0224075fcb59
GIT_HASH_sys=  sha256:b5fdef2664d43430e58250c25564b0376895eb44fbd7e292d5251e5deea8a0c8
GIT_HASH_text=  sha256:f65d0191d15042773899efe405fd3e4168922bba2494b2e68f0408bbef23e777
GIT_HASH_tools=  sha256:c260308533abc9ea95328eee34616f59ccef1737c51be9be6d652f538777b661
GIT_HASH_tour=  sha256:c484f1dbdd67e5108418574d808daf223cc4c544c0f9e4bea4150978197914bc

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

# The timestamp is generated immediately once when the Makefile is evaluated to
# ensure every package gets the same one.
GOTS := $(shell date +"%Y%m%dT%H%M%SZ")

# Make sure the source code and object files have identical timestamps so
# the Go compiler doesn't try to rebuild them.
PKG_MACROS += TIMESTAMP=$(GOTS)
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
	($(MKDIR) $(PROTOUSRSHAREDIR)/golang); \
	($(CP) $(BUILD_DIR)/man1/go.1 $(PROTOUSRSHAREDIR)/golang/go-$(COMPONENT_MAJOR_VERSION).1); \
	($(RM) $(NO_ELFSIGN_MOG))
endef

# clear COMPONENT_POST_INSTALL_ACTION so we can append PERL_SCRIPTS_PROCESS
# at the end
COMPONENT_POST_INSTALL_ACTION =

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
# Install supplementary packages (this cannot be done one-by-one); install
# tools/go/types first to avoid quirk with trimpath and dependencies.  This is
# technically a build and install, but go's build command won't "install"
# results, it only verifies a target can be built and dumps it into a temporary
# directory.
#
# The -trimpath option used here ensures that the paths recorded in the
# pre-built packages do not contain the containing directory; the result is a
# path that Go will evaluate relative to $GOPATH and so will pass the "stale"
# object checks that Go performs at build time allowing reuse of the pre-built
# packages.
PROTO_ROOT= $(SUPP_ROOT)
COMPONENT_POST_INSTALL_ACTION += \
	($(ENV) $(COMPONENT_INSTALL_ENV) go install \
		-asmflags -trimpath=$(PROTO_ROOT) -gcflags -trimpath=$(PROTO_ROOT) \
		"golang.org/x/tools/go/types"; \
	$(ENV) $(COMPONENT_INSTALL_ENV) go install \
		-asmflags -trimpath=$(PROTO_ROOT) -gcflags -trimpath=$(PROTO_ROOT) \
		"golang.org/x/..."; \
	$(ENV) $(COMPONENT_INSTALL_ENV) go install \
		-asmflags -trimpath=$(PROTO_ROOT) -gcflags -trimpath=$(PROTO_ROOT) \
		"github.com/golang/...");

PERL_SCRIPTS= \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/plan9/mksyscall.pl \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/unix/mksysnum_netbsd.pl \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/unix/mksyscall_solaris.pl \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/unix/mksyscall.pl \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/unix/mksysnum_freebsd.pl \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/unix/mksysctl_openbsd.pl \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/unix/mksysnum_dragonfly.pl \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/unix/mksysnum_openbsd.pl \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/unix/mksysnum_linux.pl \
  $(PROTOUSRLIBDIR)/gocode/1.5/src/golang.org/x/sys/unix/mksysnum_darwin.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/regexp/syntax/make_perl_groups.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/syscall/mksysnum_freebsd.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/syscall/mksysctl_openbsd.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/syscall/mksyscall.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/syscall/mksysnum_openbsd.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/syscall/mksysnum_darwin.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/syscall/mksysnum_netbsd.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/syscall/mksysnum_linux.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/syscall/mksyscall_solaris.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/src/syscall/mksysnum_dragonfly.pl \
  $(PROTOUSRLIBDIR)/golang/1.5/test/errchk

COMPONENT_POST_INSTALL_ACTION += $(PERL_SCRIPTS_PROCESS)

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
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += system/header
REQUIRED_PACKAGES += system/library
# Used for cgo support at runtime; we don't add a package dependency since cgo
# support is optional.
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/linker
