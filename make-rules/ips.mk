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
PKGLINT =	/usr/bin/pkglint

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
PKG_OPTIONS +=		-D COMPONENT_SUMMARY=$(COMPONENT_SUMMARY)
PKG_OPTIONS +=		-D COMPONENT_DESCRIPTION=$(COMPONENT_DESCRIPTION)
PKG_OPTIONS +=		-D COMPONENT_CLASSIFICATION=$(COMPONENT_CLASSIFICATION)

MANIFEST_BASE =		$(COMPONENT_SRC)/manifest-$(MACH)

CANONICAL_MANIFESTS =	$(wildcard *.p5m)
GENERATED =		$(MANIFEST_BASE)-generated
COMBINED =		$(MANIFEST_BASE)-combined
MANIFESTS =		$(CANONICAL_MANIFESTS:%=$(MANIFEST_BASE)-%)


MOGRIFIED=$(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.resolved)
PUBLISHED=$(MOGRIFIED:%.resolved=%.published)

COPYRIGHT_FILE =	$(COMPONENT_NAME)-$(COMPONENT_VERSION).copyright
ifeq	($(IPS_PKG_NAME),)
	IPS_PKG_NAME =	$(COMPONENT_NAME)
endif
ifeq	($(COMPONENT_SUMMARY),)
	COMPONENT_SUMMARY =	$(COMPONENT_DESCRIPTION)
endif
IPS_COMPONENT_VERSION =	$(COMPONENT_VERSION)

.DEFAULT:		publish

.SECONDARY:

publish:		install $(COMPONENT_SRC)/.published

sample-manifest:	$(GENERATED).p5m

$(GENERATED).p5m:	install
	$(PKGSEND) generate $(PKG_HARDLINKS:%=--target %) $(PROTO_DIR) | \
	$(PKGMOGRIFY) $(PKG_OPTIONS) /dev/fd/0 $(GENERATE_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | $(PKGFMT) >$@

# copy the canonical manifest(s) to the build tree
$(MANIFEST_BASE)-%.generate:	%.p5m canonical-manifests
	cat $(METADATA_TEMPLATE) $< >$@

# mogrify the manifest
$(MANIFEST_BASE)-%.mogrified:	%.p5m $(METADATA_TEMPLATE) canonical-manifests
	$(PKGMOGRIFY) $(PKG_OPTIONS) $(METADATA_TEMPLATE) $< \
		$(PUBLISH_TRANSFORMS) | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@

# generate dependencies, drop variant.arch in set and depend actions because
# "pkgdepend resolve" fails when it's present.
$(MANIFEST_BASE)-%.depend:	$(MANIFEST_BASE)-%.mogrified
	$(PKGDEPEND) generate -m $< $(PROTO_DIR) | \
	$(PKGMOGRIFY) /dev/fd/0 $(WS_TOP)/transforms/drop-variant.arch >$@

# resolve dependencies, prepend the mogrified manifest, less the unresolved
# dependencies to the result.
$(MANIFEST_BASE)-%.resolved:	$(MANIFEST_BASE)-%.depend
	$(PKGMOGRIFY) $(@:%.resolved=%.mogrified) \
		$(WS_TOP)/transforms/drop-unresolved-dependencies | \
		sed -e '/^$$/d' -e '/^#.*$$/d' | uniq >$@
	$(PKGDEPEND) resolve -o $< | sed -e '1d' >>$@

# lint the manifest before we publish with it.
$(MANIFEST_BASE)-%.linted:	$(MANIFEST_BASE)-%.resolved
	@echo "VALIDATING MANIFEST CONTENT: $<"
	PYTHONPATH=$(WS_TOP)/tools/python $(PKGLINT) -f $(WS_TOP)/tools/pkglintrc $<
	$(PKGFMT) <$< >$@

# published
$(MANIFEST_BASE)-%.published:	$(MANIFEST_BASE)-%.linted
	$(PKGSEND) -s $(PKG_REPO) publish --fmri-in-manifest \
		-d $(PROTO_DIR) -d $(@D) -d . $<
	$(PKGFMT) <$< >$@

$(COMPONENT_SRC)/.published:	$(PUBLISHED)
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

$(MOGRIFIED):	install

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
