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

# Copyright 2016 Aurelien Larcher
# Copyright 2017 Till Wegmueller
#

include ../../../make-rules/shared-macros.mk

PATCH_EACH_ARCHIVE= 1

#
# WARNING:
# This component is needed for bootstrapping golang 1.19 so it cannot be obsoleted yet.
#

COMPONENT_NAME=			golang
COMPONENT_VERSION=		1.8.7
COMPONENT_REVISION=		1
COMPONENT_MAJOR_VERSION=	$(shell echo $(COMPONENT_VERSION) | gsed -e 's/\([0-9]\+\.[0-9]\+\).*/\1/')
COMPONENT_FMRI=			developer/golang
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_SUMMARY=		The Go Programming Language
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=		https://golang.org/
COMPONENT_ARCHIVE=		go$(COMPONENT_VERSION).src.tar.gz
COMPONENT_ARCHIVE_URL=		https://storage.googleapis.com/golang/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:5911e751807eebbc1980dad4305ef5492b96d6cd720bf93cbcefa86e1c195f9e
COMPONENT_LICENSE=		BSD-style, Patent Grant
COMPONENT_LICENSE_FILE=		$(COMPONENT_NAME).license
MEDIATEDUSRSHAREMAN1DIR=	$(PROTO_DIR)/usr/share/golang/1.8/man/man1

# Go has a number of supplementary tools and packages that are located in
# separate archives or source repositories. Because Go currently forces a
# recompile of all packages whenever the compiler changes, building and
# delivering them within the same build component build process is the best
# option for now.

# This version of Go is not actually packaged; it is only used to bootstrap the
# actual version of the Go that will be packaged.  The long-term plan is
# roughly as follows:
#
# - verify 1.5 produces "correct" result for bootstrapping 1.5 (upstream
#   still uses 1.4 officially)
# - after 1.5 has been available for at least a few builds in the WOS, switch
#   to building Go with system version of Go
# - when SPARC support is integrated into Go upstream, build upstream version
#   using system Go for x86, then build Go for SPARC using upstream version
#   just built for x86 (cross-compilation), package both at the same time
# - after SPARC version has been available for at least a few builds in the
#   WOS, switch to building Go with system version for x86 and SPARC
#

COMPONENT_NAME_1=		golang
COMPONENT_VERSION_1=		1.4.3
COMPONENT_SRC_NAME_1=		$(COMPONENT_NAME_1)$(COMPONENT_VERSION_1)
COMPONENT_SRC_1=		$(COMPONENT_SRC_NAME_1)
COMPONENT_ARCHIVE_1=		go$(COMPONENT_VERSION_1).src.tar.gz
COMPONENT_ARCHIVE_HASH_1=	\
	sha256:9947fc705b0b841b5938c48b22dc33e9647ec0752bae66e50278df4f23f64959
COMPONENT_ARCHIVE_URL_1=	https://storage.googleapis.com/golang/$(COMPONENT_ARCHIVE_1)

# Bake in where Go package will be installed.
GOROOT_FINAL=		/usr/lib/golang/$(COMPONENT_MAJOR_VERSION)
# Enable easier stack unwinding for debugging.
GOEXPERIMENT=		framepointer
COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS) $(CPP_XPG6MODE)"
COMPONENT_BUILD_ENV +=	GOROOT_FINAL="$(GOROOT_FINAL)"
COMPONENT_BUILD_ENV +=	GOEXPERIMENT="$(GOEXPERIMENT)"
COMPONENT_BUILD_ENV +=	\
	GOROOT_BOOTSTRAP="$(BUILD_DIR_64)/$(COMPONENT_SRC_NAME_1)"

