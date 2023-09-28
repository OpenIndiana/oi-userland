#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2023 Till Wegmueller
#

PKGDEV="/ws/toasty/.cargo/bin/pkgdev"

generate-pakage-kdl:
	@echo "generating package.kdl for $(COMPONENT_NAME)"
	$(PKGDEV) create $(COMPONENT_FMRI)
	@for package in $(REQUIRED_PACKAGES) ; do \
		$(PKGDEV) add dependency --dev --kind require $$package ;  \
	done
	$(PKGDEV) set project-name "$(COMPONENT_NAME)"
	$(PKGDEV) set summary "$(COMPONENT_SUMMARY)"
	$(PKGDEV) set classification "$(COMPONENT_CLASSIFICATION)"
	$(PKGDEV) set license "$(COMPONENT_LICENSE)" "$(COMPONENT_LICENSE_FILE)"
	$(PKGDEV) set version "$(COMPONENT_VERSION)"
	$(PKGDEV) set project-url "$(COMPONENT_PROJECT_URL)"
	$(PKGDEV) set maintainer "The OpenIndiana Maintainers"
	$(PKGDEV) add source archive "$(COMPONENT_ARCHIVE_URL)"

