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
#	install:	$(COMPONENT_SRC)/build-32/.installed \
#	 		$(COMPONENT_SRC)/build-64/.installed
#
# This set of rules makes the "publish" target the default target for make(1)
#

PKGSEND =	/usr/bin/pkgsend
PKGMOGRIFY =	/usr/bin/pkgmogrify
PKGDEPEND =	/usr/bin/pkgdepend

# Add some default transforms that should apply to everyone
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/defaults
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/actuators
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/devel
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/docs

.DEFAULT:	publish

publish:	$(COMPONENT_SRC)/.published

COPYRIGHT_FILE =	$(COMPONENT_NAME)-$(COMPONENT_VERSION).copyright

$(PROTO_DIR)/$(COPYRIGHT_FILE):	$(COMPONENT_COPYRIGHT)
	$(CP) $< $@

$(COMPONENT_SRC)/manifest:	install
	pkgsend generate $(PROTO_DIR) >$@

$(COMPONENT_SRC)/manifest.mog:	$(COMPONENT_SRC)/manifest $(PROTO_DIR)/$(COPYRIGHT_FILE)
	echo "set name=pkg.fmri value=pkg:/$(PUBLISHER)/$(COMPONENT_NAME)@$(COMPONENT_VERSION),$(BUILD_VERSION)" >$@
	echo "set name=pkg.description value=\"$(COMPONENT_DESCRIPTION)\"" >>$@
	echo "set name=pkg.name value=\"$(COMPONENT_DESCRIPTION)\"" >>$@
	echo "set name=org.opensolaris.consolidation value=$(CONSOLIDATION)" >>$@
	echo "license $(COPYRIGHT_FILE) license=$(COPYRIGHT_FILE)" >>$@
	pkgmogrify $(PKGMOGRIFY_MACROS:%=-D %) $(PKGMOGRIFY_TRANSFORMS) $< >>$@

$(COMPONENT_SRC)/manifest.fdeps:	$(COMPONENT_SRC)/manifest.mog
	pkgdepend generate -m $< $(PROTO_DIR) >$@

$(COMPONENT_SRC)/manifest.fdeps.res:	$(COMPONENT_SRC)/manifest.fdeps
	pkgdepend resolve -m $<

$(COMPONENT_SRC)/.published:	$(COMPONENT_SRC)/manifest.fdeps.res
	pkgsend -s $(PKG_REPO) publish --fmri-in-manifest \
		-d $(PROTO_DIR) $<
	$(TOUCH) $@
