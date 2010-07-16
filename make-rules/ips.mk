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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#

#
# Rules and Macros for generating an IPS package manifest and publishing an
# IPS package to a pkg depot.
#
# To use these rules, include ../make-rules/ips.mk in your Makefile
# and define an "install" target appropriate to building your component.
# Ex:
#
#	install:	$(COMPONENT_SRC)/build-$(MACH32)/.installed \
#	 		$(COMPONENT_SRC)/build-$(MACH64)/.installed
#
# This set of rules makes the "publish" target the default target for make(1)
#

PKGDEPEND =	/usr/bin/pkgdepend
PKGFMT =	/usr/bin/pkgfmt
PKGMOGRIFY =	/usr/bin/pkgmogrify
PKGSEND =	/usr/bin/pkgsend

# Package headers should all pretty much follow the same format
METADATA_TEMPLATE =		$(WS_TOP)/transforms/manifest-metadata-template
COPYRIGHT_TEMPLATE =		$(WS_TOP)/transforms/copyright-template

# order is important
GENERATE_TRANSFORMS +=		$(WS_TOP)/transforms/generate-cleanup
GENERATE_TRANSFORMS +=		$(WS_TOP)/transforms/variant.arch

COMPARISON_TRANSFORMS +=	$(WS_TOP)/transforms/comparison-cleanup
COMPARISON_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)

# order is important
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/defaults
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/actuators
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/devel
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/docs
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/locale
PUBLISH_TRANSFORMS +=	$(PKGMOGRIFY_TRANSFORMS)
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/publish-cleanup

PKG_MACROS +=		MACH=$(MACH)
PKG_MACROS +=		ARCH=$(MACH)
PKG_MACROS +=		MACH32=$(MACH32)
PKG_MACROS +=		MACH64=$(MACH64)
PKG_MACROS +=		IPS_PKG_NAME=$(IPS_PKG_NAME)
PKG_MACROS +=		PUBLISHER=$(PUBLISHER)
PKG_MACROS +=		CONSOLIDATION=$(CONSOLIDATION)
PKG_MACROS +=		BUILD_VERSION=$(BUILD_VERSION)
PKG_MACROS +=		SOLARIS_VERSION=$(SOLARIS_VERSION)
PKG_MACROS +=		OS_VERSION=$(OS_VERSION)
PKG_MACROS +=		IPS_COMPONENT_VERSION=$(IPS_COMPONENT_VERSION)
PKG_MACROS +=		COMPONENT_PROJECT_URL=$(COMPONENT_PROJECT_URL)
PKG_MACROS +=		COMPONENT_ARCHIVE_URL=$(COMPONENT_ARCHIVE_URL)

PKG_OPTIONS +=		$(PKG_MACROS:%=-D %)
# multi-word macros get broken up, so we handle them "specially"
PKG_OPTIONS +=		-D COMPONENT_SUMMARY=\"$(COMPONENT_SUMMARY)\"
PKG_OPTIONS +=		-D COMPONENT_DESCRIPTION=\"$(COMPONENT_DESCRIPTION)\"
PKG_OPTIONS +=		-D COMPONENT_CLASSIFICATION=\"$(COMPONENT_CLASSIFICATION)\"

MANIFEST_BASE =		$(COMPONENT_SRC)/manifest-$(MACH)

CANONICAL_MANIFESTS =	$(wildcard *.ips)
GENERATED =		$(MANIFEST_BASE)-generated
COMBINED =		$(MANIFEST_BASE)-combined
MANIFESTS =		$(CANONICAL_MANIFESTS:%=$(MANIFEST_BASE)-%)


MOGRIFIED=$(CANONICAL_MANIFESTS:%.ips=$(MANIFEST_BASE)-%.resolved)
PUBLISHED=$(MOGRIFIED:%.resolved=%.published)

COPYRIGHT_FILE =	$(COMPONENT_NAME)-$(COMPONENT_VERSION).copyright
IPS_PKG_NAME =		$(COMPONENT_NAME)
IPS_COMPONENT_VERSION =	$(COMPONENT_VERSION)

.DEFAULT:		publish

.SECONDARY:		$(GENERATED).fdeps

publish:		install $(COMPONENT_SRC)/.published

sample-manifest:	$(GENERATED).ips

#
# Rules for generating a manifest automatically.  Generated manifests will
# contain the following:
#    copyright - template copyright information
#    metadata  - mogrified template metadata
#    actions   - "normalized" actions for the paths to be installed.
#    depends   - automatically generated dependencies
#

# transform template metadata into slightly more package specific metadata.
$(GENERATED).metadata:	$(METADATA_TEMPLATE) install
	$(PKGMOGRIFY) -D IPS_PKG_NAME=$(IPS_PKG_NAME) $< | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | $(PKGFMT) >$@

# generate actions from the proto dir
$(GENERATED).generate:	install
	$(PKGSEND) generate $(PKG_HARDLINKS:%=--target %) $(PROTO_DIR) >$@

# convert actions to a "normalized" format
$(GENERATED).actions:	$(GENERATED).generate
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< $(GENERATE_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | $(PKGFMT) >$@

# generate dependencies
$(MANIFEST_BASE)-%.fdeps:	$(MANIFEST_BASE)-%.generate
	$(PKGDEPEND) generate $(PKG_OPTIONS) $< $(PROTO_DIR) >$@

$(MANIFEST_BASE)-%.depend:	$(MANIFEST_BASE)-%.fdeps
	$(PKGDEPEND) resolve -o $< | sed -e '1d' >$@

# generate a complete manifest from the pieces
$(GENERATED).ips:	$(GENERATED).metadata $(GENERATED).actions \
			$(GENERATED).depend
	cat $(COPYRIGHT_TEMPLATE) $(GENERATED).metadata $(GENERATED).actions \
	    $(GENERATED).depend >$@

#
# Rules to generate a combined manifest from the canonical manifest(s) checked
# into the workspace.
#

# Combine the canonical manifest(s) for this component and "normalize" them
# for comparison.
$(COMBINED).ips:	canonical-manifests
	cat $(CANONICAL_MANIFESTS) | $(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 | \
 		sed -e '/^$$/d' -e '/^#.*$$/d' | sort -u | $(PKGFMT) >$@

$(MANIFEST_BASE)-%.compare:		$(MANIFEST_BASE)-%.ips
	$(PKGMOGRIFY) $(PKG_OPTIONS) $(COMPARISON_TRANSFORMS) $< >$@

manifest-compare:	$(COMBINED).compare $(GENERATED).compare
	@echo "Manifest comparison"
	@pkgdiff $(GENERATED).compare $(COMBINED).compare

# mogrify the canonical manifest(s) 
#
$(MANIFEST_BASE)-%.resolved:	%.ips manifest-compare
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< $(PUBLISH_TRANSFORMS) >$@

$(MANIFEST_BASE)-%.published:	$(MANIFEST_BASE)-%.resolved
	$(PKGSEND) -s $(PKG_REPO) publish --fmri-in-manifest \
		-d $(PROTO_DIR) -d . $<
	$(TOUCH) $@

$(COMPONENT_SRC)/.published:	manifest-compare $(PUBLISHED)
	$(TOUCH) $@

canonical-manifests:	$(CANONICAL_MANIFESTS)
ifeq	($(strip $(CANONICAL_MANIFESTS)),)
	# If there were no canonical manifests in the workspace, nothing will
	# be published and we should fail.  A sample manifest can be generated
	# with
	#   $ gmake sample-manifest
	# Once created, it will need to be reviewed, edited, and added to the
	# workspace.
	$(error Missing canonical manifest(s))
endif
