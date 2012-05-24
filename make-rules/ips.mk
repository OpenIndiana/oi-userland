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
# Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
#

#
# Rules and Macros for generating an IPS package manifest and publishing an
# IPS package to a pkg depot.
#
# To use these rules, include ../make-rules/ips.mk in your Makefile
# and define an "install" target appropriate to building your component.
# Ex:
#
#	install:	$(BUILD_DIR)/build/$(MACH32)/.installed \
#	 		$(BUILD_DIR)/build/$(MACH64)/.installed
#
# This set of rules makes the "publish" target the default target for make(1)
#

PKGDEPEND =	/usr/bin/pkgdepend
PKGFMT =	/usr/bin/pkgfmt
PKGMOGRIFY =	/usr/bin/pkgmogrify
PKGSEND =	/usr/bin/pkgsend
PKGLINT =	/usr/bin/pkglint
PKGMANGLE =	$(WS_TOOLS)/userland-mangler

# Package headers should all pretty much follow the same format
METADATA_TEMPLATE =		$(WS_TOP)/transforms/manifest-metadata-template
COPYRIGHT_TEMPLATE =		$(WS_TOP)/transforms/copyright-template

# order is important
GENERATE_TRANSFORMS +=		$(WS_TOP)/transforms/generate-cleanup

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop

COMPARISON_TRANSFORMS +=	$(WS_TOP)/transforms/comparison-cleanup
COMPARISON_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)

# order is important
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/variant-cleanup
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/autopyc
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/defaults
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/actuators
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/devel
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/docs
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/locale
PUBLISH_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/publish-cleanup

PKG_MACROS +=		MACH=$(MACH)
PKG_MACROS +=		MACH32=$(MACH32)
PKG_MACROS +=		MACH64=$(MACH64)
PKG_MACROS +=		PUBLISHER=$(PUBLISHER)
PKG_MACROS +=		PUBLISHER_LOCALIZABLE=$(PUBLISHER_LOCALIZABLE)
PKG_MACROS +=		CONSOLIDATION=$(CONSOLIDATION)
PKG_MACROS +=		BUILD_VERSION=$(BUILD_VERSION)
PKG_MACROS +=		SOLARIS_VERSION=$(SOLARIS_VERSION)
PKG_MACROS +=		OS_VERSION=$(OS_VERSION)
PKG_MACROS +=		HUMAN_VERSION=$(HUMAN_VERSION)
PKG_MACROS +=		IPS_COMPONENT_VERSION=$(IPS_COMPONENT_VERSION)
PKG_MACROS +=		COMPONENT_VERSION=$(COMPONENT_VERSION)
PKG_MACROS +=		COMPONENT_PROJECT_URL=$(COMPONENT_PROJECT_URL)
PKG_MACROS +=		COMPONENT_ARCHIVE_URL=$(COMPONENT_ARCHIVE_URL)
PKG_MACROS +=		COMPONENT_HG_URL=$(COMPONENT_HG_URL)
PKG_MACROS +=		COMPONENT_HG_REV=$(COMPONENT_HG_REV)

PKG_OPTIONS +=		$(PKG_MACROS:%=-D %)

MANGLED_DIR =	$(PROTO_DIR)/mangled

PKG_PROTO_DIRS += $(MANGLED_DIR) $(PROTO_DIR) $(@D) $(COMPONENT_DIR) $(COMPONENT_SRC)

MANIFEST_BASE =		$(BUILD_DIR)/manifest-$(MACH)

CANONICAL_MANIFESTS =	$(wildcard *.p5m)
GENERATED =		$(MANIFEST_BASE)-generated
COMBINED =		$(MANIFEST_BASE)-combined
MANIFESTS =		$(CANONICAL_MANIFESTS:%=$(MANIFEST_BASE)-%)


DEPENDED=$(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.depend)
RESOLVED=$(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.depend.res)
PUBLISHED=$(RESOLVED:%.depend.res=%.published)

COPYRIGHT_FILE ?=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).copyright
IPS_COMPONENT_VERSION ?=	$(COMPONENT_VERSION)

.DEFAULT:		publish

.SECONDARY:

# allow publishing to be overridden, such as when
# a package is for one architecture only.
PUBLISH_STAMP ?= $(BUILD_DIR)/.published-$(MACH)

publish:		build install $(PUBLISH_STAMP)

sample-manifest:	$(GENERATED).p5m

