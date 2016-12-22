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
BUILD_BITS= 64
COMPILER= gcc
# The golang build process just doesn't work with Parfait.
export PARFAIT_BUILD=no
include ../../make-rules/shared-macros.mk

PATCH_EACH_ARCHIVE= 1

COMPONENT_NAME=		golang
COMPONENT_VERSION=	1.7
COMPONENT_MAJOR_VERSION=	$(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\([0-9]\+\.[0-9]\+\).*/\1/')
COMPONENT_PROJECT_URL=	https://golang.org/
COMPONENT_ARCHIVE=	go$(COMPONENT_VERSION).src.tar.gz
COMPONENT_ARCHIVE_URL=	https://storage.googleapis.com/golang/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	 \
	sha256:72680c16ba0891fcf2ccf46d0f809e4ecf47bbf889f5d884ccb54c5e9a17e1c0
COMPONENT_PROJECT_URL=	https://golang.org

ARC_CASE=		PSARC/2015/203,PSARC/2016/250
TPNO=			29538

# Go has a number of supplementary tools and packages that are located in
# separate archives or source repositories. Because Go currently forces a
# recompile of all packages whenever the compiler changes, building and
# delivering them within the same build component build process is the best
# option for now.

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
GIT_COMMIT_ID_crypto=		986d3313588aa5c68f1df95eac956f79cf3b2c01
GIT_COMMIT_ID_image=		9f8d0d45877da31f672995d10677ae6a586e31a5
GIT_COMMIT_ID_lint=		c7bacac2b21ca01afa1dee0acf64df3ce047c28f
GIT_COMMIT_ID_net=		7394c112eae4dba7e96bfcfe738e6373d61772b4
GIT_COMMIT_ID_sys=		9bb9f0998d48b31547d975974935ae9b48c7a03c
GIT_COMMIT_ID_text=		d69c40b4be55797923cec7457fac7a244d91a9b6
GIT_COMMIT_ID_tools=		5cb1c80a83ef2a98bbc7b2fba1305239bb684fbe
GIT_COMMIT_ID_tour=		c9941e54e5b8e9618a8c951bc89798f85f6a7a71

# Resulting hash of related git commit once archived.
GIT_HASH_crypto=  sha256:62a83544383df032f63d655c6831316da80de93b1a3d99593950b32f40a823a3
GIT_HASH_image=  sha256:979c3a8fb093508c27b95dff99b42a3a1fbd0e83374f40097608dd637b9f6968
GIT_HASH_lint=  sha256:6f9d91eaa133f7dad2bb65a901b972e952c1acc9e7e504e5efe0605000369305
GIT_HASH_net=  sha256:e568aee2b95f9eb375a213ed80020a5ce133767b93723bba037f9a99071e7d32
GIT_HASH_sys=  sha256:dd44f9fc2d78bc69eec53dd9bfcdf6740fbb5bd2ad4a75ad11d62f5b4bd62afd
GIT_HASH_text=  sha256:397ab7c85efc9272de036ebdebfe91ca6ac190765d883950845dec6a189769bc
GIT_HASH_tools=  sha256:0d386842aea4abf61d1d5eff7795ee01ec3d6a49353fccb477c53330f42245e3
GIT_HASH_tour=  sha256:b9f64fa35ca745b1841502e7aa880c7cadbadcb07c657239d58b5e31da55f170

# Go package imports for lint are found in github directory.
COMPONENT_IMPORT_SRC_lint=	github.com/golang

# Go's "not well-formed" elf objects confuse elfsign, which then causes
# problems for RE.  For now, we workaround this by adding the
# 'com.oracle.elfsign=false' tag to every elf object.
NO_ELFSIGN_MOG=		$(BUILD_DIR)/no-elfsign.mog

PUBLISH_STAMP= $(NO_ELFSIGN_MOG) $(BUILD_DIR)/.published-$(MACH)

# Bake in where Go package will be installed.
GOROOT_FINAL=		/usr/lib/golang/$(COMPONENT_MAJOR_VERSION)
# Enable easier stack unwinding for debugging.
GOEXPERIMENT=		framepointer
COMPONENT_BUILD_ENV +=	GOROOT_FINAL="$(GOROOT_FINAL)"
COMPONENT_BUILD_ENV +=	GOEXPERIMENT="$(GOEXPERIMENT)"

# This allows us to build regardless of whether 1.5 or 1.7 is installed.
BOOTSTRAP= $(firstword $(wildcard $(USRLIBDIR)/golang/1.[57]))
COMPONENT_BUILD_ENV +=	\
	GOROOT_BOOTSTRAP="$(BOOTSTRAP)"

# Install root for supplementary packages.
SUPP_ROOT=$(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)

# For convenience during installation of supplementary packages.
COMPONENT_INSTALL_ENV += PATH="$(PROTO_DIR)$(GOROOT_FINAL)/bin:$(PATH)"
COMPONENT_INSTALL_ENV += GOROOT="$(PROTO_DIR)$(GOROOT_FINAL)"
COMPONENT_INSTALL_ENV += GOPATH="$(SUPP_ROOT)"

BUILD_STYLE= justmake
BUILD_64 += $(BUILD_DIR)/man1/go.1
INSTALL_64 := build $(INSTALL_64)
ifeq ($(MACH), sparc)
# At least one test in the suite core dumps on sparc64; skip until ready.
TEST_TARGET= $(SKIP_TESTS)
endif
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
# Go internally determines one normally from git revision info.  Use the block
# below when building from the upstream source repository or when building a
# development version from a source tarball:
#
# We have to fiddle with the package archives to get them into the same source
# directory so that we can use the standard build targets.  We're effectively
# building multiple components using a single target.
COMPONENT_POST_UNPACK_ACTION= \
	$(MV) go $(COMPONENT_SRC) && \
	$(TOUCH) $(COMPONENT_SRC)/VERSION && \
	echo "devel $(shell digest -a md5 $(COMPONENT_ARCHIVE)) \
		$(shell date -u +'%a %b %e %T %Z %Y')" > \
		$(COMPONENT_SRC)/VERSION && \
	(cd $(COMPONENT_SRC); git apply -p1 < ../patches/*.git)

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
# Compound version of major version (e.g. 1.5 -> 15).
PKG_MACROS += COMPONENT_CMAJOR_VERSION=$(subst .,,$(COMPONENT_MAJOR_VERSION))
# COMPONENT_MAJOR_VERSION suitable for use in regular expressions.
PKG_MACROS += COMPONENT_RE_MAJOR_VERSION=$(subst .,\\.,$(COMPONENT_MAJOR_VERSION))
# GOMACH64 is Go's name for current build architecture
PKG_MACROS += GOMACH64=$(MACH64:sparcv9=sparc64)

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
$(MANIFEST_BASE)-$(1)-17.mogrified: PKG_PROTO_DIRS= $(MANGLED_DIR) $(PROTO_DIR) $(@D) $(COMPONENT_DIR) $(COMPONENT_SRC_$(1))

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
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/plan9/mksyscall.pl \
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/unix/mksyscall.pl \
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/unix/mksyscall_solaris.pl \
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/unix/mksysctl_openbsd.pl \
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/unix/mksysnum_darwin.pl \
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/unix/mksysnum_dragonfly.pl \
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/unix/mksysnum_freebsd.pl \
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/unix/mksysnum_linux.pl \
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/unix/mksysnum_netbsd.pl \
  $(PROTOUSRLIBDIR)/gocode/$(COMPONENT_MAJOR_VERSION)/src/golang.org/x/sys/unix/mksysnum_openbsd.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/net/http/cgi/testdata/test.cgi \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/regexp/syntax/make_perl_groups.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/syscall/mksyscall.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/syscall/mksyscall_solaris.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/syscall/mksysctl_openbsd.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/syscall/mksysnum_darwin.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/syscall/mksysnum_dragonfly.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/syscall/mksysnum_freebsd.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/syscall/mksysnum_linux.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/syscall/mksysnum_netbsd.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/src/syscall/mksysnum_openbsd.pl \
  $(PROTOUSRLIBDIR)/golang/$(COMPONENT_MAJOR_VERSION)/test/errchk

COMPONENT_POST_INSTALL_ACTION += $(PERL_SCRIPTS_PROCESS)

# Go's test suite is currently designed to be run from the build area.

# Used during the build.
REQUIRED_PACKAGES += developer/gcc
REQUIRED_PACKAGES += developer/versioning/git
ifneq ($(MACH), sparc)
# Go bootstraps itself using Go, so at least one previous version must already
# be installed.
REQUIRED_PACKAGES += developer/golang
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
