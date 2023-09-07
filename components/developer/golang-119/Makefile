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
# Copyright 2021 Till Wegmueller
#

BUILD_STYLE= justmake
USE_COMMON_TEST_MASTER= no
CLONEY_ARGS= CLONEY_MODE="copy"
include ../../../make-rules/shared-macros.mk

PATCH_EACH_ARCHIVE= 1

COMPONENT_NAME=			golang
COMPONENT_MAJOR_VERSION=	1.19
COMPONENT_VERSION=		$(COMPONENT_MAJOR_VERSION).13
COMPONENT_SUMMARY=		The Go Programming Language
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=		https://golang.org/
COMPONENT_ARCHIVE=		go$(COMPONENT_VERSION).src.tar.gz
COMPONENT_ARCHIVE_URL=		https://storage.googleapis.com/golang/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:ccf36b53fb0024a017353c3ddb22c1f00bc7a8073c6aac79042da24ee34434d3
COMPONENT_FMRI=			developer/golang
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=		BSD-style, Patent Grant
COMPONENT_LICENSE_FILE=		LICENSE

MEDIATEDUSRSHAREMAN1DIR=	$(PROTO_DIR)/usr/share/golang/$(COMPONENT_MAJOR_VERSION)/man/man1

# Go has a number of supplementary tools and packages that are located in
# separate archives or source repositories. Because Go currently forces a
# recompile of all packages whenever the compiler changes, building and
# delivering them within the same build component build process is the best
# option for now.

# Bake in where Go package will be installed.
GOROOT_FINAL=		/usr/lib/golang/$(COMPONENT_MAJOR_VERSION)
# Enable easier stack unwinding for debugging.
GOEXPERIMENT=
# Use golang 1.8 to bootstrap golang 1.19
COMPONENT_BUILD_ENV += GOROOT_BOOTSTRAP="/usr/lib/golang/1.8"
COMPONENT_BUILD_ENV +=	GOROOT_FINAL="$(GOROOT_FINAL)"
COMPONENT_BUILD_ENV +=	GOEXPERIMENT="$(GOEXPERIMENT)"
COMPONENT_BUILD_ENV +=	GOOS="illumos"
COMPONENT_BUILD_ENV +=	GOCACHE="$(SOURCE_DIR)/gocache"
COMPONENT_BUILD_ENV +=  GOPATH="$(SOURCE_DIR)/gopath"
COMPONENT_BUILD_ENV +=  GO_LDSO=/lib/64/ld.so.1

# For convenience during installation of supplementary packages.
COMPONENT_INSTALL_ENV += PATH="$(PROTO_DIR)$(GOROOT_FINAL)/bin:$(PATH)"
COMPONENT_INSTALL_ENV += GOROOT="$(PROTO_DIR)$(GOROOT_FINAL)"
COMPONENT_INSTALL_ENV += GOCACHE="$(SOURCE_DIR)/gocache"
COMPONENT_INSTALL_ENV += GOPATH="$(SOURCE_DIR)/gopath"

include $(WS_MAKE_RULES)/common.mk

# We have to fiddle with the package archives to get them into the same source
# directory so that we can use the standard build targets.  We're effectively
# building multiple components using a single target.
COMPONENT_POST_UNPACK_ACTION= \
	$(MV) go $(COMPONENT_SRC)

# Go doesn't have a standard Makefile-based build process, so override the
# default.
COMPONENT_BUILD_ACTION=	\
	cd $(@D)/src; $(ENV) $(COMPONENT_BUILD_ENV) ./make.bash

COMPONENT_TARGET_DIR= \
	$(PROTOUSRLIBDIR)/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)

# We can't do any ASLR'ing as the Go 6l linker has no understanding of the
# -z aslr=... option. So just override where needed in the .p5m files.
ASLR_MODE = $(ASLR_DISABLE)

COMPONENT_TEST_ENV +=	PATH="$(@D)/bin:$(PATH)"
COMPONENT_TEST_ENV +=	GOROOT="$(@D)"
COMPONENT_TEST_DIR =	$(@D)/src
COMPONENT_TEST_CMD =	./run.bash
COMPONENT_TEST_TARGETS =
# Remove CPU
COMPONENT_TEST_TRANSFORMS += "-e '/^\# CPU:/d'"
# Remove OS Version
COMPONENT_TEST_TRANSFORMS += "-e '/^\# OS Version:/d'"
# Remove measured times (eg. 11.106s, 0.312s or 1,16s):
COMPONENT_TEST_TRANSFORMS += "-e 's/[ \t]*[0-9]\{1,\}\.[0-9]\{1,\}s//'"

# Use this Command to copy the Go Source tree into the proto area. In order to deliver the Go SDK under GOROOT
# Additionally nuke all the funky binary files used for test suites. They keep bothering the packaging tools
define COMPONENT_INSTALL_ACTION=
	($(MKDIR) $(COMPONENT_TARGET_DIR)/src); \
	(cd $(SOURCE_DIR) && \
	/usr/gnu/bin/find . -maxdepth 1 -path "./$(COMPONENT_SRC_NAME)" \
	  -prune -o \( ! -iname ".*" \) -print \
	  -exec /usr/gnu/bin/cp -r \
	  --parents {} $(COMPONENT_TARGET_DIR) \;); \
	(cd $(BUILD_DIR_64) && \
	/usr/gnu/bin/find src -type f \
		-exec /usr/gnu/bin/cp --parents {} $(COMPONENT_TARGET_DIR) \;); \
	(cd $(BUILD_DIR_64) && $(CP) -r bin $(COMPONENT_TARGET_DIR)/); \
	(cd $(BUILD_DIR_64) && $(CP) -r pkg $(COMPONENT_TARGET_DIR)/); \
	(rm -r $(COMPONENT_TARGET_DIR)/pkg/obj); \
	($(MKDIR) -p $(MEDIATEDUSRSHAREMAN1DIR)); \
	/usr/gnu/bin/find $(COMPONENT_TARGET_DIR)/src -type f \
       	| egrep -v '\.go|\.s|\.bash|\.txt|\.c|\.tmpl|\.h|\.pl|\.md|\.S|\.py|\.dist|\.rc|\.bat|README|Makefile|\.awk|\.rules|\.mod|\.json|LICENSE|PATENTS|\.bin'\
	| xargs rm;
endef

REQUIRED_PACKAGES += developer/golang-18

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
