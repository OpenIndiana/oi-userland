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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

# $(WS_MAKE_RULES)/ips.mk really isn't set up to allow you to bypass all
# the automatic (and lengthy) manifest manipulation that it does, which we
# really don't need to do for these static, uninteresting packages.  So we just
# write a simple set of publication rules to get the packages into the repo.

# For gmake clean to work
COMPONENT_SRC=nonexistent

PKGSEND =	/usr/bin/pkgsend
PKGLINT =	/usr/bin/python3.5 /usr/bin/pkglint
PKGMOGRIFY =	/usr/bin/pkgmogrify

GENERATE_HISTORY=	$(WS_TOOLS)/generate-history
HISTORY=		history

MANIFEST_BASE =		$(BUILD_DIR)/manifest-$(MACH)

CANONICAL_MANIFESTS =	$(filter-out dummy.p5m,$(wildcard *.p5m))
HISTORICAL_MANIFESTS =	$(shell $(NAWK) -v FUNCTION=name -f $(GENERATE_HISTORY) < $(HISTORY))
ARCH_MANIFESTS =	$(wildcard *.p5m.$(MACH))
GENERATED_ARCH_MANIFESTS =	$(ARCH_MANIFESTS:%.p5m.$(MACH)=%.p5m)
CANONICAL_MANIFESTS +=  $(GENERATED_ARCH_MANIFESTS)

MOGRIFIED =		$(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.mogrified)
HISTOGRIFIED =		$(HISTORICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.histogrified)
PUBLISHED =		$(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.published)
PUBLISHED +=		$(HISTORICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.published)

# Rule to generate historical manifests from the $(HISTORY) file.
define history-manifest-rule
$(MANIFEST_BASE)-$(1): $(HISTORY) $(BUILD_DIR)
	$(NAWK) -v FUNCTION=manifest -v TARGET=$1 -f $(GENERATE_HISTORY) < \
	    $(HISTORY) > $$@
endef
$(foreach mfst,$(HISTORICAL_MANIFESTS),$(eval $(call history-manifest-rule,$(mfst))))

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PKG_MACROS =		CONSOLIDATION=$(CONSOLIDATION)
PKG_MACROS +=		BUILD_VERSION=$(BUILD_VERSION)
PKG_MACROS +=		OS_VERSION=$(OS_VERSION)

PKG_OPTIONS +=		$(PKG_MACROS:%=-D %)

build install test system-test:
	@echo "nothing to be done for $@"

$(BUILD_DIR):
	$(MKDIR) $@

$(MANIFEST_BASE)-%.mogrified: %.p5m $(BUILD_DIR)
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< > $@

$(MANIFEST_BASE)-%.histogrified: $(MANIFEST_BASE)-%.p5m $(BUILD_DIR)
	$(PKGMOGRIFY) $(PKG_OPTIONS) $< > $@

$(MANIFEST_BASE)-%.published: $(MANIFEST_BASE)-%.mogrified $(BUILD_DIR)
	$(PKGSEND) -s $(PKG_REPO) publish --fmri-in-manifest --no-catalog $<
	$(CP) $< $@

$(MANIFEST_BASE)-%.published: $(MANIFEST_BASE)-%.histogrified $(BUILD_DIR)
	$(PKGSEND) -s $(PKG_REPO) publish --fmri-in-manifest --no-catalog $<
	$(CP) $< $@

$(BUILD_DIR)/.linted-$(MACH): $(MOGRIFIED) $(HISTOGRIFIED) $(BUILD_DIR)
	if [[ -n "$(MOGRIFIED)" ]]; \
	then \
	$(ENV) PYTHONPATH=$(WS_TOOLS)/python \
		SOLARIS_VERSION=$(SOLARIS_VERSION) \
		$(PKGLINT) $(CANONICAL_REPO:%=-c $(WS_LINT_CACHE)) \
			-f $(WS_TOOLS)/pkglintrc $(MOGRIFIED); \
	fi
	$(TOUCH) $@

$(BUILD_DIR)/.published-$(MACH): $(BUILD_DIR)/.linted-$(MACH) $(PUBLISHED)
	$(TOUCH) $@

publish: $(BUILD_DIR)/.published-$(MACH)

%.p5m: 	%.p5m.$(MACH)
	$(CP) $< $@
	
clobber clean::
	$(RM) -r $(BUILD_DIR) $(GENERATED_ARCH_MANIFESTS)
