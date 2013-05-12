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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

# $(WS_TOP)/make-rules/ips.mk really isn't set up to allow you to bypass all
# the automatic (and lengthy) manifest manipulation that it does, which we
# really don't need to do for these static, uninteresting packages.  So we just
# write a simple set of publication rules to get the packages into the repo.

PKGSEND =	/usr/bin/pkgsend
PKGLINT =	/usr/bin/pkglint
PKGMOGRIFY =	/usr/bin/pkgmogrify

COMPONENT_NAME=		"Package History"
COMPONENT_BUGDB=	gate-stuff/userland

CANONICAL_MANIFESTS =	$(shell ls *.p5m | sed -f manifests.ignore)
ARCH_MANIFESTS =	$(shell ls *.p5m.$(MACH) | sed -f manifests.ignore)
GENERATED_ARCH_MANIFESTS =	$(ARCH_MANIFESTS:%.p5m.$(MACH)=%.p5m)
CANONICAL_MANIFESTS +=  $(GENERATED_ARCH_MANIFESTS)

MANIFEST_BASE =		$(BUILD_DIR)/manifest-$(MACH)
MOGRIFIED =		$(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.mogrified)
PUBLISHED =		$(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.published)

download prep build install:
	@echo "nothing to be done for $@"

$(BUILD_DIR):
	$(MKDIR) $@

$(MANIFEST_BASE)-%.mogrified: %.p5m $(BUILD_DIR)
	$(PKGMOGRIFY) -D CONSOLIDATION=$(CONSOLIDATION) $< > $@

$(MANIFEST_BASE)-%.published: $(MANIFEST_BASE)-%.mogrified $(BUILD_DIR)
	$(PKGSEND) -s $(PKG_REPO) publish --fmri-in-manifest $<
	$(CP) $< $@

$(BUILD_DIR)/.linted-$(MACH): $(MOGRIFIED) $(BUILD_DIR)
#	$(ENV) PYTHONPATH=$(WS_TOOLS)/python \
#		$(PKGLINT) $(CANONICAL_REPO:%=-c $(WS_LINT_CACHE)) \
#			-f $(WS_TOOLS)/pkglintrc $(MOGRIFIED)
	$(TOUCH) $@

$(BUILD_DIR)/.published-$(MACH): $(BUILD_DIR)/.linted-$(MACH) $(PUBLISHED)
	$(TOUCH) $@

publish: $(BUILD_DIR)/.published-$(MACH)

%.p5m: 	%.p5m.$(MACH)
	$(CP) $< $@
	
clobber clean:
	$(RM) -r $(BUILD_DIR) $(GENERATED_ARCH_MANIFESTS)