$(GENERATED).p5m:	install
	$(PKGSEND) generate $(PKG_HARDLINKS:%=--target %) $(PROTO_DIR) | \
	$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 $(GENERATE_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | $(PKGFMT) | \
		cat $(METADATA_TEMPLATE) - >$@

# copy the canonical manifest(s) to the build tree
$(MANIFEST_BASE)-%.generate:	%.p5m canonical-manifests
	cat $(METADATA_TEMPLATE) $< >$@

# mogrify the manifest
$(MANIFEST_BASE)-%.mogrified:	%.p5m $(BUILD_DIR) canonical-manifests
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@

# mangle the file contents
$(BUILD_DIR) $(MANGLED_DIR):
	$(MKDIR) $@

PKGMANGLE_OPTIONS = -D $(MANGLED_DIR) $(PKG_PROTO_DIRS:%=-d %)
$(MANIFEST_BASE)-%.mangled:	$(MANIFEST_BASE)-%.mogrified $(MANGLED_DIR)
	$(PKGMANGLE) $(PKGMANGLE_OPTIONS) -m $< >$@

# generate dependencies
PKGDEPEND_GENERATE_OPTIONS = -m $(PKG_PROTO_DIRS:%=-d %)
$(MANIFEST_BASE)-%.depend:	$(MANIFEST_BASE)-%.mangled
	$(PKGDEPEND) generate $(PKGDEPEND_GENERATE_OPTIONS) $< >$@

# resolve the dependencies all at once
$(BUILD_DIR)/.resolved-$(MACH):	$(DEPENDED)
	$(PKGDEPEND) resolve -m $(DEPENDED)
	$(TOUCH) $@

# lint the manifests all at once
$(BUILD_DIR)/.linted-$(MACH):	$(BUILD_DIR)/.resolved-$(MACH)
	@echo "VALIDATING MANIFEST CONTENT: $(RESOLVED)"
	$(ENV) PYTHONPATH=$(WS_TOOLS)/python PROTO_PATH="$(PKG_PROTO_DIRS)"\
		$(PKGLINT) $(CANONICAL_REPO:%=-c $(WS_LINT_CACHE)) \
			-f $(WS_TOOLS)/pkglintrc $(RESOLVED)
	$(TOUCH) $@


# published
PKGSEND_PUBLISH_OPTIONS = -s $(PKG_REPO) publish --fmri-in-manifest
PKGSEND_PUBLISH_OPTIONS += $(PKG_PROTO_DIRS:%=-d %)
PKGSEND_PUBLISH_OPTIONS += -T \*.py
$(MANIFEST_BASE)-%.published:	$(MANIFEST_BASE)-%.depend.res $(BUILD_DIR)/.linted-$(MACH)
	$(PKGSEND) $(PKGSEND_PUBLISH_OPTIONS) $<
	$(PKGFMT) <$< >$@

$(BUILD_DIR)/.published-$(MACH):	$(PUBLISHED)
	$(TOUCH) $@

print-package-names:	canonical-manifests
	@cat $(CANONICAL_MANIFESTS) $(WS_TOP)/transforms/print-pkgs | \
		$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
 		sed -e '/^$$/d' -e '/^#.*$$/d' | sort -u

print-package-paths:	canonical-manifests
	@cat $(CANONICAL_MANIFESTS) $(WS_TOP)/transforms/print-paths | \
		$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
 		sed -e '/^$$/d' -e '/^#.*$$/d' | sort -u

install-packages:	publish
	@if [ $(IS_GLOBAL_ZONE) = 0 -o x$(ROOT) != x ]; then \
	    cat $(CANONICAL_MANIFESTS) $(WS_TOP)/transforms/print-paths | \
		$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
 		sed -e '/^$$/d' -e '/^#.*$$/d' -e 's;/;;' | sort -u | \
		(cd $(PROTO_DIR) ; pfexec /bin/cpio -dump $(ROOT)) ; \
	else ; \
	    echo "unsafe to install package(s) automatically" ; \
        fi

$(RESOLVED):	install

canonical-manifests:	$(CANONICAL_MANIFESTS) Makefile $(PATCHES)
ifeq	($(strip $(CANONICAL_MANIFESTS)),)
	# If there were no canonical manifests in the workspace, nothing will
	# be published and we should fail.  A sample manifest can be generated
	# with
	#   $ gmake sample-manifest
	# Once created, it will need to be reviewed, edited, and added to the
	# workspace.
	$(error Missing canonical manifest(s))
endif

# This converts required paths to containing package names for be able to
# properly setup the build environment for a component.
required-pkgs.mk:	Makefile
	@echo "generating $@ from Makefile REQUIRED_* data"
	@pkg search -H -l '<$(DEPENDS:%=% OR) /bin/true>' \
		| sed -e 's/pkg:\/\(.*\)@.*/REQUIRED_PKGS += \1/g' >$@

pre-prep:	required-pkgs.mk


CLEAN_PATHS +=	required-pkgs.mk