# For convenience during installation of supplementary packages.
COMPONENT_INSTALL_ENV += PATH="$(PROTO_DIR)$(GOROOT_FINAL)/bin:$(PATH)"
COMPONENT_INSTALL_ENV += GOROOT="$(PROTO_DIR)$(GOROOT_FINAL)"
COMPONENT_INSTALL_ENV += GOPATH="$(SUPP_ROOT)"

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# We have to fiddle with the package archives to get them into the same source
# directory so that we can use the standard build targets.  We're effectively
# building multiple components using a single target.
COMPONENT_POST_UNPACK_ACTION= \
	$(MV) go $(COMPONENT_SRC)

COMPONENT_POST_UNPACK_ACTION_1= \
	$(MV) go $(COMPONENT_SRC_1) && \
	$(CP) -r $(COMPONENT_SRC_1) $(COMPONENT_SRC)/$(COMPONENT_SRC_1)

# Fixup compressed data affected by patches.
COMPONENT_PREP_ACTION= \
	cd $(COMPONENT_SRC) && \
	bzip2 -c src/compress/testdata/Mark.Twain-Tom.Sawyer.txt > \
		src/compress/bzip2/testdata/Mark.Twain-Tom.Sawyer.txt.bz2

# Build the bootstrap compiler before attempting to build Go 1.5+.  For the
# bootstrap compiler ensure GOROOT_FINAL is unset as it will be executed out of
# the build area, and ensure GOROOT_BOOTSTRAP is also not set.  GOEXPERIMENT
# must also be unset as it is 1.5+ only.
COMPONENT_PRE_BUILD_ACTION= \
	cd $(@D)/$(COMPONENT_SRC_NAME_1)/src; \
	$(ENV) $(COMPONENT_BUILD_ENV) \
	PATH="$(GCC_BINDIR):$(PATH)" \
	GOEXPERIMENT= GOROOT_BOOTSTRAP= GOROOT_FINAL= ./make.bash

# Go doesn't have a standard Makefile-based build process, so override the
# default.
COMPONENT_BUILD_ACTION=	\
	cd $(@D)/src; $(ENV) $(COMPONENT_BUILD_ENV) \
	PATH="$(GCC_BINDIR):$(PATH)" \
	./make.bash

COMPONENT_TARGET_DIR= \
	$(PROTOUSRLIBDIR)/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)

# We can't do any ASLR'ing as the Go 6l linker has no understanding of the
# -z aslr=... option. So just override where needed in the .p5m files.
ASLR_MODE = $(ASLR_DISABLE)

COMPONENT_TEST_ENV +=	PATH="$(@D)/bin:$(GCC_BINDIR):$(PATH)"
COMPONENT_TEST_ENV +=	GOROOT="$(@D)"
COMPONENT_TEST_DIR=	$(@D)/src
COMPONENT_TEST_CMD=	./run.bash
COMPONENT_TEST_TARGETS=

define COMPONENT_INSTALL_ACTION=
	($(MKDIR) $(COMPONENT_TARGET_DIR)/src); \
	(cd $(SOURCE_DIR) && \
	/usr/gnu/bin/find . -maxdepth 1 -path "./$(COMPONENT_SRC_NAME_1)" \
	  -prune -o \( ! -iname ".*" \) -print \
	  -exec /usr/gnu/bin/cp -r \
	  --parents {} $(COMPONENT_TARGET_DIR) \;); \
	(cd $(BUILD_DIR_64) && \
	/usr/gnu/bin/find src -type f \
		-exec /usr/gnu/bin/cp --parents {} $(COMPONENT_TARGET_DIR) \;); \
	(cd $(BUILD_DIR_64) && $(CP) -r bin $(COMPONENT_TARGET_DIR)/); \
	(cd $(BUILD_DIR_64) && $(CP) -r pkg $(COMPONENT_TARGET_DIR)/); \
	($(MKDIR) -p $(MEDIATEDUSRSHAREMAN1DIR) && cp -f $(COMPONENT_DIR)/files/go.1 $(MEDIATEDUSRSHAREMAN1DIR));
endef

# common targets
build:		$(BUILD_64)

install:	build $(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
